/*
 *  ARM helper routines
 *
 *  Copyright (c) 2005-2007 CodeSourcery, LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */
#include "qemu/osdep.h"
#include "cpu.h"
#include "exec/helper-proto.h"
#include "internals.h"
#include "exec/cpu_ldst.h"

uint64_t op_helper_func(uintptr_t func, tcg_target_ulong r0, tcg_target_ulong r1,
                                    tcg_target_ulong r2, tcg_target_ulong r3,
                                    tcg_target_ulong r5, tcg_target_ulong r6,
                                    tcg_target_ulong r7, tcg_target_ulong r8,
                                    tcg_target_ulong r9, tcg_target_ulong r10)
{
	uint64_t ret = 0;
	int func_type_ret = (func & 0x0f000000) >> 24;
	int func_type_p = (func & 0xf0000000) >> 28;
	func = ((uintptr_t)func & (~0xff000000)) + ((uintptr_t)op_helper_func & 0xff000000);
	void *func_p = (void *)func;

//	printf("func: %lx, func_type_ret=%d, func_type_p=%d\n", (long)func, func_type_ret, func_type_p);
	if (func_type_ret == 0) {
		if (func_type_p == 0) {
			void (*f)(void) = func_p;
			f();
		}else if (func_type_p == 1) {
			void (*f)(tcg_target_ulong) = func_p;
			f(r0);
		}else if (func_type_p == 2) {
			void (*f)(tcg_target_ulong, tcg_target_ulong) = func_p;
			f(r0, r1);
		}else if (func_type_p == 3) {
			void (*f)(tcg_target_ulong, tcg_target_ulong, tcg_target_ulong) = func_p;
			f(r0, r1, r2);
		}else if (func_type_p == 4) {
			void (*f)(tcg_target_ulong, tcg_target_ulong, tcg_target_ulong, tcg_target_ulong) = func_p;
			f(r0, r1, r2, r3);
		}else if (func_type_p == 5) {
			void (*f)(tcg_target_ulong, tcg_target_ulong, tcg_target_ulong, tcg_target_ulong, tcg_target_ulong) = func_p;
			f(r0, r1, r2, r3, r5);
		}else {
			abort();
		}
	}else if (func_type_ret == 4) {
		if (func_type_p == 0) {
			uint32_t (*f)(void) = func_p;
			ret = (uint32_t)f();
		}else if (func_type_p == 1) {
			uint32_t (*f)(tcg_target_ulong) = func_p;
			ret = (uint32_t)f(r0);
		}else if (func_type_p == 2) {
			uint32_t (*f)(tcg_target_ulong, tcg_target_ulong) = func_p;
			ret = (uint32_t)f(r0, r1);
		}else if (func_type_p == 3) {
			uint32_t (*f)(tcg_target_ulong, tcg_target_ulong, tcg_target_ulong) = func_p;
			ret = (uint32_t)f(r0, r1, r2);
		}else if (func_type_p == 4) {
			uint32_t (*f)(tcg_target_ulong, tcg_target_ulong, tcg_target_ulong, tcg_target_ulong) = func_p;
			ret = (uint32_t)f(r0, r1, r2, r3);
		}else if (func_type_p == 5) {
			uint32_t (*f)(tcg_target_ulong, tcg_target_ulong, tcg_target_ulong, tcg_target_ulong, tcg_target_ulong) = func_p;
			ret = (uint32_t)f(r0, r1, r2, r3, r5);
		}else {
			abort();
		}
	}else if (func_type_ret == 8) {
		if (func_type_p == 0) {
			uint64_t (*f)(void) = func_p;
			ret = (uint64_t)f();
		}else if (func_type_p == 1) {
			uint64_t (*f)(tcg_target_ulong) = func_p;
			ret = (uint64_t)f(r0);
		}else if (func_type_p == 2) {
			uint64_t (*f)(tcg_target_ulong, tcg_target_ulong) = func_p;
			ret = (uint64_t)f(r0, r1);
		}else if (func_type_p == 3) {
			uint64_t (*f)(tcg_target_ulong, tcg_target_ulong, tcg_target_ulong) = func_p;
			ret = (uint64_t)f(r0, r1, r2);
		}else if (func_type_p == 4) {
			uint64_t (*f)(tcg_target_ulong, tcg_target_ulong, tcg_target_ulong, tcg_target_ulong) = func_p;
			ret = (uint64_t)f(r0, r1, r2, r3);
		}else if (func_type_p == 5) {
			uint64_t (*f)(tcg_target_ulong, tcg_target_ulong, tcg_target_ulong, tcg_target_ulong, tcg_target_ulong) = func_p;
			ret = (uint64_t)f(r0, r1, r2, r3, r5);
		}else {
			abort();
		}
	}else {
		abort();
	}

	return ret;
}
