#ifndef TQEMU_H
#define TQEMU_H

#include "qemu/compiler.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <inttypes.h>
#include <limits.h>
/* Put unistd.h before time.h as that triggers localtime_r/gmtime_r
 * function availability on recentish Mingw-w64 platforms. */
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <assert.h>
/* setjmp must be declared before sysemu/os-win32.h
 * because it is redefined there. */
#include <setjmp.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/uio.h>

#undef __linux__
#include <glib.h>
#include "qemu/typedefs.h"


#define QEMU_VMALLOC_ALIGN 4096

/* HOST_LONG_BITS is the size of a native pointer in bits. */
#if UINTPTR_MAX == UINT32_MAX
# define HOST_LONG_BITS 32
#elif UINTPTR_MAX == UINT64_MAX
# define HOST_LONG_BITS 64
#else
# error Unknown pointer size
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

/* Minimum function that returns zero only iff both values are zero.
 * Intended for use with unsigned values only. */
#ifndef MIN_NON_ZERO
#define MIN_NON_ZERO(a, b) ((a) == 0 ? (b) : \
                                ((b) == 0 ? (a) : (MIN(a, b))))
#endif

/* Round number down to multiple */
#define QEMU_ALIGN_DOWN(n, m) ((n) / (m) * (m))

/* Round number up to multiple */
#define QEMU_ALIGN_UP(n, m) QEMU_ALIGN_DOWN((n) + (m) - 1, (m))

#ifndef ROUND_UP
#define ROUND_UP(n,d) (((n) + (d) - 1) & -(d))
#endif

#ifndef DIV_ROUND_UP
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

extern void *rom_mem;
extern unsigned long rom_len;
extern void *ram_mem;
extern unsigned long ram_len;

const char *qemu_hw_version(void);
void *qemu_try_memalign(size_t alignment, size_t size);
void *qemu_memalign(size_t alignment, size_t size);
void *qemu_anon_ram_alloc(size_t size, uint64_t *align);
void qemu_vfree(void *ptr);
void qemu_anon_ram_free(void *ptr, size_t size);


//////////////////////////////////////////////
#define QEMU_VERSION "2.6.1"
#define QEMU_PKGVERSION ""
#define CONFIG_POSIX 1
#define CONFIG_LINUX 1
#define CONFIG_SOFTMMU 1
#define CONFIG_TCG_INTERPRETER 1

//////////////////////////////////////////////////
unsigned long crc32(unsigned long crc, const unsigned char *buf, unsigned int len);

////////////////////////////////////////////////
struct rcu_head {
	int nouse;
};
static inline void rcu_register_thread(void) {}
static inline void rcu_unregister_thread(void) {}
static inline void rcu_read_lock(void) {}
static inline void rcu_read_unlock(void) {}
static inline void rcu_after_fork(void) {}
#define call_rcu(head, func, field) do{(void)func;}while(0)
#define g_free_rcu(obj, field) do{}while(0)

////////////////////////////////////////////////////
typedef struct QemuMutex QemuMutex;
typedef struct QemuCond QemuCond;
typedef struct QemuSemaphore QemuSemaphore;
typedef struct QemuEvent QemuEvent;
typedef struct QemuThread QemuThread;

struct QemuMutex {
    int lock;
};

struct QemuCond {
    int cond;
};

struct QemuSemaphore {
    unsigned int count;
};

struct QemuEvent {
    unsigned value;
};

struct QemuThread {
    int thread;
};

#define QEMU_THREAD_JOINABLE 0
#define QEMU_THREAD_DETACHED 1

static inline void qemu_mutex_init(QemuMutex *mutex) {(void)mutex;}
static inline void qemu_mutex_destroy(QemuMutex *mutex) {(void)mutex;}
static inline void qemu_mutex_lock(QemuMutex *mutex) {(void)mutex;}
static inline int qemu_mutex_trylock(QemuMutex *mutex) {(void)mutex; return 1;}
static inline void qemu_mutex_unlock(QemuMutex *mutex) {(void)mutex;}

static inline void qemu_cond_init(QemuCond *cond) {(void)cond;}
static inline void qemu_cond_destroy(QemuCond *cond) {(void)cond;}

/*
 * IMPORTANT: The implementation does not guarantee that pthread_cond_signal
 * and pthread_cond_broadcast can be called except while the same mutex is
 * held as in the corresponding pthread_cond_wait calls!
 */
static inline void qemu_cond_signal(QemuCond *cond) {(void)cond;}
static inline void qemu_cond_broadcast(QemuCond *cond) {(void)cond;}
static inline void qemu_cond_wait(QemuCond *cond, QemuMutex *mutex) {(void)cond;}

static inline void qemu_sem_init(QemuSemaphore *sem, int init) {(void)sem; (void)init;}
static inline void qemu_sem_post(QemuSemaphore *sem) {(void)sem;}
static inline void qemu_sem_wait(QemuSemaphore *sem) {(void)sem;}
static inline int qemu_sem_timedwait(QemuSemaphore *sem, int ms) {(void)sem; (void)ms; return 0;}
static inline void qemu_sem_destroy(QemuSemaphore *sem) {(void)sem;}

static inline void qemu_event_init(QemuEvent *ev, bool init) {(void)ev; (void)init;}
static inline void qemu_event_set(QemuEvent *ev) {(void)ev;}
static inline void qemu_event_reset(QemuEvent *ev) {(void)ev;}
static inline void qemu_event_wait(QemuEvent *ev) {(void)ev; assert(0);}
static inline void qemu_event_destroy(QemuEvent *ev) {(void)ev;}

static inline void qemu_thread_create(QemuThread *thread, const char *name,
                        void *(*start_routine)(void *),
                        void *arg, int mode) {(void)name; (void)start_routine; (void)arg; (void)mode; thread->thread = 0x1234;}
static inline void *qemu_thread_join(QemuThread *thread) {(void)thread; assert(0);}
static inline void qemu_thread_get_self(QemuThread *thread) {(void)thread;}
static inline bool qemu_thread_is_self(QemuThread *thread) {(void)thread; return 1;}
static inline void qemu_thread_exit(void *retval) {(void)retval;}
static inline void qemu_thread_naming(bool enable) {(void)enable;}

struct Notifier;
static inline void qemu_thread_atexit_add(struct Notifier *notifier) {(void)notifier;}
static inline void qemu_thread_atexit_remove(struct Notifier *notifier) {(void)notifier;}

static inline int qemu_get_thread_id(void) {return 0x1234;}

/////////////////////////////////////////////////////
//hack OS dep
#define QEMU_MADV_DONTDUMP 0
#define QEMU_MADV_MERGEABLE 0
#define QEMU_MADV_HUGEPAGE 0
#define QEMU_MADV_DONTFORK 0
static inline int qemu_madvise(void *addr, size_t len, int advice) {(void)addr; (void)len; (void)advice; return 0;}

//////////////////////////////////////////////////////////
#include "qemu-common.h"

#endif
