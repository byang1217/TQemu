/*
 * QEMU System Emulator
 *
 * Copyright (c) 2003-2008 Fabrice Bellard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* Needed early for CONFIG_BSD etc. */
#include "qemu/osdep.h"

#include "monitor/monitor.h"
#include "qapi/qmp/qerror.h"
#include "qemu/error-report.h"
#include "sysemu/sysemu.h"
#include "sysemu/block-backend.h"
#include "exec/gdbstub.h"
#include "sysemu/dma.h"
#include "sysemu/kvm.h"
#include "qmp-commands.h"

#include "qemu/thread.h"
#include "sysemu/cpus.h"
#include "sysemu/qtest.h"
#include "qemu/main-loop.h"
#include "qemu/bitmap.h"
#include "qemu/seqlock.h"
#include "qapi-event.h"
#include "hw/nmi.h"
#include "sysemu/replay.h"

#ifndef _WIN32
#include "qemu/compatfd.h"
#endif

#ifdef CONFIG_LINUX

#include <sys/prctl.h>

#ifndef PR_MCE_KILL
#define PR_MCE_KILL 33
#endif

#ifndef PR_MCE_KILL_SET
#define PR_MCE_KILL_SET 1
#endif

#ifndef PR_MCE_KILL_EARLY
#define PR_MCE_KILL_EARLY 1
#endif

#endif /* CONFIG_LINUX */

static CPUState *next_cpu;
int64_t max_delay;
int64_t max_advance;

/* vcpu throttling controls */
static QEMUTimer *throttle_timer;
static unsigned int throttle_percentage;

#define CPU_THROTTLE_PCT_MIN 1
#define CPU_THROTTLE_PCT_MAX 99
#define CPU_THROTTLE_TIMESLICE_NS 10000000

bool cpu_is_stopped(CPUState *cpu)
{
    return cpu->stopped || !runstate_is_running();
}

static bool cpu_thread_is_idle(CPUState *cpu)
{
    if (cpu->stop || cpu->queued_work_first) {
        return false;
    }
    if (cpu_is_stopped(cpu)) {
        return true;
    }
    if (!cpu->halted || cpu_has_work(cpu) ||
        kvm_halt_in_kernel()) {
        return false;
    }
    return true;
}

static bool all_cpu_threads_idle(void)
{
    CPUState *cpu;

    CPU_FOREACH(cpu) {
        if (!cpu_thread_is_idle(cpu)) {
            return false;
        }
    }
    return true;
}

/***********************************************************/
/* guest cycle counter */

/* Protected by TimersState seqlock */

static bool icount_sleep = true;
static int64_t vm_clock_warp_start = -1;
/* Conversion factor from emulated instructions to virtual clock ticks.  */
static int icount_time_shift;
/* Arbitrarily pick 1MIPS as the minimum allowable speed.  */
#define MAX_ICOUNT_SHIFT 10

static QEMUTimer *icount_rt_timer;
static QEMUTimer *icount_vm_timer;
static QEMUTimer *icount_warp_timer;

typedef struct TimersState {
    /* Protected by BQL.  */
    int64_t cpu_ticks_prev;
    int64_t cpu_ticks_offset;

    /* cpu_clock_offset can be read out of BQL, so protect it with
     * this lock.
     */
    QemuSeqLock vm_clock_seqlock;
    int64_t cpu_clock_offset;
    int32_t cpu_ticks_enabled;
    int64_t dummy;

    /* Compensate for varying guest execution speed.  */
    int64_t qemu_icount_bias;
    /* Only written by TCG thread */
    int64_t qemu_icount;
} TimersState;

static TimersState timers_state;

int64_t cpu_get_icount_raw(void)
{
    int64_t icount;
    CPUState *cpu = current_cpu;

    icount = timers_state.qemu_icount;
    if (cpu) {
        if (!cpu->can_do_io) {
            fprintf(stderr, "Bad icount read\n");
            exit(1);
        }
        icount -= (cpu->icount_decr.u16.low + cpu->icount_extra);
    }
    return icount;
}

/* Return the virtual CPU time, based on the instruction counter.  */
static int64_t cpu_get_icount_locked(void)
{
    int64_t icount = cpu_get_icount_raw();
    return timers_state.qemu_icount_bias + cpu_icount_to_ns(icount);
}

