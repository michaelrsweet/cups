dnl
dnl Common configuration stuff for CUPS.
dnl
dnl Copyright © 2007-2018 by Apple Inc.
dnl Copyright © 1997-2007 by Easy Software Products, all rights reserved.
dnl
dnl Licensed under Apache License v2.0.  See the file "LICENSE" for more
dnl information.
dnl

dnl Set the name of the config header file...
AC_CONFIG_HEADER(config.h)

dnl Version number information...
CUPS_VERSION="AC_PACKAGE_VERSION"
CUPS_REVISION=""
CUPS_BUILD="cups-$CUPS_VERSION"

AC_ARG_WITH(cups_build, [  --with-cups-build       set "cups-config --build" string ],
	CUPS_BUILD="$withval")

AC_SUBST(CUPS_VERSION)
AC_SUBST(CUPS_REVISION)
AC_SUBST(CUPS_BUILD)
AC_DEFINE_UNQUOTED(CUPS_SVERSION, "AC_PACKAGE_NAME v$CUPS_VERSION$CUPS_REVISION")
AC_DEFINE_UNQUOTED(CUPS_MINIMAL, "AC_PACKAGE_NAME/$CUPS_VERSION$CUPS_REVISION")

dnl Default compiler flags...
CFLAGS="${CFLAGS:=}"
CPPFLAGS="${CPPFLAGS:=}"
CXXFLAGS="${CXXFLAGS:=}"
LDFLAGS="${LDFLAGS:=}"

dnl Checks for programs...
AC_PROG_AWK
AC_PROG_CC(clang cc gcc)
AC_PROG_CPP
AC_PROG_CXX(clang++ c++ g++)
AC_PROG_RANLIB
AC_PATH_PROG(AR,ar)
AC_PATH_PROG(CHMOD,chmod)
AC_PATH_PROG(GZIP,gzip)
AC_PATH_PROG(LD,ld)
AC_PATH_PROG(LN,ln)
AC_PATH_PROG(MKDIR,mkdir)
AC_PATH_PROG(MV,mv)
AC_PATH_PROG(RM,rm)
AC_PATH_PROG(RMDIR,rmdir)
AC_PATH_PROG(SED,sed)
AC_PATH_PROG(XDGOPEN,xdg-open)
if test "x$XDGOPEN" = x; then
	CUPS_HTMLVIEW="htmlview"
else
	CUPS_HTMLVIEW="$XDGOPEN"
fi
AC_SUBST(CUPS_HTMLVIEW)

AC_MSG_CHECKING(for install-sh script)
INSTALL="`pwd`/install-sh"
AC_SUBST(INSTALL)
AC_MSG_RESULT(using $INSTALL)

if test "x$AR" = x; then
	AC_MSG_ERROR([Unable to find required library archive command.])
fi
if test "x$CC" = x; then
	AC_MSG_ERROR([Unable to find required C compiler command.])
fi

dnl Static library option...
INSTALLSTATIC=""
AC_ARG_ENABLE(static, [  --enable-static         install static libraries])

if test x$enable_static = xyes; then
	echo Installing static libraries...
	INSTALLSTATIC="installstatic"
fi

AC_SUBST(INSTALLSTATIC)

dnl Check for pkg-config, which is used for some other tests later on...
AC_PATH_TOOL(PKGCONFIG, pkg-config)

dnl Check for libraries...
AC_SEARCH_LIBS(abs, m, AC_DEFINE(HAVE_ABS))
AC_SEARCH_LIBS(crypt, crypt)
AC_SEARCH_LIBS(fmod, m)
AC_SEARCH_LIBS(getspent, sec gen)

LIBMALLOC=""
AC_ARG_ENABLE(mallinfo, [  --enable-mallinfo       build with malloc debug logging])

if test x$enable_mallinfo = xyes; then
	SAVELIBS="$LIBS"
	LIBS=""
	AC_SEARCH_LIBS(mallinfo, malloc, AC_DEFINE(HAVE_MALLINFO))
	LIBMALLOC="$LIBS"
	LIBS="$SAVELIBS"
fi

AC_SUBST(LIBMALLOC)

dnl Check for libpaper support...
AC_ARG_ENABLE(libpaper, [  --enable-libpaper       build with libpaper support])

if test x$enable_libpaper = xyes; then
	AC_CHECK_LIB(paper,systempapername,
		AC_DEFINE(HAVE_LIBPAPER)
		LIBPAPER="-lpaper",
		LIBPAPER="")
else
	LIBPAPER=""
fi
AC_SUBST(LIBPAPER)

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADER(langinfo.h,AC_DEFINE(HAVE_LANGINFO_H))
AC_CHECK_HEADER(stdint.h,AC_DEFINE(HAVE_STDINT_H))
AC_CHECK_HEADER(string.h,AC_DEFINE(HAVE_STRING_H))
AC_CHECK_HEADER(sys/param.h,AC_DEFINE(HAVE_SYS_PARAM_H))

dnl Checks for iconv.h and iconv_open
AC_CHECK_HEADER(iconv.h,
	SAVELIBS="$LIBS"
	LIBS=""
	AC_SEARCH_LIBS(iconv_open,iconv,
		AC_DEFINE(HAVE_ICONV_H)
		SAVELIBS="$SAVELIBS $LIBS")
	AC_SEARCH_LIBS(libiconv_open,iconv,
		AC_DEFINE(HAVE_ICONV_H)
		SAVELIBS="$SAVELIBS $LIBS")
	LIBS="$SAVELIBS")

