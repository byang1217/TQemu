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
#include "sysemu/replay.h"

extern AddressSpace address_space_io;
extern AddressSpace address_space_memory;

ReplayMode replay_mode = REPLAY_MODE_NONE;
int icount_align_option;
bool msi_nonbroken;
CharDriverState *parallel_hds[MAX_PARALLEL_PORTS];
bool gdb_has_xml;

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
	//snprintf(sym, sizeof(sym), "[%lx]:"TARGET_FMT_lx, (long)ptr, *ptr);
	snprintf(sym, sizeof(sym), "ins:"TARGET_FMT_lx, *ptr);
	return sym;
}

const VMStateInfo vmstate_info_uint8 = {
    .name = "uint8",
};

const VMStateInfo vmstate_info_int32 = {
    .name = "int32",
};

const VMStateInfo vmstate_info_uint32 = {
    .name = "uint32",
};

const VMStateInfo vmstate_info_int64 = {
    .name = "int64",
};

const VMStateInfo vmstate_info_uint64 = {
    .name = "uint64",
};

const VMStateInfo vmstate_info_uint16 = {
    .name = "uint16",
};

const VMStateInfo vmstate_info_unused_buffer = {
    .name = "unused_buffer",
};

const VMStateInfo vmstate_info_bool = {
    .name = "bool",
};

const VMStateInfo vmstate_info_timer = {
    .name = "timer",
};

const VMStateInfo vmstate_info_int32_le = {
    .name = "int32 le",
};

const VMStateInfo vmstate_info_float64 = {
    .name = "float64",
};





