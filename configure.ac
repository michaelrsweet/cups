dnl
dnl Configuration script for CUPS.
dnl
dnl Copyright © 2007-2018 by Apple Inc.
dnl Copyright © 1997-2007 by Easy Software Products, all rights reserved.
dnl
dnl Licensed under Apache License v2.0.  See the file "LICENSE" for more
dnl information.
dnl

dnl We need at least autoconf 2.60...
AC_PREREQ(2.60)

dnl Package name and version...
AC_INIT([CUPS], [3.0b1], [https://github.com/michaelrsweet/xcups/issues], [cups], [https://www.cups.org/])

sinclude(config-scripts/cups-opsys.m4)
sinclude(config-scripts/cups-common.m4)
sinclude(config-scripts/cups-directories.m4)
sinclude(config-scripts/cups-manpages.m4)

sinclude(config-scripts/cups-sharedlibs.m4)
sinclude(config-scripts/cups-libtool.m4)
sinclude(config-scripts/cups-compiler.m4)

sinclude(config-scripts/cups-network.m4)
sinclude(config-scripts/cups-poll.m4)
sinclude(config-scripts/cups-threads.m4)
sinclude(config-scripts/cups-tls.m4)
sinclude(config-scripts/cups-pam.m4)
sinclude(config-scripts/cups-largefile.m4)
sinclude(config-scripts/cups-dnssd.m4)
sinclude(config-scripts/cups-startup.m4)
sinclude(config-scripts/cups-defaults.m4)

INSTALL_LANGUAGES=""
UNINSTALL_LANGUAGES=""
LANGFILES=""
if test "x$LANGUAGES" != x; then
	INSTALL_LANGUAGES="install-languages"
	UNINSTALL_LANGUAGES="uninstall-languages"
elif test "x$CUPS_BUNDLEDIR" != x; then
	INSTALL_LANGUAGES="install-langbundle"
	UNINSTALL_LANGUAGES="uninstall-langbundle"
fi

AC_SUBST(INSTALL_LANGUAGES)
AC_SUBST(UNINSTALL_LANGUAGES)

AC_OUTPUT(Makedefs
	  cups-config
	  scheduler/cups.sh
	  scheduler/org.cups.cupsd.path
	  scheduler/org.cups.cupsd.service
	  scheduler/org.cups.cupsd.socket)

chmod +x cups-config
