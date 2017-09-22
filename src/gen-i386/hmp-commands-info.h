

{
.name       = "version",
.args_type  = "",
.params     = "",
.help       = "show the version of QEMU",
.mhandler.cmd = hmp_info_version,
},


{
.name       = "network",
.args_type  = "",
.params     = "",
.help       = "show the network state",
.mhandler.cmd = hmp_info_network,
},


{
.name       = "chardev",
.args_type  = "",
.params     = "",
.help       = "show the character devices",
.mhandler.cmd = hmp_info_chardev,
},


{
.name       = "block",
.args_type  = "nodes:-n,verbose:-v,device:B?",
.params     = "[-n] [-v] [device]",
.help       = "show info of one block device or all block devices "
"(-n: show named nodes; -v: show details)",
.mhandler.cmd = hmp_info_block,
},


{
.name       = "blockstats",
.args_type  = "",
.params     = "",
.help       = "show block device statistics",
.mhandler.cmd = hmp_info_blockstats,
},


{
.name       = "block-jobs",
.args_type  = "",
.params     = "",
.help       = "show progress of ongoing block device operations",
.mhandler.cmd = hmp_info_block_jobs,
},


{
.name       = "registers",
.args_type  = "",
.params     = "",
.help       = "show the cpu registers",
.mhandler.cmd = hmp_info_registers,
},


#if defined(TARGET_I386)
{
.name       = "lapic",
.args_type  = "",
.params     = "",
.help       = "show local apic state",
.mhandler.cmd = hmp_info_local_apic,
},
#endif


#if defined(TARGET_I386)
{
.name       = "ioapic",
.args_type  = "",
.params     = "",
.help       = "show io apic state",
.mhandler.cmd = hmp_info_io_apic,
},
#endif


{
.name       = "cpus",
.args_type  = "",
.params     = "",
.help       = "show infos for each CPU",
.mhandler.cmd = hmp_info_cpus,
},


{
.name       = "history",
.args_type  = "",
.params     = "",
.help       = "show the command line history",
.mhandler.cmd = hmp_info_history,
},


#if defined(TARGET_I386) || defined(TARGET_PPC) || defined(TARGET_MIPS) || \
defined(TARGET_LM32) || (defined(TARGET_SPARC) && !defined(TARGET_SPARC64))
{
.name       = "irq",
.args_type  = "",
.params     = "",
.help       = "show the interrupts statistics (if available)",
#ifdef TARGET_SPARC
.mhandler.cmd = sun4m_hmp_info_irq,
#elif defined(TARGET_LM32)
.mhandler.cmd = lm32_hmp_info_irq,
#else
.mhandler.cmd = hmp_info_irq,
#endif
},


{
.name       = "pic",
.args_type  = "",
.params     = "",
.help       = "show i8259 (PIC) state",
#ifdef TARGET_SPARC
.mhandler.cmd = sun4m_hmp_info_pic,
#elif defined(TARGET_LM32)
.mhandler.cmd = lm32_hmp_info_pic,
#else
.mhandler.cmd = hmp_info_pic,
#endif
},
#endif


{
.name       = "pci",
.args_type  = "",
.params     = "",
.help       = "show PCI info",
.mhandler.cmd = hmp_info_pci,
},


#if defined(TARGET_I386) || defined(TARGET_SH4) || defined(TARGET_SPARC) || \
defined(TARGET_PPC) || defined(TARGET_XTENSA)
{
.name       = "tlb",
.args_type  = "",
.params     = "",
.help       = "show virtual to physical memory mappings",
.mhandler.cmd = hmp_info_tlb,
},
#endif


#if defined(TARGET_I386)
{
.name       = "mem",
.args_type  = "",
.params     = "",
.help       = "show the active virtual memory mappings",
.mhandler.cmd = hmp_info_mem,
},
#endif


{
.name       = "mtree",
.args_type  = "",
.params     = "",
.help       = "show memory tree",
.mhandler.cmd = hmp_info_mtree,
},


{
.name       = "jit",
.args_type  = "",
.params     = "",
.help       = "show dynamic compiler info",
.mhandler.cmd = hmp_info_jit,
},


{
.name       = "opcount",
.args_type  = "",
.params     = "",
.help       = "show dynamic compiler opcode counters",
.mhandler.cmd = hmp_info_opcount,
},


{
.name       = "kvm",
.args_type  = "",
.params     = "",
.help       = "show KVM information",
.mhandler.cmd = hmp_info_kvm,
},


{
.name       = "numa",
.args_type  = "",
.params     = "",
.help       = "show NUMA information",
.mhandler.cmd = hmp_info_numa,
},


{
.name       = "usb",
.args_type  = "",
.params     = "",
.help       = "show guest USB devices",
.mhandler.cmd = hmp_info_usb,
},


{
.name       = "usbhost",
.args_type  = "",
.params     = "",
.help       = "show host USB devices",
.mhandler.cmd = hmp_info_usbhost,
},


{
.name       = "profile",
.args_type  = "",
.params     = "",
.help       = "show profiling information",
.mhandler.cmd = hmp_info_profile,
},


{
.name       = "capture",
.args_type  = "",
.params     = "",
.help       = "show capture information",
.mhandler.cmd = hmp_info_capture,
},