int64_t cpu_get_icount(void)
{
    int64_t icount;
    unsigned start;

    do {
        start = seqlock_read_begin(&timers_state.vm_clock_seqlock);
        icount = cpu_get_icount_locked();
    } while (seqlock_read_retry(&timers_state.vm_clock_seqlock, start));

    return icount;
}

int64_t cpu_icount_to_ns(int64_t icount)
{
    return icount << icount_time_shift;
}

/* return the host CPU cycle counter and handle stop/restart */
/* Caller must hold the BQL */
int64_t cpu_get_ticks(void)
{
    int64_t ticks;

    ticks = timers_state.cpu_ticks_offset;
    if (timers_state.cpu_ticks_enabled) {
        ticks += cpu_get_host_ticks();
    }

    if (timers_state.cpu_ticks_prev > ticks) {
        /* Note: non increasing ticks may happen if the host uses
           software suspend */
        timers_state.cpu_ticks_offset += timers_state.cpu_ticks_prev - ticks;
        ticks = timers_state.cpu_ticks_prev;
    }

    timers_state.cpu_ticks_prev = ticks;
    return ticks;
}

static int64_t cpu_get_clock_locked(void)
{
    int64_t ticks;

    ticks = timers_state.cpu_clock_offset;
    if (timers_state.cpu_ticks_enabled) {
        ticks += get_clock();
    }

    return ticks;
}

/* return the host CPU monotonic timer and handle stop/restart */
int64_t cpu_get_clock(void)
{
    int64_t ti;
    unsigned start;

    do {
        start = seqlock_read_begin(&timers_state.vm_clock_seqlock);
        ti = cpu_get_clock_locked();
    } while (seqlock_read_retry(&timers_state.vm_clock_seqlock, start));

    return ti;
}

/* enable cpu_get_ticks()
 * Caller must hold BQL which server as mutex for vm_clock_seqlock.
 */
void cpu_enable_ticks(void)
{
    /* Here, the really thing protected by seqlock is cpu_clock_offset. */
    seqlock_write_lock(&timers_state.vm_clock_seqlock);
    if (!timers_state.cpu_ticks_enabled) {
        timers_state.cpu_ticks_offset -= cpu_get_host_ticks();
        timers_state.cpu_clock_offset -= get_clock();
        timers_state.cpu_ticks_enabled = 1;
    }
    seqlock_write_unlock(&timers_state.vm_clock_seqlock);
}

/* disable cpu_get_ticks() : the clock is stopped. You must not call
 * cpu_get_ticks() after that.
 * Caller must hold BQL which server as mutex for vm_clock_seqlock.
 */
void cpu_disable_ticks(void)
{
    /* Here, the really thing protected by seqlock is cpu_clock_offset. */
    seqlock_write_lock(&timers_state.vm_clock_seqlock);
    if (timers_state.cpu_ticks_enabled) {
        timers_state.cpu_ticks_offset += cpu_get_host_ticks();
        timers_state.cpu_clock_offset = cpu_get_clock_locked();
        timers_state.cpu_ticks_enabled = 0;
    }
    seqlock_write_unlock(&timers_state.vm_clock_seqlock);
}

/* Correlation between real and virtual time is always going to be
   fairly approximate, so ignore small variation.
   When the guest is idle real and virtual time will be aligned in
   the IO wait loop.  */
#define ICOUNT_WOBBLE (NANOSECONDS_PER_SECOND / 10)

static void icount_adjust(void)
{
    int64_t cur_time;
    int64_t cur_icount;
    int64_t delta;

    /* Protected by TimersState mutex.  */
    static int64_t last_delta;

    /* If the VM is not running, then do nothing.  */
    if (!runstate_is_running()) {
        return;
    }

    seqlock_write_lock(&timers_state.vm_clock_seqlock);
    cur_time = cpu_get_clock_locked();
    cur_icount = cpu_get_icount_locked();

    delta = cur_icount - cur_time;
    /* FIXME: This is a very crude algorithm, somewhat prone to oscillation.  */
    if (delta > 0
        && last_delta + ICOUNT_WOBBLE < delta * 2
        && icount_time_shift > 0) {
        /* The guest is getting too far ahead.  Slow time down.  */
        icount_time_shift--;
    }
    if (delta < 0
        && last_delta - ICOUNT_WOBBLE > delta * 2
        && icount_time_shift < MAX_ICOUNT_SHIFT) {
        /* The guest is getting too far behind.  Speed time up.  */
        icount_time_shift++;
    }
    last_delta = delta;
    timers_state.qemu_icount_bias = cur_icount
                              - (timers_state.qemu_icount << icount_time_shift);
    seqlock_write_unlock(&timers_state.vm_clock_seqlock);
}

