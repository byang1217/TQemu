#include "qemu/osdep.h"
#include "hw/boards.h"
#include "hw/hw.h"
#include "hw/qdev.h"
#include "net/net.h"
#include "monitor/monitor.h"
#include "sysemu/sysemu.h"
#include "qemu/timer.h"
#include "migration/migration.h"
#include "migration/postcopy-ram.h"
#include "qapi/qmp/qerror.h"
#include "qemu/error-report.h"
#include "qemu/queue.h"
#include "sysemu/cpus.h"
#include "exec/memory.h"
#include "qmp-commands.h"
#include "trace.h"
#include "qemu/bitops.h"
#include "qemu/iov.h"
#include "block/snapshot.h"
#include "block/qapi.h"
#include "qemu/cutils.h"

extern AddressSpace address_space_io;
extern AddressSpace address_space_memory;

ReplayMode replay_mode = REPLAY_MODE_NONE;

void qapi_event_send_device_deleted(bool has_device, const char *device, const char *path, Error **errp)
{
}

int vmstate_register_with_alias_id(DeviceState *dev, int instance_id,
                                   const VMStateDescription *vmsd,
                                   void *opaque, int alias_id,
                                   int required_for_version)
{
	return 0;
}

void vmstate_unregister(DeviceState *dev, const VMStateDescription *vmsd,
                        void *opaque)
{
}

void xen_modified_memory(ram_addr_t start, ram_addr_t length)
{
}

void xen_ram_alloc(ram_addr_t ram_addr, ram_addr_t size, MemoryRegion *mr,
                   Error **errp)
{
}

void migration_bitmap_extend(ram_addr_t old, ram_addr_t new)
{
}

#include "sysemu/replay.h"
int icount_align_option;
int replay_get_instructions(void)
{
    int res = 0;
    return res;
}

bool replay_checkpoint(ReplayCheckpoint checkpoint)
{
	return true;
}

int64_t replay_save_clock(ReplayClockKind kind, int64_t clock)
{
    return clock;
}

int64_t replay_read_clock(ReplayClockKind kind)
{
    error_report("REPLAY INTERNAL ERROR %d", __LINE__);
    exit(1);
}

bool replay_has_interrupt(void)
{
	return false;
}

bool replay_interrupt(void)
{
    return true;
}

bool replay_has_exception(void)
{
	return false;
}

bool replay_exception(void)
{
	return true;
}

void replay_finish(void)
{
}

void qemu_log_close(void)
{
}

/* Look up symbol for debugging purpose.  Returns "" if unknown. */
const char *lookup_symbol(target_ulong orig_addr)
{
	static char sym[32];
        target_ulong *ptr;
        hwaddr l, addr;
        MemoryRegion *mr;

	rcu_read_lock();
        l = sizeof(target_ulong);
        mr = address_space_translate(&address_space_memory, orig_addr, &addr, &l, false);
        assert(l == sizeof(target_ulong));
        ptr = qemu_get_ram_ptr(mr->ram_block,
                        memory_region_get_ram_addr(mr) + addr);
	rcu_read_unlock();
	snprintf(sym, sizeof(sym), "[%lx]:"TARGET_FMT_lx, (long)ptr, *ptr);
	return sym;
}

