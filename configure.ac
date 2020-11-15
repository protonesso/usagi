AC_PREREQ([2.64])
AC_INIT([usagi], [alpha], [ataraxialinux@protonmail.com])

AM_INIT_AUTOMAKE([foreign])
AM_SANITY_CHECK
AM_CONDITIONAL(CROSS_COMPILATION, test x$cross_compiling = xyes)
AC_CANONICAL_HOST
AC_CONFIG_MACRO_DIRS([m4])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_PROG_AWK([awk])
AC_PROG_CC([clang])
AC_CHECK_TOOL([OBJDUMP],[llvm-objdump])
AC_CHECK_TOOL([AR],[llvm-ar])
AC_CHECK_TOOL([STRIP],[llvm-strip])
AC_CHECK_TOOL([RANLIB],[llvm-ranlib])
AM_PROG_INSTALL_STRIP
LT_PREREQ([2.2])
LT_INIT([dlopen shared])

AC_ARG_ENABLE(werror,
		[  --enable-werror	Use -Werror compiler flag],
		enable_werror=$enableval,
		enable_werror=no)

AX_CHECK_COMPILE_FLAG([-std=c2x], [
			CXXFLAGS="$CXXFLAGS -std=c2x"])
AX_CHECK_COMPILE_FLAG([-Wall], [
			CXXFLAGS="$CXXFLAGS -Wall"])

if test "x$enable_werror" = "xyes"; then
	AX_CHECK_COMPILE_FLAG([-Werror], [
				CXXFLAGS="$CXXFLAGS -Werror"])
fi

PKG_CHECK_MODULES([LIBZSTD], [libzstd >= 1.4.0])

AC_CONFIG_FILES([Makefile
		src/Makefile])
AC_OUTPUT