static void icount_adjust_rt(void *opaque)
{
    timer_mod(icount_rt_timer,
              qemu_clock_get_ms(QEMU_CLOCK_VIRTUAL_RT) + 1000);
    icount_adjust();
}

static void icount_adjust_vm(void *opaque)
{
    timer_mod(icount_vm_timer,
                   qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) +
                   NANOSECONDS_PER_SECOND / 10);
    icount_adjust();
}

static int64_t qemu_icount_round(int64_t count)
{
    return (count + (1 << icount_time_shift) - 1) >> icount_time_shift;
}

static void icount_warp_rt(void)
{
    unsigned seq;
    int64_t warp_start;

    /* The icount_warp_timer is rescheduled soon after vm_clock_warp_start
     * changes from -1 to another value, so the race here is okay.
     */
    do {
        seq = seqlock_read_begin(&timers_state.vm_clock_seqlock);
        warp_start = vm_clock_warp_start;
    } while (seqlock_read_retry(&timers_state.vm_clock_seqlock, seq));

    if (warp_start == -1) {
        return;
    }

    seqlock_write_lock(&timers_state.vm_clock_seqlock);
    if (runstate_is_running()) {
        int64_t clock = REPLAY_CLOCK(REPLAY_CLOCK_VIRTUAL_RT,
                                     cpu_get_clock_locked());
        int64_t warp_delta;

        warp_delta = clock - vm_clock_warp_start;
        timers_state.qemu_icount_bias += warp_delta;
    }
    vm_clock_warp_start = -1;
    seqlock_write_unlock(&timers_state.vm_clock_seqlock);

    if (qemu_clock_expired(QEMU_CLOCK_VIRTUAL)) {
        qemu_clock_notify(QEMU_CLOCK_VIRTUAL);
    }
}

static void icount_timer_cb(void *opaque)
{
    /* No need for a checkpoint because the timer already synchronizes
     * with CHECKPOINT_CLOCK_VIRTUAL_RT.
     */
    icount_warp_rt();
}

void qemu_start_warp_timer(void)
{
}

static void qemu_account_warp_timer(void)
{
}

static bool icount_state_needed(void *opaque)
{
    return use_icount;
}

/*
 * This is a subsection for icount migration.
 */
static const VMStateDescription icount_vmstate_timers = {
    .name = "timer/icount",
    .version_id = 1,
    .minimum_version_id = 1,
    .needed = icount_state_needed,
#if 0
    .fields = (VMStateField[]) {
        VMSTATE_INT64(qemu_icount_bias, TimersState),
        VMSTATE_INT64(qemu_icount, TimersState),
        VMSTATE_END_OF_LIST()
    }
#endif
};

static const VMStateDescription vmstate_timers = {
    .name = "timer",
    .version_id = 2,
    .minimum_version_id = 1,
#if 0
    .fields = (VMStateField[]) {
        VMSTATE_INT64(cpu_ticks_offset, TimersState),
        VMSTATE_INT64(dummy, TimersState),
        VMSTATE_INT64_V(cpu_clock_offset, TimersState, 2),
        VMSTATE_END_OF_LIST()
    },
    .subsections = (const VMStateDescription*[]) {
        &icount_vmstate_timers,
        NULL
    }
#endif
};

static void cpu_throttle_thread(void *opaque)
{
    CPUState *cpu = opaque;
    double pct;
    double throttle_ratio;
    long sleeptime_ns;

    if (!cpu_throttle_get_percentage()) {
        return;
    }

    pct = (double)cpu_throttle_get_percentage()/100;
    throttle_ratio = pct / (1 - pct);
    sleeptime_ns = (long)(throttle_ratio * CPU_THROTTLE_TIMESLICE_NS);

    qemu_mutex_unlock_iothread();
    atomic_set(&cpu->throttle_thread_scheduled, 0);
    g_usleep(sleeptime_ns / 1000); /* Convert ns to us for usleep call */
    qemu_mutex_lock_iothread();
}

