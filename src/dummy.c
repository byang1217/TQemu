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
#include "sysemu/char.h"
#include "exec/gdbstub.h"

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
#if 0
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
#else
	return "";
#endif
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

///////////////////////////////////////////////
void qapi_event_send_device_deleted(bool has_device, const char *device, const char *path, Error **errp) {abort();}
void xen_ram_alloc(ram_addr_t ram_addr, ram_addr_t size, MemoryRegion *mr,
		Error **errp) {abort();}
int replay_get_instructions(void)  {abort();}
int64_t replay_save_clock(ReplayClockKind kind, int64_t clock) {abort();}
int64_t replay_read_clock(ReplayClockKind kind) {abort();}
void qemu_put_be16(QEMUFile *f, unsigned int v) {abort();}
void qemu_put_be32(QEMUFile *f, unsigned int v) {abort();}
void qemu_put_be64(QEMUFile *f, uint64_t v) {abort();}
unsigned int qemu_get_be16(QEMUFile *f) {abort();}
unsigned int qemu_get_be32(QEMUFile *f) {abort();}
uint64_t qemu_get_be64(QEMUFile *f) {abort();}
int qemu_get_byte(QEMUFile *f) {abort();}
void gdb_exit(CPUArchState *env, int code) {abort();}
int arm_cpu_gdb_read_register(CPUState *cs, uint8_t *mem_buf, int n) {abort();}
int arm_cpu_gdb_write_register(CPUState *cs, uint8_t *mem_buf, int n) {abort();}
int x86_cpu_gdb_read_register(CPUState *cs, uint8_t *mem_buf, int n) {abort();}
int x86_cpu_gdb_write_register(CPUState *cs, uint8_t *mem_buf, int n) {abort();}
int x86_cpu_write_elf32_note(WriteCoreDumpFunction f, CPUState *cs,
                             int cpuid, void *opaque) {abort();}
int x86_cpu_write_elf32_qemunote(WriteCoreDumpFunction f, CPUState *cs,
                                 void *opaque) {abort();}
int x86_cpu_write_elf64_note(WriteCoreDumpFunction f, CPUState *cs,
                             int cpuid, void *opaque) {abort();}
int x86_cpu_write_elf64_qemunote(WriteCoreDumpFunction f, CPUState *cs,
                                 void *opaque) {abort();}
int arm_cpu_write_elf32_note(WriteCoreDumpFunction f, CPUState *cs,
                             int cpuid, void *opaque) {abort();}
int arm_cpu_write_elf64_note(WriteCoreDumpFunction f, CPUState *cs,
                             int cpuid, void *opaque) {abort();}
const char *blk_name(BlockBackend *blk) {abort();}
DriveInfo *blk_legacy_dinfo(BlockBackend *blk) {abort();}
int blk_attach_dev(BlockBackend *blk, void *dev) {abort();}
void blk_detach_dev(BlockBackend *blk, void *dev) {abort();}
BlockBackend *blk_by_name(const char *name) {abort();}
void blockdev_auto_del(BlockBackend *blk) {abort();}
CharDriverState *qemu_chr_find(const char *name) {abort();}
int net_hub_id_for_client(NetClientState *nc, int *id) {abort();}
NetClientState *net_hub_port_find(int hub_id) {abort();}
int event_notifier_set(EventNotifier *e) {abort();}
void qemu_chr_add_handlers(CharDriverState *s,
                           IOCanReadHandler *fd_can_read,
                           IOReadHandler *fd_read,
                           IOEventHandler *fd_event,
                           void *opaque) {abort();}
int qemu_find_net_clients_except(const char *id, NetClientState **ncs,
                                 NetClientOptionsKind type, int max) {abort();}
target_ulong do_arm_semihosting(CPUARMState *env) {abort();}
void qemu_system_shutdown_request(void) {abort();}

/////////////////////return 0
int vmstate_register_with_alias_id(DeviceState *dev, int instance_id,
                                   const VMStateDescription *vmsd,
                                   void *opaque, int alias_id,
                                   int required_for_version) {return 0;}
void vmstate_unregister(DeviceState *dev, const VMStateDescription *vmsd,
                        void *opaque) {}
bool replay_has_exception(void) {return 0;}
void replay_finish(void) {}
void qemu_log_close(void) {}
bool replay_has_interrupt(void) {return 0;}
void migration_bitmap_extend(ram_addr_t old, ram_addr_t new) {}
void xen_modified_memory(ram_addr_t start, ram_addr_t length) {}
bool semihosting_enabled(void) {return 0;}
int print_insn_arm (bfd_vma pc, struct disassemble_info *info) {return 0;}
int monitor_get_cpu_index(void) {return 0;}
void vmstate_register_ram_global(MemoryRegion *mr) {}
void gdb_register_coprocessor(CPUState *cpu,
                              gdb_reg_cb get_reg, gdb_reg_cb set_reg,
                              int num_regs, const char *xml, int g_pos) {}


/////////////// return 1
bool replay_checkpoint(ReplayCheckpoint checkpoint) {return 1;}
bool replay_interrupt(void) {return 1;}
bool replay_exception(void) {return 1;}
