AM_CFLAGS = -g -Werror -DNEED_CPU_H \
	-include ${top_builddir}/config.h \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/src \
	-I$(top_srcdir)/src/tcg \
	-I$(top_srcdir)/src/tcg/tci \
	-I$(top_srcdir) \
	-I$(top_srcdir)/qemu/ \
	-I$(top_srcdir)/qemu/include \
	-I$(top_srcdir)/qemu/tcg \
	-I$(top_srcdir)/qemu/tcg/tci

tqemu_SOURCES = \
		src/tqemu.c \
		src/dummy.c \
		src/dummy_func.c \
		src/osdep.c \
		src/qemu-timer.c \
		src/cpus.c \
		src/exec.c \
		src/cpu-exec.c \
		src/util/qemu-error.c

tqemu_SOURCES += \
		 glib/gmsg.c \
		 glib/ghash.c \
		 glib/gmem.c \
		 glib/gstrfuncs.c \
		 glib/gslist.c \
		 glib/glist.c \
		 glib/gstring.c \
		 glib/gbytes.c \
		 glib/gmain.c \
		 glib/gqueue.c

tqemu_SOURCES += \
		 qemu/qobject/qbool.c \
		 qemu/qobject/qdict.c \
		 qemu/qobject/qfloat.c \
		 qemu/qobject/qint.c \
		 qemu/qobject/qlist.c \
		 qemu/qobject/qnull.c \
		 qemu/qobject/qobject.c \
		 qemu/qobject/qstring.c \
		 qemu/cputlb.c \
		 qemu/memory.c \
		 qemu/translate-all.c \
		 qemu/ioport.c \
		 qemu/translate-common.c \
		 qemu/cpu-exec-common.c \
		 qemu/memory_mapping.c \
		 qemu/accel.c \
		 qemu/fpu/softfloat.c \
		 qemu/crypto/aes.c \
		 qemu/tci.c \
		 qemu/tcg/tcg-common.c \
		 qemu/tcg/tcg-op.c \
		 qemu/tcg/tcg.c \
		 qemu/tcg-runtime.c \
		 qemu/tcg/optimize.c \
		 qemu/util/module.c \
		 qemu/util/error.c \
		 qemu/util/bitops.c \
		 qemu/util/qemu-option.c \
		 qemu/util/qemu-config.c \
		 qemu/util/cutils.c \
		 qemu/util/bitmap.c \
		 qemu/util/host-utils.c \
		 qemu/util/notify.c \
		 qemu/qapi/qapi-visit-core.c \
		 qemu/qapi/string-output-visitor.c \
		 qemu/qapi/qapi-dealloc-visitor.c \
		 qemu/qapi/string-input-visitor.c \
		 qemu/qapi/qmp-input-visitor.c \
		 qemu/qapi/qmp-output-visitor.c \
		 qemu/qapi/opts-visitor.c \
		 qemu/qom/object.c \
		 qemu/qom/cpu.c \
		 qemu/qom/container.c \
		 qemu/qom/qom-qobject.c \
		 qemu/qom/object_interfaces.c \
		 qemu/hw/core/qdev.c \
		 qemu/hw/core/qdev-properties.c \
		 qemu/hw/core/sysbus.c \
		 qemu/hw/core/irq.c \
		 qemu/hw/core/qdev-properties-system.c \
		 qemu/hw/core/hotplug.c \
		 qemu/hw/core/fw-path-provider.c \
		 qemu/hw/core/machine.c

if TARGET_IS_ARM
AM_CFLAGS += -DTARGET_ARM=1 -DTARGET_NAME="arm" \
	-I$(top_srcdir)/src/gen-arm \
	-I$(top_srcdir)/src/target-arm \
	-I$(top_srcdir)/qemu/target-arm

endif

if TARGET_IS_I386
AM_CFLAGS += -DTARGET_I386=1 -DTARGET_NAME="i386" \
	-I$(top_srcdir)/src/gen-i386 \
	-I$(top_srcdir)/src/target-i386 \
	-I$(top_srcdir)/qemu/target-i386

tqemu_SOURCES += \
		 qemu/target-i386/cpu.c \
		 qemu/target-i386/mem_helper.c \
		 qemu/target-i386/excp_helper.c \
		 qemu/target-i386/svm_helper.c \
		 qemu/target-i386/helper.c \
		 qemu/target-i386/mpx_helper.c \
		 qemu/target-i386/cc_helper.c \
		 qemu/target-i386/seg_helper.c \
		 qemu/target-i386/bpt_helper.c \
		 qemu/target-i386/smm_helper.c \
		 qemu/target-i386/translate.c \
		 qemu/target-i386/fpu_helper.c \
		 qemu/target-i386/misc_helper.c \
		 qemu/target-i386/int_helper.c \
		 qemu/target-i386/arch_memory_mapping.c \
		 qemu/target-i386/machine.c \
		 qemu/hw/intc/apic.c \
		 qemu/hw/intc/apic_common.c \
		 qemu/hw/intc/ioapic.c \
		 qemu/hw/intc/ioapic_common.c \
		 qemu/hw/intc/i8259.c \
		 qemu/hw/intc/i8259_common.c \
		 qemu/hw/isa/isa-bus.c \
		 qemu/hw/i386/kvmvapic.c \
		 \
		 src/hw/i386/pc.c \
		 src/gen-i386/qapi-types.c \
		 src/gen-i386/qapi-visit.c
endif

if HOST_IS_JS
#workaround for emcc
AM_CFLAGS += -m32 \
	-Wno-incompatible-pointer-types-discards-qualifiers \
	-Wno-constant-conversion

bin_PROGRAMS = tqemu.bc tqemu.html
tqemu_bc_LDADD = -lm
tqemu_bc_SOURCES = $(tqemu_SOURCES)

tqemu.html: tqemu.bc
	echo "gen html & js ..."
	emcc -s TOTAL_MEMORY=0x8000000 $^ -o $@ --preload-file rom.bin

else
bin_PROGRAMS = tqemu
tqemu_LDADD = -lm
endif

AM_CPPFLAGS = $(AM_CFLAGS)