static void cpu_throttle_timer_tick(void *opaque)
{
    CPUState *cpu;
    double pct;

    /* Stop the timer if needed */
    if (!cpu_throttle_get_percentage()) {
        return;
    }
    CPU_FOREACH(cpu) {
        if (!atomic_xchg(&cpu->throttle_thread_scheduled, 1)) {
            async_run_on_cpu(cpu, cpu_throttle_thread, cpu);
        }
    }

    pct = (double)cpu_throttle_get_percentage()/100;
    timer_mod(throttle_timer, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL_RT) +
                                   CPU_THROTTLE_TIMESLICE_NS / (1-pct));
}

void cpu_throttle_set(int new_throttle_pct)
{
    /* Ensure throttle percentage is within valid range */
    new_throttle_pct = MIN(new_throttle_pct, CPU_THROTTLE_PCT_MAX);
    new_throttle_pct = MAX(new_throttle_pct, CPU_THROTTLE_PCT_MIN);

    atomic_set(&throttle_percentage, new_throttle_pct);

    timer_mod(throttle_timer, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL_RT) +
                                       CPU_THROTTLE_TIMESLICE_NS);
}

void cpu_throttle_stop(void)
{
    atomic_set(&throttle_percentage, 0);
}

bool cpu_throttle_active(void)
{
    return (cpu_throttle_get_percentage() != 0);
}

int cpu_throttle_get_percentage(void)
{
    return atomic_read(&throttle_percentage);
}

void cpu_ticks_init(void)
{
    seqlock_init(&timers_state.vm_clock_seqlock, NULL);
    vmstate_register(NULL, 0, &vmstate_timers, &timers_state);
    throttle_timer = timer_new_ns(QEMU_CLOCK_VIRTUAL_RT,
                                           cpu_throttle_timer_tick, NULL);
}

void configure_icount(QemuOpts *opts, Error **errp)
{
}

/***********************************************************/
void hw_error(const char *fmt, ...)
{
    va_list ap;
    CPUState *cpu;

    va_start(ap, fmt);
    fprintf(stderr, "qemu: hardware error: ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    CPU_FOREACH(cpu) {
        fprintf(stderr, "CPU #%d:\n", cpu->cpu_index);
        cpu_dump_state(cpu, stderr, fprintf, CPU_DUMP_FPU);
    }
    va_end(ap);
    abort();
}

void cpu_synchronize_all_states(void)
{
    CPUState *cpu;

    CPU_FOREACH(cpu) {
        cpu_synchronize_state(cpu);
    }
}

void cpu_synchronize_all_post_reset(void)
{
    CPUState *cpu;

    CPU_FOREACH(cpu) {
        cpu_synchronize_post_reset(cpu);
    }
}

void cpu_synchronize_all_post_init(void)
{
    CPUState *cpu;

    CPU_FOREACH(cpu) {
        cpu_synchronize_post_init(cpu);
    }
}

static bool cpu_can_run(CPUState *cpu)
{
    if (cpu->stop) {
        return false;
    }
    if (cpu_is_stopped(cpu)) {
        return false;
    }
    return true;
}

static void cpu_handle_guest_debug(CPUState *cpu)
{
    gdb_set_stop_cpu(cpu);
    qemu_system_debug_request();
    cpu->stopped = true;
}

static QemuMutex qemu_global_mutex;
static QemuCond qemu_io_proceeded_cond;
static unsigned iothread_requesting_mutex;

static QemuThread io_thread;

/* cpu creation */
static QemuCond qemu_cpu_cond;
/* system init */
static QemuCond qemu_pause_cond;
static QemuCond qemu_work_cond;

void run_on_cpu(CPUState *cpu, void (*func)(void *data), void *data)
{
    struct qemu_work_item wi;

    if (qemu_cpu_is_self(cpu)) {
        func(data);
        return;
    }

    wi.func = func;
    wi.data = data;
    wi.free = false;

    qemu_mutex_lock(&cpu->work_mutex);
    if (cpu->queued_work_first == NULL) {
        cpu->queued_work_first = &wi;
    } else {
        cpu->queued_work_last->next = &wi;
    }
    cpu->queued_work_last = &wi;
    wi.next = NULL;
    wi.done = false;
    qemu_mutex_unlock(&cpu->work_mutex);

    qemu_cpu_kick(cpu);
    while (!atomic_mb_read(&wi.done)) {
        CPUState *self_cpu = current_cpu;

        qemu_cond_wait(&qemu_work_cond, &qemu_global_mutex);
        current_cpu = self_cpu;
    }
}

