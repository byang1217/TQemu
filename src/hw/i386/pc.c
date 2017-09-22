#include "qemu/osdep.h"
#include "hw/hw.h"
#include "hw/char/serial.h"
#include "hw/i386/pc.h"
#include "hw/i386/apic.h"
#include "hw/i386/topology.h"
#include "hw/sysbus.h"
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

void ioapic_init_gsi(GSIState *gsi_state, const char *parent_name)
{
    DeviceState *dev;
    SysBusDevice *d;
    unsigned int i;

    dev = qdev_create(NULL, "ioapic");
    if (parent_name) {
        object_property_add_child(object_resolve_path(parent_name, NULL),
                                  "ioapic", OBJECT(dev), NULL);
    }
    qdev_init_nofail(dev);
    d = SYS_BUS_DEVICE(dev);
    sysbus_mmio_map(d, 0, IO_APIC_DEFAULT_ADDRESS);

    for (i = 0; i < IOAPIC_NUM_PINS; i++) {
        gsi_state->ioapic_irq[i] = qdev_get_gpio_in(dev, i);
    }
}

void gsi_handler(void *opaque, int n, int level)
{
    GSIState *s = opaque;

    //DPRINTF("pc: %s GSI %d\n", level ? "raising" : "lowering", n);
    if (n < ISA_NUM_IRQS) {
        qemu_set_irq(s->i8259_irq[n], level);
    }
    qemu_set_irq(s->ioapic_irq[n], level);
}

static void pic_irq_request(void *opaque, int irq, int level)
{
    CPUState *cs = first_cpu;
    X86CPU *cpu = X86_CPU(cs);

//    DPRINTF("pic_irqs: %s irq %d\n", level? "raise" : "lower", irq);
    if (cpu->apic_state) {
        CPU_FOREACH(cs) {
            cpu = X86_CPU(cs);
            if (apic_accept_pic_intr(cpu->apic_state)) {
                apic_deliver_pic_intr(cpu->apic_state, level);
            }
        }
    } else {
        if (level) {
            cpu_interrupt(cs, CPU_INTERRUPT_HARD);
        } else {
            cpu_reset_interrupt(cs, CPU_INTERRUPT_HARD);
        }
    }
}


qemu_irq pc_allocate_cpu_irq(void)
{
    return qemu_allocate_irq(pic_irq_request, NULL, 0);
}


/* MSDOS compatibility mode FPU exception support */
static qemu_irq ferr_irq;

void pc_register_ferr_irq(qemu_irq irq)
{
    ferr_irq = irq;
}

/* XXX: add IGNNE support */
void cpu_set_ferr(CPUX86State *s)
{
    qemu_irq_raise(ferr_irq);
}

/* TSC handling */
uint64_t cpu_get_tsc(CPUX86State *env)
{
    return cpu_get_ticks();
}

int cpu_get_pic_interrupt(CPUX86State *env)
{
    X86CPU *cpu = x86_env_get_cpu(env);
    int intno;

    intno = apic_get_interrupt(cpu->apic_state);
    if (intno >= 0) {
        return intno;
    }
    /* read the irq from the PIC */
    if (!apic_accept_pic_intr(cpu->apic_state)) {
        return -1;
    }

    intno = pic_read_irq(isa_pic);
    return intno;
}

DeviceState *cpu_get_current_apic(void)
{
    if (current_cpu) {
        X86CPU *cpu = X86_CPU(current_cpu);
        return cpu->apic_state;
    } else {
        return NULL;
    }
}

static X86CPU *pc_new_cpu(const char *cpu_model, int64_t apic_id,
                          Error **errp)
{
    X86CPU *cpu = NULL;
    Error *local_err = NULL;

    cpu = cpu_x86_create(cpu_model, &local_err);
    if (local_err != NULL) {
        goto out;
    }

    object_property_set_int(OBJECT(cpu), apic_id, "apic-id", &local_err);
    object_property_set_bool(OBJECT(cpu), true, "realized", &local_err);

out:
    if (local_err) {
        error_propagate(errp, local_err);
        object_unref(OBJECT(cpu));
        cpu = NULL;
    }
    return cpu;
}

#define MAX_IDE_BUS 2
static const int ide_iobase[MAX_IDE_BUS] = { 0x1f0, 0x170 };
static const int ide_iobase2[MAX_IDE_BUS] = { 0x3f6, 0x376 };
static const int ide_irq[MAX_IDE_BUS] = { 14, 15 };

/* PC hardware initialisation */
static void pc_machine_init(MachineState *machine)
{
    MemoryRegion *system_memory = get_system_memory();
    MemoryRegion *system_io = get_system_io();
    int i;
    ISABus *isa_bus;
    qemu_irq *gsi;
    qemu_irq *i8259;
    GSIState *gsi_state;
    ISADevice *rtc_state;
    MemoryRegion *ram_memory;
    MemoryRegion *rom_memory;
    ram_addr_t lowmem;

    gsi_state = g_malloc0(sizeof(*gsi_state));
    gsi = qemu_allocate_irqs(gsi_handler, gsi_state, GSI_NUM_PINS);

    isa_bus = isa_bus_new(NULL, get_system_memory(), system_io,
		    &error_abort);
    isa_bus_irqs(isa_bus, gsi);

    i8259 = i8259_init(isa_bus, pc_allocate_cpu_irq());

    for (i = 0; i < ISA_NUM_IRQS; i++) {
        gsi_state->i8259_irq[i] = i8259[i];
    }
    g_free(i8259);
    ioapic_init_gsi(gsi_state, NULL);

    pc_register_ferr_irq(gsi[13]);

    /* init basic PC hardware */
#if 0
    pc_basic_device_init(isa_bus, gsi, &rtc_state, true,
                         (pcms->vmport != ON_OFF_AUTO_ON), 0x4);
    pc_nic_init(isa_bus, pci_bus);
#endif

// rom & mem
    MemoryRegion *rom;
    rom = g_malloc(sizeof(*rom));
    memory_region_init_ram_ptr(rom, NULL, "rom", rom_len, rom_mem);
    memory_region_set_readonly(rom, true);
//    memory_region_add_subregion_overlap(system_memory, (uint32_t)(-rom_len), rom, 1);
    memory_region_add_subregion_overlap(system_memory, 0xffff8000, rom, 1);

#if 0
    MemoryRegion *ram;
    ram = g_malloc(sizeof(*ram));
    memory_region_init_ram_ptr(ram, NULL, "ram", ram_len, ram_mem);
    memory_region_add_subregion(system_memory, 0, ram);
#endif
}

static void pc_machine_class_init(ObjectClass *oc, void *data)
{
    MachineClass *mc = MACHINE_CLASS(oc);

    mc->desc = "pc i386";
    mc->init = pc_machine_init;
    mc->max_cpus = 1;
    mc->is_default = 1;
}

static const TypeInfo pc_machine_type = {
    .name = MACHINE_TYPE_NAME("pc-machine-i386"),
    .parent = TYPE_MACHINE,
    .class_init = pc_machine_class_init,
};

static void pc_machine_type_init(void)
{
    type_register_static(&pc_machine_type);
}

type_init(pc_machine_type_init)

void hw_init(void)
{
	X86CPU *cpu = NULL;

	cpu = pc_new_cpu("qemu32", 0, NULL);
	object_unref(OBJECT(cpu));
}

