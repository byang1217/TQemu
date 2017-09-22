AM_CPPFLAGS = -DTARGET_I386=1 -DTARGET_NAME="i386" \
	-g -O0 -DNEED_CPU_H -Iinclude/tqemu -Iinclude -Itcg -Itcg/tci/ -Itarget-i386/

AM_CFLAGS = -DTARGET_I386=1 -DTARGET_NAME="i386" \
	-g -O0 -DNEED_CPU_H -Iinclude/tqemu -Iinclude -Itcg -Itcg/tci/ -Itarget-i386/

bin_PROGRAMS = tqemu
tqemu_SOURCES = main.c ghash.c tci.c
tqemu_LDFLAGS = -static
