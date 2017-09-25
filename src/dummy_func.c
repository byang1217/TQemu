#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

void abort(void);
int __dummy_ret0(void)
{
	return 0;
}

int __dummy_ret1(void)
{
        return 1;
}

void __dummy_abort(void)
{
        abort();
}

#define FUNC_ABORT(fname) \
        void fname(void) __attribute__ ((alias("__dummy_abort")))

#define FUNC_RET0(fname) \
        int fname(void) __attribute__ ((alias("__dummy_ret0")))

#define FUNC_RET1(fname) \
        int fname(void) __attribute__ ((alias("__dummy_ret1")))


FUNC_ABORT(qapi_event_send_device_deleted);
FUNC_ABORT(xen_ram_alloc);
FUNC_ABORT(replay_get_instructions);
FUNC_ABORT(replay_save_clock);
FUNC_ABORT(replay_read_clock);
FUNC_ABORT(qemu_put_be16);
FUNC_ABORT(qemu_put_be32);
FUNC_ABORT(qemu_put_be64);
FUNC_ABORT(qemu_get_be16);
FUNC_ABORT(qemu_get_be32);
FUNC_ABORT(qemu_get_be64);
FUNC_ABORT(qemu_get_byte);
FUNC_ABORT(gdb_exit);
FUNC_ABORT(arm_cpu_gdb_read_register);
FUNC_ABORT(arm_cpu_gdb_write_register);
FUNC_ABORT(x86_cpu_gdb_read_register);
FUNC_ABORT(x86_cpu_gdb_write_register);
FUNC_ABORT(x86_cpu_write_elf32_note);
FUNC_ABORT(x86_cpu_write_elf32_qemunote);
FUNC_ABORT(x86_cpu_write_elf64_note);
FUNC_ABORT(x86_cpu_write_elf64_qemunote);
FUNC_ABORT(arm_cpu_write_elf32_note);
FUNC_ABORT(arm_cpu_write_elf64_note);
FUNC_ABORT(blk_name);
FUNC_ABORT(blk_legacy_dinfo);
FUNC_ABORT(blk_attach_dev);
FUNC_ABORT(blk_detach_dev);
FUNC_ABORT(blk_by_name);
FUNC_ABORT(blockdev_auto_del);
FUNC_ABORT(qemu_chr_find);
FUNC_ABORT(net_hub_id_for_client);
FUNC_ABORT(net_hub_port_find);
FUNC_ABORT(event_notifier_set);
FUNC_ABORT(qemu_chr_add_handlers);
FUNC_ABORT(qemu_find_net_clients_except);
FUNC_ABORT(do_arm_semihosting);
FUNC_ABORT(qemu_system_shutdown_request);


FUNC_RET0(vmstate_register_with_alias_id);
FUNC_RET0(vmstate_unregister);
FUNC_RET0(replay_has_exception);
FUNC_RET0(replay_finish);
FUNC_RET0(qemu_log_close);
FUNC_RET0(replay_has_interrupt);
FUNC_RET0(migration_bitmap_extend);
FUNC_RET0(xen_modified_memory);
FUNC_RET0(semihosting_enabled);
FUNC_RET0(print_insn_arm);
FUNC_RET0(monitor_get_cpu_index);
FUNC_RET0(vmstate_register_ram_global);
FUNC_RET0(gdb_register_coprocessor);

FUNC_RET1(replay_checkpoint);
FUNC_RET1(replay_interrupt);
FUNC_RET1(replay_exception);

