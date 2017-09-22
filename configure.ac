#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([TQemu], [1.0], [byang1217@gmail.com])
AM_INIT_AUTOMAKE([subdir-objects foreign -Wno-portability -Wall -Werror])
AC_CONFIG_SRCDIR([tqemu.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_MAKE_SET

# Checks for libraries.

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([stdio.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

AC_CHECK_SIZEOF([int])
AC_CHECK_SIZEOF([long])

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([gettimeofday])

AC_ARG_WITH(target,
            [AS_HELP_STRING([--with-target=@<:@i386/arm@:>@],
                            [emu target [default=arm]])],
            [],
            [with_target=arm])

TQEMU_TARGET="$with_target"
AC_SUBST(TQEMU_TARGET)
AM_CONDITIONAL(TARGET_IS_I386, [test x"$TQEMU_TARGET" = xi386])
AM_CONDITIONAL(TARGET_IS_ARM, [test x"$TQEMU_TARGET" = xarm])

AC_ARG_WITH(host,
            [AS_HELP_STRING([--with-host=@<:@native/js@:>@],
                            [host to run tqemu [default=native]])],
            [],
            [with_host=native])

TQEMU_HOST="$with_host"
AC_SUBST(TQEMU_HOST)
AM_CONDITIONAL(HOST_IS_NATIVE, [test x"$TQEMU_HOST" = xnative])
AM_CONDITIONAL(HOST_IS_JS, [test x"$TQEMU_HOST" = xjs])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
