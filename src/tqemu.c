#include "qemu/osdep.h"
#include "hw/hw.h"
#include "hw/boards.h"
#include "sysemu/accel.h"
#include "hw/char/serial.h"
#include "sysemu/cpus.h"
#include "exec/memory.h"
#include "exec/address-spaces.h"
#include "sysemu/arch_init.h"
#include "qemu/bitmap.h"
#include "qemu/config-file.h"
#include "qemu/error-report.h"
#include "qapi/visitor.h"
#include "qapi-visit.h"
#include "qom/cpu.h"

#include "prebuild/mem.h"

int use_rt_clock;
bool xen_allowed;
int singlestep = 0;
int max_cpus = 1;
int smp_cpus = 1;
int smp_cores = 1;
int smp_threads = 1;
ram_addr_t ram_size;
QEMUOptionRom option_rom[MAX_OPTION_ROMS];
int nb_option_roms;
static RunState current_run_state = RUN_STATE_PRELAUNCH;
int vga_interface_type = VGA_NONE;

static int debug_requested;
void qemu_system_debug_request(void)
{
    debug_requested = 1;
}
void gdb_set_stop_cpu(CPUState *cpu)
{
//    gdbserver_state->c_cpu = cpu;
//    gdbserver_state->g_cpu = cpu;
}


//////////////////////////////////////////////////////////////////
/***********************************************************/
/* main execution loop */

struct vm_change_state_entry {
    VMChangeStateHandler *cb;
    void *opaque;
    QLIST_ENTRY (vm_change_state_entry) entries;
};

static QLIST_HEAD(vm_change_state_head, vm_change_state_entry) vm_change_state_head;

VMChangeStateEntry *qemu_add_vm_change_state_handler(VMChangeStateHandler *cb,
                                                     void *opaque)
{
    VMChangeStateEntry *e;

    e = g_malloc0(sizeof (*e));

    e->cb = cb;
    e->opaque = opaque;
    QLIST_INSERT_HEAD(&vm_change_state_head, e, entries);
    return e;
}

void qemu_del_vm_change_state_handler(VMChangeStateEntry *e)
{
    QLIST_REMOVE (e, entries);
    g_free (e);
}

void vm_state_notify(int running, RunState state)
{
    VMChangeStateEntry *e, *next;

    QLIST_FOREACH_SAFE(e, &vm_change_state_head, entries, next) {
        e->cb(e->opaque, running, state);
    }
}

void vm_start(void)
{
	cpu_enable_ticks();
	current_run_state = RUN_STATE_RUNNING;
	vm_state_notify(1, RUN_STATE_RUNNING);
	resume_all_vcpus();
}

/* reset/shutdown handler */
typedef struct QEMUResetEntry {
    QTAILQ_ENTRY(QEMUResetEntry) entry;
    QEMUResetHandler *func;
    void *opaque;
} QEMUResetEntry;

static QTAILQ_HEAD(reset_handlers, QEMUResetEntry) reset_handlers =
    QTAILQ_HEAD_INITIALIZER(reset_handlers);

void qemu_register_reset(QEMUResetHandler *func, void *opaque)
{
    QEMUResetEntry *re = g_malloc0(sizeof(QEMUResetEntry));

    re->func = func;
    re->opaque = opaque;
    QTAILQ_INSERT_TAIL(&reset_handlers, re, entry);
}

void qemu_unregister_reset(QEMUResetHandler *func, void *opaque)
{
    QEMUResetEntry *re;

    QTAILQ_FOREACH(re, &reset_handlers, entry) {
        if (re->func == func && re->opaque == opaque) {
            QTAILQ_REMOVE(&reset_handlers, re, entry);
            g_free(re);
            return;
        }
    }
}

void qemu_devices_reset(void)
{
    QEMUResetEntry *re, *nre;

    /* reset all devices */
    QTAILQ_FOREACH_SAFE(re, &reset_handlers, entry, nre) {
        re->func(re->opaque);
    }
}

void qemu_system_reset_request(void)
{
	assert(0);
}

void qemu_register_suspend_notifier(Notifier *notifier)
{
}

void qemu_register_wakeup_notifier(Notifier *notifier)
{
}

void qemu_register_powerdown_notifier(Notifier *notifier)
{
}

static bool machine_init_done;
static NotifierList machine_init_done_notifiers =
    NOTIFIER_LIST_INITIALIZER(machine_init_done_notifiers);

void qemu_add_machine_init_done_notifier(Notifier *notify)
{
    notifier_list_add(&machine_init_done_notifiers, notify);
    if (machine_init_done) {
        notify->notify(notify, NULL);
    }
}

static void qemu_run_machine_init_done_notifiers(void)
{
    notifier_list_notify(&machine_init_done_notifiers, NULL);
    machine_init_done = true;
}


//////////////////////////////////////////////////////////////////
int runstate_is_running(void)
{
	return current_run_state == RUN_STATE_RUNNING;
}



/***********************************************************/
/* machine registration */

MachineState *current_machine;

QemuOpts *qemu_get_machine_opts(void)
{
    return qemu_find_opts_singleton("machine");
}

