# TQemu
Tiny Qemu run on any host (including JS/browser)
To support any host, it cannot use any OS specific API. Libc and Libm might be the only libs which it can use. For JS/browser, we can use emscripten solution.

# Demo
https://byang1217.github.io/tqemu.html

# How to build Native version
mkdir out; cd out;
../TQemu/configure
make

# How to build JS version to run on web browser
mkdir out
emconfigure ../TQemu/configure --with-host=js
make

# Technical Notes
## Change Qemu to single thread
Originally, Qemu is multithread which has TCG thread and IO thread (and rcu update thread). To change it into single thread mode, it needs to handle TCG and IO in a mainloop.

## TCG dead lock issue
when exec loop in guest VM which waits for HW status change, single thread will cause dead lock. Add max exec ins count to exit dead loop temporarily.

## TCG Debug tips

	try to force tcg to gen TB every single instructure

	enable tcg_dump_ops in tcg_gen_code()

	trace TB exec in cpu_tb_exec()

	trace tci in tcg_qemu_tb_exec()

## Optimize Linux boot
The kernel decompressing is too slow. Use XIP to get rid of kernel decompressing and relocating

The initrd decompressing is too slow. Hacking build script not to compress initrd. refer to patch: prebuild/linux-3.18_speed_up_initrd.patch

## Linux XIP issue
Linux kernel (3.18) has as a MMU config bug which does not set Translate Table correct for ro_data and init_data. This bug cause kernel boot OOP.

Translate table is set in the head.S by below code:

Get base from head.S code (r4) : mcr     p15, 0, r4, c2, c0, 0           @ load page table pointer

But it is cleared by mistake in prepare_page_table() function.

refer to patch: prebuild/linux-3.18_fix_xip_oop.patch


## JS/Browser issue
emscripten is a LLVM backend which can transfer LLVM byte code into javascript and run it in browser.

emcc has func pointer limitation, which needs function parameter number being matched strictly. 

	g_list cmp function needs to be reworked.

	all op helper functions need to be fixed

emcc has memory alignment limitation, which cannot access unaligned memory.
	
	add __attribute__((aligned(1))) to fix unaligned access issue.

It can find corresponding C functions in JS code if set -O0 in CFLAGS

Sometimes, it needs to extend the exceptions levels to find error code. (change Error.stackTraceLimit by JS console)