void async_run_on_cpu(CPUState *cpu, void (*func)(void *data), void *data)
{
    struct qemu_work_item *wi;

    if (qemu_cpu_is_self(cpu)) {
        func(data);
        return;
    }

    wi = g_malloc0(sizeof(struct qemu_work_item));
    wi->func = func;
    wi->data = data;
    wi->free = true;

    qemu_mutex_lock(&cpu->work_mutex);
    if (cpu->queued_work_first == NULL) {
        cpu->queued_work_first = wi;
    } else {
        cpu->queued_work_last->next = wi;
    }
    cpu->queued_work_last = wi;
    wi->next = NULL;
    wi->done = false;
    qemu_mutex_unlock(&cpu->work_mutex);

    qemu_cpu_kick(cpu);
}

static void flush_queued_work(CPUState *cpu)
{
    struct qemu_work_item *wi;

    if (cpu->queued_work_first == NULL) {
        return;
    }

    qemu_mutex_lock(&cpu->work_mutex);
    while (cpu->queued_work_first != NULL) {
        wi = cpu->queued_work_first;
        cpu->queued_work_first = wi->next;
        if (!cpu->queued_work_first) {
            cpu->queued_work_last = NULL;
        }
        qemu_mutex_unlock(&cpu->work_mutex);
        wi->func(wi->data);
        qemu_mutex_lock(&cpu->work_mutex);
        if (wi->free) {
            g_free(wi);
        } else {
            atomic_mb_set(&wi->done, true);
        }
    }
    qemu_mutex_unlock(&cpu->work_mutex);
    qemu_cond_broadcast(&qemu_work_cond);
}

static void qemu_wait_io_event_common(CPUState *cpu)
{
    if (cpu->stop) {
        cpu->stop = false;
        cpu->stopped = true;
        qemu_cond_broadcast(&qemu_pause_cond);
    }
    flush_queued_work(cpu);
    cpu->thread_kicked = false;
}

static void qemu_tcg_wait_io_event(CPUState *cpu)
{
    while (all_cpu_threads_idle()) {
        qemu_cond_wait(cpu->halt_cond, &qemu_global_mutex);
    }

    while (iothread_requesting_mutex) {
        qemu_cond_wait(&qemu_io_proceeded_cond, &qemu_global_mutex);
    }

    CPU_FOREACH(cpu) {
        qemu_wait_io_event_common(cpu);
    }
}

static void tcg_exec_all(void);
static int tcg_exec_ready;

static void *qemu_tcg_cpu_thread_fn(void *arg)
{
    CPUState *cpu = arg;

    rcu_register_thread();

    qemu_mutex_lock_iothread();
    qemu_thread_get_self(cpu->thread);

    CPU_FOREACH(cpu) {
        cpu->thread_id = qemu_get_thread_id();
        cpu->created = true;
        cpu->can_do_io = 1;
    }
    qemu_cond_signal(&qemu_cpu_cond);

    /* wait for initial kick-off after machine start */
printf("%s, stopped=%d\n", __func__, first_cpu->stopped);
    while (first_cpu->stopped) {
printf("%s, wait halt_cond\n", __func__);
//        qemu_cond_wait(first_cpu->halt_cond, &qemu_global_mutex);
printf("%s, done halt_cond, stopped=%d\n", __func__, first_cpu->stopped);

        /* process any pending work */
	usleep(1000000);
    }

        CPU_FOREACH(cpu) {
            qemu_wait_io_event_common(cpu);
        }
    /* process any pending work */
    atomic_mb_set(&exit_request, 1);
printf("%s, ready ...\n", __func__);
    tcg_exec_ready = 1;

if (0) {
    while (1) {
        tcg_exec_all();

        qemu_tcg_wait_io_event(QTAILQ_FIRST(&cpus));
    }
}

    return NULL;
}

static void qemu_cpu_kick_thread(CPUState *cpu)
{
}

static void qemu_cpu_kick_no_halt(void)
{
    CPUState *cpu;
    /* Ensure whatever caused the exit has reached the CPU threads before
     * writing exit_request.
     */
    atomic_mb_set(&exit_request, 1);
    cpu = atomic_mb_read(&tcg_current_cpu);
    if (cpu) {
        cpu_exit(cpu);
    }
}

