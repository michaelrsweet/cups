dnl
dnl TLS stuff for CUPS.
dnl
dnl Copyright © 2007-2018 by Apple Inc.
dnl Copyright © 1997-2007 by Easy Software Products, all rights reserved.
dnl
dnl Licensed under Apache License v2.0.  See the file "LICENSE" for more
dnl information.
dnl

AC_ARG_ENABLE(tls, [  --disable-tls           disable SSL/TLS support])
AC_ARG_ENABLE(cdsa, [  --enable-cdsa           use CDSA for SSL/TLS support, default=first])
AC_ARG_ENABLE(gnutls, [  --enable-gnutls         use GNU TLS for SSL/TLS support, default=second])

TLSFLAGS=""
TLSLIBS=""
have_tls=0
CUPS_SERVERKEYCHAIN=""

if test x$enable_tls != xno; then
    dnl Look for CDSA...
    if test $have_tls = 0 -a "x$enable_cdsa" != "xno"; then
	if test $host_os_name = darwin; then
	    AC_CHECK_HEADER(Security/SecureTransport.h, [
	    	have_tls=1
		AC_DEFINE(HAVE_SSL)
		AC_DEFINE(HAVE_CDSASSL)
		CUPS_SERVERKEYCHAIN="/Library/Keychains/System.keychain"

		dnl Check for the various security headers...
		AC_CHECK_HEADER(Security/SecureTransportPriv.h,
		    AC_DEFINE(HAVE_SECURETRANSPORTPRIV_H))
		AC_CHECK_HEADER(Security/SecCertificate.h,
		    AC_DEFINE(HAVE_SECCERTIFICATE_H))
		AC_CHECK_HEADER(Security/SecItem.h,
		    AC_DEFINE(HAVE_SECITEM_H))
		AC_CHECK_HEADER(Security/SecItemPriv.h,
		    AC_DEFINE(HAVE_SECITEMPRIV_H),,
		    [#include <Security/SecItem.h>])
		AC_CHECK_HEADER(Security/SecPolicy.h,
		    AC_DEFINE(HAVE_SECPOLICY_H))
		AC_CHECK_HEADER(Security/SecPolicyPriv.h,
		    AC_DEFINE(HAVE_SECPOLICYPRIV_H))
		AC_CHECK_HEADER(Security/SecBasePriv.h,
		    AC_DEFINE(HAVE_SECBASEPRIV_H))
		AC_CHECK_HEADER(Security/SecIdentitySearchPriv.h,
		    AC_DEFINE(HAVE_SECIDENTITYSEARCHPRIV_H))

		AC_DEFINE(HAVE_CSSMERRORSTRING)
		AC_DEFINE(HAVE_SECKEYCHAINOPEN)])

		if test $host_os_version -ge 150; then
			AC_DEFINE(HAVE_SSLSETENABLEDCIPHERS)
		fi
	fi
    fi

    dnl Then look for GNU TLS...
    if test $have_tls = 0 -a "x$enable_gnutls" != "xno" -a "x$PKGCONFIG" != x; then
    	AC_PATH_TOOL(LIBGNUTLSCONFIG,libgnutls-config)
	if $PKGCONFIG --exists gnutls; then
	    have_tls=1
	    TLSLIBS=`$PKGCONFIG --libs gnutls`
	    TLSFLAGS=`$PKGCONFIG --cflags gnutls`
	    AC_DEFINE(HAVE_SSL)
	    AC_DEFINE(HAVE_GNUTLS)
	elif test "x$LIBGNUTLSCONFIG" != x; then
	    have_tls=1
	    TLSLIBS=`$LIBGNUTLSCONFIG --libs`
	    TLSFLAGS=`$LIBGNUTLSCONFIG --cflags`
	    AC_DEFINE(HAVE_SSL)
	    AC_DEFINE(HAVE_GNUTLS)
	fi

	if test $have_tls = 1; then
	    CUPS_SERVERKEYCHAIN="ssl"

	    SAVELIBS="$LIBS"
	    LIBS="$LIBS $TLSLIBS"
	    AC_CHECK_FUNC(gnutls_transport_set_pull_timeout_function, AC_DEFINE(HAVE_GNUTLS_TRANSPORT_SET_PULL_TIMEOUT_FUNCTION))
	    AC_CHECK_FUNC(gnutls_priority_set_direct, AC_DEFINE(HAVE_GNUTLS_PRIORITY_SET_DIRECT))
	    LIBS="$SAVELIBS"
	fi
    fi
fi

if test $have_tls = 1; then
    AC_MSG_RESULT([    Using TLSLIBS="$TLSLIBS"])
    AC_MSG_RESULT([    Using TLSFLAGS="$TLSFLAGS"])
elif test x$enable_cdsa = xyes -o x$enable_gnutls = xyes; then
    AC_MSG_ERROR([Unable to enable TLS support.])
fi

AC_SUBST(CUPS_SERVERKEYCHAIN)
AC_SUBST(TLSFLAGS)
AC_SUBST(TLSLIBS)

EXPORT_TLSLIBS="$TLSLIBS"
AC_SUBST(EXPORT_TLSLIBS)