dnl Checks for statfs and its many headers...
AC_CHECK_HEADER(sys/mount.h,AC_DEFINE(HAVE_SYS_MOUNT_H))
AC_CHECK_HEADER(sys/statfs.h,AC_DEFINE(HAVE_SYS_STATFS_H))
AC_CHECK_HEADER(sys/statvfs.h,AC_DEFINE(HAVE_SYS_STATVFS_H))
AC_CHECK_HEADER(sys/vfs.h,AC_DEFINE(HAVE_SYS_VFS_H))
AC_CHECK_FUNCS(statfs statvfs)

dnl Checks for string functions.
AC_CHECK_FUNCS(strdup strlcat strlcpy)
if test "$host_os_name" = "hp-ux" -a "$host_os_version" = "1020"; then
	echo Forcing snprintf emulation for HP-UX.
else
	AC_CHECK_FUNCS(snprintf vsnprintf)
fi

dnl Check for random number functions...
AC_CHECK_FUNCS(random lrand48 arc4random)

dnl Check for vsyslog function.
AC_CHECK_FUNCS(vsyslog)

dnl Checks for signal functions.
case "$host_os_name" in
	linux* | gnu*)
		# Do not use sigset on Linux or GNU HURD
		;;
	*)
		# Use sigset on other platforms, if available
		AC_CHECK_FUNCS(sigset)
		;;
esac

AC_CHECK_FUNCS(sigaction)

dnl Checks for wait functions.
AC_CHECK_FUNCS(waitpid wait3)

dnl Check for posix_spawn
AC_CHECK_FUNCS(posix_spawn)

dnl Check for getgrouplist
AC_CHECK_FUNCS(getgrouplist)

dnl See if the tm structure has the tm_gmtoff member...
AC_MSG_CHECKING(for tm_gmtoff member in tm structure)
AC_TRY_COMPILE([#include <time.h>],[struct tm t;
	int o = t.tm_gmtoff;],
	AC_MSG_RESULT(yes)
	AC_DEFINE(HAVE_TM_GMTOFF),
	AC_MSG_RESULT(no))

dnl See if the stat structure has the st_gen member...
AC_MSG_CHECKING(for st_gen member in stat structure)
AC_TRY_COMPILE([#include <sys/stat.h>],[struct stat t;
	int o = t.st_gen;],
	AC_MSG_RESULT(yes)
	AC_DEFINE(HAVE_ST_GEN),
	AC_MSG_RESULT(no))

dnl ZLIB
INSTALL_GZIP=""
LIBZ=""
AC_CHECK_HEADER(zlib.h,
    AC_CHECK_LIB(z, gzgets,
	AC_DEFINE(HAVE_LIBZ)
	LIBZ="-lz"
	LIBS="$LIBS -lz"
	AC_CHECK_LIB(z, inflateCopy, AC_DEFINE(HAVE_INFLATECOPY))
	if test "x$GZIP" != z; then
		INSTALL_GZIP="-z"
	fi))
AC_SUBST(INSTALL_GZIP)
AC_SUBST(LIBZ)

dnl Flags for "ar" command...
case $host_os_name in
        darwin* | *bsd*)
                ARFLAGS="-rcv"
                ;;
        *)
                ARFLAGS="crvs"
                ;;
esac

AC_SUBST(ARFLAGS)

dnl Prep libraries specifically for cupsd...
SERVERLIBS=""
AC_SUBST(SERVERLIBS)

dnl Extra platform-specific libraries...
case $host_os_name in
        darwin*)
                SERVERLIBS="$SERVERLIBS -framework IOKit -weak_framework ApplicationServices"
                LIBS="-framework SystemConfiguration -framework CoreFoundation -framework Security $LIBS"

		dnl Check for framework headers...
		AC_CHECK_HEADER(ApplicationServices/ApplicationServices.h,AC_DEFINE(HAVE_APPLICATIONSERVICES_H))
		AC_CHECK_HEADER(CoreFoundation/CoreFoundation.h,AC_DEFINE(HAVE_COREFOUNDATION_H))
		AC_CHECK_HEADER(CoreFoundation/CFPriv.h,AC_DEFINE(HAVE_CFPRIV_H))
		AC_CHECK_HEADER(CoreFoundation/CFBundlePriv.h,AC_DEFINE(HAVE_CFBUNDLEPRIV_H))

		dnl Check for dynamic store function...
		AC_CHECK_FUNCS(SCDynamicStoreCopyComputerName)

		dnl Check for notify_post support
		AC_CHECK_HEADER(notify.h,AC_DEFINE(HAVE_NOTIFY_H))
		AC_CHECK_FUNCS(notify_post)

		AC_CHECK_HEADER(Security/SecBasePriv.h,AC_DEFINE(HAVE_SECBASEPRIV_H))
                ;;
esac

dnl Check for build components
COMPONENTS="all"

AC_ARG_WITH(components, [  --with-components       set components to build:
			    - "all" (default) builds everything
			    - "core" builds libcups and IPP tools],
	COMPONENTS="$withval")

case "$COMPONENTS" in
	all)
		BUILDDIRS="berkeley scheduler systemv conf data locale man"
		;;

	core)
		BUILDDIRS="data locale"
		;;

	*)
		AC_MSG_ERROR([Bad build component "$COMPONENT" specified!])
		;;
esac

AC_SUBST(BUILDDIRS)