void qemu_cpu_kick(CPUState *cpu)
{
    qemu_cond_broadcast(cpu->halt_cond);
    if (tcg_enabled()) {
        qemu_cpu_kick_no_halt();
    } else {
        qemu_cpu_kick_thread(cpu);
    }
}

void qemu_cpu_kick_self(void)
{
    assert(current_cpu);
    qemu_cpu_kick_thread(current_cpu);
}

bool qemu_cpu_is_self(CPUState *cpu)
{
    return qemu_thread_is_self(cpu->thread);
}

bool qemu_in_vcpu_thread(void)
{
    return current_cpu && qemu_cpu_is_self(current_cpu);
}

static __thread bool iothread_locked = false;

bool qemu_mutex_iothread_locked(void)
{
    return iothread_locked;
}

void qemu_mutex_lock_iothread(void)
{
if (0) {
    atomic_inc(&iothread_requesting_mutex);
    /* In the simple case there is no need to bump the VCPU thread out of
     * TCG code execution.
     */
    if (!tcg_enabled() || qemu_in_vcpu_thread() ||
        !first_cpu || !first_cpu->created) {
        qemu_mutex_lock(&qemu_global_mutex);
        atomic_dec(&iothread_requesting_mutex);
    } else {
        if (qemu_mutex_trylock(&qemu_global_mutex)) {
            qemu_cpu_kick_no_halt();
            qemu_mutex_lock(&qemu_global_mutex);
        }
        atomic_dec(&iothread_requesting_mutex);
        qemu_cond_broadcast(&qemu_io_proceeded_cond);
    }
    iothread_locked = true;
}
}

void qemu_mutex_unlock_iothread(void)
{
if (0) {
    iothread_locked = false;
    qemu_mutex_unlock(&qemu_global_mutex);
}
}

static int all_vcpus_paused(void)
{
    CPUState *cpu;

    CPU_FOREACH(cpu) {
        if (!cpu->stopped) {
            return 0;
        }
    }

    return 1;
}

void pause_all_vcpus(void)
{
    CPUState *cpu;

    qemu_clock_enable(QEMU_CLOCK_VIRTUAL, false);
    CPU_FOREACH(cpu) {
        cpu->stop = true;
        qemu_cpu_kick(cpu);
    }

    if (qemu_in_vcpu_thread()) {
        cpu_stop_current();
        if (!kvm_enabled()) {
            CPU_FOREACH(cpu) {
                cpu->stop = false;
                cpu->stopped = true;
            }
            return;
        }
    }

    while (!all_vcpus_paused()) {
        qemu_cond_wait(&qemu_pause_cond, &qemu_global_mutex);
        CPU_FOREACH(cpu) {
            qemu_cpu_kick(cpu);
        }
    }
}

void cpu_resume(CPUState *cpu)
{
printf("%s\n", __func__);
    cpu->stop = false;
    cpu->stopped = false;
    qemu_cpu_kick(cpu);
}

void resume_all_vcpus(void)
{
    CPUState *cpu;

    qemu_clock_enable(QEMU_CLOCK_VIRTUAL, true);
    CPU_FOREACH(cpu) {
        cpu_resume(cpu);
    }
}

/* For temporary buffers for forming a name */
#define VCPU_THREAD_NAME_SIZE 16

#if 0
static void qemu_tcg_init_vcpu(CPUState *cpu)
{
    char thread_name[VCPU_THREAD_NAME_SIZE];
    static QemuCond *tcg_halt_cond;
    static QemuThread *tcg_cpu_thread;

    /* share a single thread for all cpus with TCG */
    if (!tcg_cpu_thread) {
        cpu->thread = g_malloc0(sizeof(QemuThread));
        cpu->halt_cond = g_malloc0(sizeof(QemuCond));
        qemu_cond_init(cpu->halt_cond);
        tcg_halt_cond = cpu->halt_cond;
        snprintf(thread_name, VCPU_THREAD_NAME_SIZE, "CPU %d/TCG",
                 cpu->cpu_index);
        qemu_thread_create(cpu->thread, thread_name, qemu_tcg_cpu_thread_fn,
                           cpu, QEMU_THREAD_JOINABLE);
#ifdef _WIN32
        cpu->hThread = qemu_thread_get_handle(cpu->thread);
#endif
        while (!cpu->created) {
            qemu_cond_wait(&qemu_cpu_cond, &qemu_global_mutex);
        }
        tcg_cpu_thread = cpu->thread;
    } else {
        cpu->thread = tcg_cpu_thread;
        cpu->halt_cond = tcg_halt_cond;
    }
}
#else
static void qemu_tcg_init_vcpu(CPUState *cpu)
{
    cpu->thread = g_malloc0(sizeof(QemuThread));
    cpu->halt_cond = g_malloc0(sizeof(QemuCond));
    qemu_cond_init(cpu->halt_cond);

    cpu->thread_id = qemu_get_thread_id();
    cpu->created = true;
    cpu->can_do_io = 1;

    tcg_exec_ready = 1;
}
#endif