static MachineClass *find_machine(const char *name)
{
    GSList *el, *machines = object_class_get_list(TYPE_MACHINE, false);
    MachineClass *mc = NULL;

    for (el = machines; el; el = el->next) {
        MachineClass *temp = el->data;

        if (!strcmp(temp->name, name)) {
            mc = temp;
            break;
        }
        if (temp->alias &&
            !strcmp(temp->alias, name)) {
            mc = temp;
            break;
        }
    }

    g_slist_free(machines);
    return mc;
}

MachineClass *find_default_machine(void)
{
    GSList *el, *machines = object_class_get_list(TYPE_MACHINE, false);
    MachineClass *mc = NULL;

    for (el = machines; el; el = el->next) {
        MachineClass *temp = el->data;

        if (temp->is_default) {
            mc = temp;
            break;
        }
    }

    g_slist_free(machines);
    return mc;
}

MachineInfoList *qmp_query_machines(Error **errp)
{
    GSList *el, *machines = object_class_get_list(TYPE_MACHINE, false);
    MachineInfoList *mach_list = NULL;

    for (el = machines; el; el = el->next) {
        MachineClass *mc = el->data;
        MachineInfoList *entry;
        MachineInfo *info;

        info = g_malloc0(sizeof(*info));
        if (mc->is_default) {
            info->has_is_default = true;
            info->is_default = true;
        }

        if (mc->alias) {
            info->has_alias = true;
            info->alias = g_strdup(mc->alias);
        }

        info->name = g_strdup(mc->name);
        info->cpu_max = !mc->max_cpus ? 1 : mc->max_cpus;

        entry = g_malloc0(sizeof(*entry));
        entry->value = info;
        entry->next = mach_list;
        mach_list = entry;
    }

    g_slist_free(machines);
    return mach_list;
}

static int machine_help_func(QemuOpts *opts, MachineState *machine)
{
    ObjectProperty *prop;
    ObjectPropertyIterator iter;

    if (!qemu_opt_has_help_opt(opts)) {
        return 0;
    }

    object_property_iter_init(&iter, OBJECT(machine));
    while ((prop = object_property_iter_next(&iter))) {
        if (!prop->set) {
            continue;
        }

        error_printf("%s.%s=%s", MACHINE_GET_CLASS(machine)->name,
                     prop->name, prop->type);
        if (prop->description) {
            error_printf(" (%s)\n", prop->description);
        } else {
            error_printf("\n");
        }
    }

    return 1;
}

static QemuOptsList qemu_machine_opts = {
    .name = "machine",
    .implied_opt_name = "type",
    .merge_lists = true,
    .head = QTAILQ_HEAD_INITIALIZER(qemu_machine_opts.head),
    .desc = {
        /*
         * no elements => accept any
         * sanity checking will happen later
         * when setting machine properties
         */
        { }
    },
};

void hw_init(void);
void tcg_exec_once(void);
int qemu_bh_poll(void);
static void main_loop(void)
{
#if 0
	int count_per_loop = 10000;
	while(--count_per_loop > 0) {
		tcg_exec_once();
		qemu_clock_run_all_timers();
		qemu_bh_poll();
	}
#else
	int count_per_loop = 10000;
	int64_t start_time = qemu_clock_get_ms(QEMU_CLOCK_REALTIME);
	while (qemu_clock_get_ms(QEMU_CLOCK_REALTIME) - start_time < 500) {
		while(--count_per_loop > 0) {
			tcg_exec_once();
			qemu_clock_run_all_timers();
			qemu_bh_poll();
		}
	}
#endif
}
int main(int argc, char **argv)
{
#ifdef __EMSCRIPTEN__
	//workaround
	dup2(1, 2);  //redirects stderr to stdout below this line.
#endif
	/* make stdin and stdout unbuffered */
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	qemu_logfile = stdout;

	MachineClass *machine_class;

	module_call_init(MODULE_INIT_QOM);
	qemu_add_opts(&qemu_machine_opts);
	module_call_init(MODULE_INIT_OPTS);

	machine_class = find_default_machine();
	//machine_class = select_machine();
	current_machine = MACHINE(object_new(object_class_get_name(
					OBJECT_CLASS(machine_class))));
	if (machine_help_func(qemu_get_machine_opts(), current_machine)) {
		exit(0);
	}
	object_property_add_child(object_get_root(), "machine",
			OBJECT(current_machine), &error_abort);

	cpu_exec_init_all();

	page_size_init();

	configure_accelerator(current_machine);

	init_clocks();

	machine_class->init(current_machine);

	qemu_register_reset(qbus_reset_all_fn, sysbus_get_default());

	qemu_run_machine_init_done_notifiers();

	qemu_devices_reset();

	vm_start();

#if 0
	CPUState *cs = first_cpu;
	cs->singlestep_enabled = 1;
#endif

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(main_loop, 1000, 0);
#else
	while(1) {
		main_loop();
		usleep(1000);
	}
#endif
}

void *rom_ptr(hwaddr addr)
{
	return NULL;
}