{
.name       = "snapshots",
.args_type  = "",
.params     = "",
.help       = "show the currently saved VM snapshots",
.mhandler.cmd = hmp_info_snapshots,
},


{
.name       = "status",
.args_type  = "",
.params     = "",
.help       = "show the current VM status (running|paused)",
.mhandler.cmd = hmp_info_status,
},


{
.name       = "mice",
.args_type  = "",
.params     = "",
.help       = "show which guest mouse is receiving events",
.mhandler.cmd = hmp_info_mice,
},


{
.name       = "vnc",
.args_type  = "",
.params     = "",
.help       = "show the vnc server status",
.mhandler.cmd = hmp_info_vnc,
},


#if defined(CONFIG_SPICE)
{
.name       = "spice",
.args_type  = "",
.params     = "",
.help       = "show the spice server status",
.mhandler.cmd = hmp_info_spice,
},
#endif


{
.name       = "name",
.args_type  = "",
.params     = "",
.help       = "show the current VM name",
.mhandler.cmd = hmp_info_name,
},


{
.name       = "uuid",
.args_type  = "",
.params     = "",
.help       = "show the current VM UUID",
.mhandler.cmd = hmp_info_uuid,
},


{
.name       = "cpustats",
.args_type  = "",
.params     = "",
.help       = "show CPU statistics",
.mhandler.cmd = hmp_info_cpustats,
},


#if defined(CONFIG_SLIRP)
{
.name       = "usernet",
.args_type  = "",
.params     = "",
.help       = "show user network stack connection states",
.mhandler.cmd = hmp_info_usernet,
},
#endif


{
.name       = "migrate",
.args_type  = "",
.params     = "",
.help       = "show migration status",
.mhandler.cmd = hmp_info_migrate,
},


{
.name       = "migrate_capabilities",
.args_type  = "",
.params     = "",
.help       = "show current migration capabilities",
.mhandler.cmd = hmp_info_migrate_capabilities,
},


{
.name       = "migrate_parameters",
.args_type  = "",
.params     = "",
.help       = "show current migration parameters",
.mhandler.cmd = hmp_info_migrate_parameters,
},


{
.name       = "migrate_cache_size",
.args_type  = "",
.params     = "",
.help       = "show current migration xbzrle cache size",
.mhandler.cmd = hmp_info_migrate_cache_size,
},


{
.name       = "balloon",
.args_type  = "",
.params     = "",
.help       = "show balloon information",
.mhandler.cmd = hmp_info_balloon,
},


{
.name       = "qtree",
.args_type  = "",
.params     = "",
.help       = "show device tree",
.mhandler.cmd = hmp_info_qtree,
},


{
.name       = "qdm",
.args_type  = "",
.params     = "",
.help       = "show qdev device model list",
.mhandler.cmd = hmp_info_qdm,
},


{
.name       = "qom-tree",
.args_type  = "path:s?",
.params     = "[path]",
.help       = "show QOM composition tree",
.mhandler.cmd = hmp_info_qom_tree,
},


{
.name       = "roms",
.args_type  = "",
.params     = "",
.help       = "show roms",
.mhandler.cmd = hmp_info_roms,
},


{
.name       = "trace-events",
.args_type  = "",
.params     = "",
.help       = "show available trace-events & their state",
.mhandler.cmd = hmp_info_trace_events,
},


{
.name       = "tpm",
.args_type  = "",
.params     = "",
.help       = "show the TPM device",
.mhandler.cmd = hmp_info_tpm,
},


{
.name       = "memdev",
.args_type  = "",
.params     = "",
.help       = "show memory backends",
.mhandler.cmd = hmp_info_memdev,
},


{
.name       = "memory-devices",
.args_type  = "",
.params     = "",
.help       = "show memory devices",
.mhandler.cmd = hmp_info_memory_devices,
},


{
.name       = "iothreads",
.args_type  = "",
.params     = "",
.help       = "show iothreads",
.mhandler.cmd = hmp_info_iothreads,
},


{
.name       = "rocker",
.args_type  = "name:s",
.params     = "name",
.help       = "Show rocker switch",
.mhandler.cmd = hmp_rocker,
},


{
.name       = "rocker-ports",
.args_type  = "name:s",
.params     = "name",
.help       = "Show rocker ports",
.mhandler.cmd = hmp_rocker_ports,
},


{
.name       = "rocker-of-dpa-flows",
.args_type  = "name:s,tbl_id:i?",
.params     = "name [tbl_id]",
.help       = "Show rocker OF-DPA flow tables",
.mhandler.cmd = hmp_rocker_of_dpa_flows,
},


{
.name       = "rocker-of-dpa-groups",
.args_type  = "name:s,type:i?",
.params     = "name [type]",
.help       = "Show rocker OF-DPA groups",
.mhandler.cmd = hmp_rocker_of_dpa_groups,
},


#if defined(TARGET_S390X)
{
.name       = "skeys",
.args_type  = "addr:l",
.params     = "address",
.help       = "Display the value of a storage key",
.mhandler.cmd = hmp_info_skeys,
},
#endif


{
.name       = "dump",
.args_type  = "",
.params     = "",
.help       = "Display the latest dump status",
.mhandler.cmd = hmp_info_dump,
},