void qemu_init_vcpu(CPUState *cpu)
{
    cpu->nr_cores = smp_cores;
    cpu->nr_threads = smp_threads;
    cpu->stopped = true;

    if (!cpu->as) {
        /* If the target cpu hasn't set up any address spaces itself,
         * give it the default one.
         */
        AddressSpace *as = address_space_init_shareable(cpu->memory,
                                                        "cpu-memory");
        cpu->num_ases = 1;
        cpu_address_space_init(cpu, as, 0);
    }

    qemu_tcg_init_vcpu(cpu);
}

void cpu_stop_current(void)
{
    if (current_cpu) {
        current_cpu->stop = false;
        current_cpu->stopped = true;
        cpu_exit(current_cpu);
        qemu_cond_broadcast(&qemu_pause_cond);
    }
}

int vm_stop(RunState state)
{
	return 0;
}

/* does a state transition even if the VM is already stopped,
   current state is forgotten forever */
int vm_stop_force_state(RunState state)
{
	return 0;
}

static int tcg_cpu_exec(CPUState *cpu)
{
    int ret;
#ifdef CONFIG_PROFILER
    int64_t ti;
#endif

#ifdef CONFIG_PROFILER
    ti = profile_getclock();
#endif
    ret = cpu_exec(cpu);
#ifdef CONFIG_PROFILER
    tcg_time += profile_getclock() - ti;
#endif
    return ret;
}

static void tcg_exec_all(void)
{
    int r;

    /* Account partial waits to QEMU_CLOCK_VIRTUAL.  */
    qemu_account_warp_timer();

    if (next_cpu == NULL) {
        next_cpu = first_cpu;
    }
    for (; next_cpu != NULL && !exit_request; next_cpu = CPU_NEXT(next_cpu)) {
        CPUState *cpu = next_cpu;

        qemu_clock_enable(QEMU_CLOCK_VIRTUAL,
                          (cpu->singlestep_enabled & SSTEP_NOTIMER) == 0);

        if (cpu_can_run(cpu)) {
            r = tcg_cpu_exec(cpu);
            if (r == EXCP_DEBUG) {
                cpu_handle_guest_debug(cpu);
                break;
            }
        } else if (cpu->stop || cpu->stopped) {
            break;
        }
    }

    /* Pairs with smp_wmb in qemu_cpu_kick.  */
    atomic_mb_set(&exit_request, 0);
}

void tcg_exec_once(void);
void tcg_exec_once(void)
{
    	if (tcg_exec_ready)
		tcg_exec_all();
}

void list_cpus(FILE *f, fprintf_function cpu_fprintf, const char *optarg)
{
    /* XXX: implement xxx_cpu_list for targets that still miss it */
#if defined(cpu_list)
    cpu_list(f, cpu_fprintf);
#endif
}

