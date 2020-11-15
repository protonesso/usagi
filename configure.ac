AC_PREREQ([2.64])
AC_INIT([usagi], [alpha], [ataraxialinux@protonmail.com])

AM_INIT_AUTOMAKE([foreign dist-xz])
AM_SANITY_CHECK
AM_CONDITIONAL(CROSS_COMPILATION, test x$cross_compiling = xyes)
AC_CANONICAL_HOST
AC_CONFIG_MACRO_DIRS([m4])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_PROG_AWK([awk])
AC_PROG_CC([clang cc])
AC_PROG_CXX([clang++ c++])
AC_CHECK_TOOL([OBJDUMP],[llvm-objdump])
AC_CHECK_TOOL([AR],[llvm-ar])
AC_CHECK_TOOL([STRIP],[llvm-strip])
AC_CHECK_TOOL([RANLIB],[llvm-ranlib])
AM_PROG_INSTALL_STRIP
LT_PREREQ([2.2])
LT_INIT([dlopen shared])

CPPFLAGS="$CPPFLAGS -D_XOPEN_SOURCE=700"
CFLAGS="$CFLAGS -std=c2x"
CXXFLAGS="$CXXFLAGS -std=c++20"

AC_ARG_ENABLE(werror,
		[  --enable-werror         Use -Werror compiler flag],
		enable_werror=$enableval,
		enable_werror=no)

AX_CHECK_COMPILE_FLAG([-Wall],
		[CFLAGS="$CFLAGS -Wall" && CXXFLAGS="$CXXFLAGS -Wall"],
		[AC_MSG_ERROR([C compiler does not accept -Wall])])
AX_CHECK_COMPILE_FLAG([-Wextra],
		[CFLAGS="$CFLAGS -Wextra" && CXXFLAGS="$CXXFLAGS -Wextra"],
		[AC_MSG_ERROR([C compiler does not accept -Wextra])])
AX_CHECK_COMPILE_FLAG([-Wunused-function],
		[CFLAGS="$CFLAGS -Wunused-function" && CXXFLAGS="$CXXFLAGS -Wunused-function"],
		[AC_MSG_ERROR([C compiler does not accept -Wunused-function])])
AX_CHECK_COMPILE_FLAG([-Wunused-label],
		[CFLAGS="$CFLAGS -Wunused-label" && CXXFLAGS="$CXXFLAGS -Wunused-label"],
		[AC_MSG_ERROR([C compiler does not accept -Wunused-label])])
AX_CHECK_COMPILE_FLAG([-Wunused-value],
		[CFLAGS="$CFLAGS -Wunused-value" && CXXFLAGS="$CXXFLAGS -Wunused-value"],
		[AC_MSG_ERROR([C compiler does not accept -Wunused-value])])
AX_CHECK_COMPILE_FLAG([-Wunused-variable],
		[CFLAGS="$CFLAGS -Wunused-variable" && CXXFLAGS="$CXXFLAGS -Wunused-variable"],
		[AC_MSG_ERROR([C compiler does not accept -Wunused-variable])])
if test "x$enable_werror" = "xyes"; then
	AX_CHECK_COMPILE_FLAG([-Werror],
			[CFLAGS="$CFLAGS -Werror" && CXXFLAGS="$CXXFLAGS -Werror"],
			[AC_MSG_ERROR([C compiler does not accept -Werror])])
fi
AX_CHECK_COMPILE_FLAG([-pedantic],
		[CFLAGS="$CFLAGS -pedantic" && CXXFLAGS="$CXXFLAGS -pedantic"],
		[AC_MSG_ERROR([C compiler does not accept -pedantic])])

AC_CHECK_HEADERS(sys/sysmacros.h stdbool.h)

PKG_CHECK_MODULES([LIBSQLITE], [sqlite3 >= 3.33.0])
PKG_CHECK_MODULES([LIBZSTD], [libzstd >= 1.4.5])

AC_CONFIG_FILES([Makefile
		src/Makefile])
AC_OUTPUT
