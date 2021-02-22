#  SATISY, a solver of the satisfiability problem of formulae in the
#  propositional calculus.
#  Copyright (C) 2017-present Paul Griffiths.
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 3, or (at your option)
#  any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; If not, see <https://www.gnu.org/licenses/>.

#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Satisfiability], [1.0.0])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/treenode.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_C99
AC_PROG_INSTALL

if test "x${ac_cv_prog_cc_c99}" = "xno"; then
    AC_MSG_ERROR([C99 compiler required])
fi

AX_COMPILER_FLAGS

# Checks for header files.
AC_CHECK_HEADERS([getopt.h stddef.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([getopt getopt_long memset])

OS=`uname -s`
AC_MSG_CHECKING([OS])
case "$OS" in
        FreeBSD*)
                AC_MSG_RESULT(FreeBSD)
                OS_FREEBSD="true"
                AM_CPPFLAGS="${AM_CPPFLAGS} -I/usr/local/include"
                AM_LDFLAGS="${AM_LDFLAGS} -L/usr/local/lib"
        ;;
        Darwin*)
                AC_MSG_RESULT(Darwin)
                OS_DARWIN="true"
                AC_DEFINE(_POSIX_C_SOURCE, [1], [Enable POSIX C source feature test macro])
                AC_DEFINE(_DARWIN_C_SOURCE, [1], [Enable full C features on OSX])
                AM_CPPFLAGS="${AM_CPPFLAGS} -I/usr/local/include -I/opt/local/include"
                AM_LDFLAGS="${AM_LDFLAGS} -L/usr/local/lib -L/opt/local/lib"
        ;;
        Linux*)
                AC_MSG_RESULT(Linux)
                AC_CHECK_LIB([dl], [dlopen], [])
                AC_DEFINE(_GNU_SOURCE, [1], [Enable GNU C source feature test macro])
                OS_LINUX="true"
        ;;
        *)
                AC_MSG_RESULT(no)
                AC_DEFINE(_POSIX_C_SOURCE, [1], [Enable POSIX C source feature test macro])
        ;;
esac
AM_CONDITIONAL([FREEBSD], [test "$OS_FREEBSD" = "true"])
AM_CONDITIONAL([DARWIN], [test "$OS_DARWIN" = "true"])
AM_CONDITIONAL([LINUX], [test "$OS_LINUX" = "true"])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