CpuInfoList *qmp_query_cpus(Error **errp)
{
    CpuInfoList *head = NULL, *cur_item = NULL;
    CPUState *cpu;

    CPU_FOREACH(cpu) {
        CpuInfoList *info;
#if defined(TARGET_I386)
        X86CPU *x86_cpu = X86_CPU(cpu);
        CPUX86State *env = &x86_cpu->env;
#elif defined(TARGET_PPC)
        PowerPCCPU *ppc_cpu = POWERPC_CPU(cpu);
        CPUPPCState *env = &ppc_cpu->env;
#elif defined(TARGET_SPARC)
        SPARCCPU *sparc_cpu = SPARC_CPU(cpu);
        CPUSPARCState *env = &sparc_cpu->env;
#elif defined(TARGET_MIPS)
        MIPSCPU *mips_cpu = MIPS_CPU(cpu);
        CPUMIPSState *env = &mips_cpu->env;
#elif defined(TARGET_TRICORE)
        TriCoreCPU *tricore_cpu = TRICORE_CPU(cpu);
        CPUTriCoreState *env = &tricore_cpu->env;
#endif

        cpu_synchronize_state(cpu);

        info = g_malloc0(sizeof(*info));
        info->value = g_malloc0(sizeof(*info->value));
        info->value->CPU = cpu->cpu_index;
        info->value->current = (cpu == first_cpu);
        info->value->halted = cpu->halted;
        info->value->qom_path = object_get_canonical_path(OBJECT(cpu));
        info->value->thread_id = cpu->thread_id;
#if defined(TARGET_I386)
        info->value->arch = CPU_INFO_ARCH_X86;
        info->value->u.x86.pc = env->eip + env->segs[R_CS].base;
#elif defined(TARGET_PPC)
        info->value->arch = CPU_INFO_ARCH_PPC;
        info->value->u.ppc.nip = env->nip;
#elif defined(TARGET_SPARC)
        info->value->arch = CPU_INFO_ARCH_SPARC;
        info->value->u.q_sparc.pc = env->pc;
        info->value->u.q_sparc.npc = env->npc;
#elif defined(TARGET_MIPS)
        info->value->arch = CPU_INFO_ARCH_MIPS;
        info->value->u.q_mips.PC = env->active_tc.PC;
#elif defined(TARGET_TRICORE)
        info->value->arch = CPU_INFO_ARCH_TRICORE;
        info->value->u.tricore.PC = env->PC;
#else
        info->value->arch = CPU_INFO_ARCH_OTHER;
#endif

        /* XXX: waiting for the qapi to support GSList */
        if (!cur_item) {
            head = cur_item = info;
        } else {
            cur_item->next = info;
            cur_item = info;
        }
    }

    return head;
}

void qmp_memsave(int64_t addr, int64_t size, const char *filename,
                 bool has_cpu, int64_t cpu_index, Error **errp)
{
    FILE *f;
    uint32_t l;
    CPUState *cpu;
    uint8_t buf[1024];
    int64_t orig_addr = addr, orig_size = size;

    if (!has_cpu) {
        cpu_index = 0;
    }

    cpu = qemu_get_cpu(cpu_index);
    if (cpu == NULL) {
        error_setg(errp, QERR_INVALID_PARAMETER_VALUE, "cpu-index",
                   "a CPU number");
        return;
    }

    f = fopen(filename, "wb");
    if (!f) {
        error_setg_file_open(errp, errno, filename);
        return;
    }

    while (size != 0) {
        l = sizeof(buf);
        if (l > size)
            l = size;
        if (cpu_memory_rw_debug(cpu, addr, buf, l, 0) != 0) {
            error_setg(errp, "Invalid addr 0x%016" PRIx64 "/size %" PRId64
                             " specified", orig_addr, orig_size);
            goto exit;
        }
        if (fwrite(buf, 1, l, f) != l) {
            error_setg(errp, QERR_IO_ERROR);
            goto exit;
        }
        addr += l;
        size -= l;
    }

exit:
    fclose(f);
}

void qmp_pmemsave(int64_t addr, int64_t size, const char *filename,
                  Error **errp)
{
    FILE *f;
    uint32_t l;
    uint8_t buf[1024];

    f = fopen(filename, "wb");
    if (!f) {
        error_setg_file_open(errp, errno, filename);
        return;
    }

    while (size != 0) {
        l = sizeof(buf);
        if (l > size)
            l = size;
        cpu_physical_memory_read(addr, buf, l);
        if (fwrite(buf, 1, l, f) != l) {
            error_setg(errp, QERR_IO_ERROR);
            goto exit;
        }
        addr += l;
        size -= l;
    }

exit:
    fclose(f);
}

void qmp_inject_nmi(Error **errp)
{
#if defined(TARGET_I386)
    CPUState *cs;

    CPU_FOREACH(cs) {
        X86CPU *cpu = X86_CPU(cs);

        if (!cpu->apic_state) {
            cpu_interrupt(cs, CPU_INTERRUPT_NMI);
        } else {
            apic_deliver_nmi(cpu->apic_state);
        }
    }
#else
    nmi_monitor_handle(monitor_get_cpu_index(), errp);
#endif
}

void dump_drift_info(FILE *f, fprintf_function cpu_fprintf)
{
}
