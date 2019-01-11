#
# Man page makefile for CUPS.
#
# Copyright © 2007-2018 by Apple Inc.
# Copyright © 1993-2006 by Easy Software Products.
#
# Licensed under Apache License v2.0.  See the file "LICENSE" for more
# information.
#

include ../Makedefs


#
# Man pages...
#

MAN1	=	cancel.1 \
		cups.1 \
		cups-config.1 \
		ippfind.1 \
		ippserver.1 \
		ipptool.1 \
		lp.1 \
		lpoptions.1 \
		lpq.1 \
		lprm.1 \
		lpr.1 \
		lpstat.1
MAN5	=	client.conf.5 \
		cups-files.conf.5 \
		cupsd.conf.5 \
		cupsd-logs.5 \
		ipptoolfile.5
MAN8	=	cupsaccept.8 \
		cupsctl.8 \
		cupsd.8 \
		cupsd-helper.8 \
		cupsenable.8 \
		lpadmin.8 \
		lpmove.8 \
		lpc.8
HTML	=	$(MAN1:.1=.html) $(MAN5:.5=.html) $(MAN8:.8=.html)

.SUFFIXES:	.1 .5 .8 .html
.1.html .5.html .8.html: mantohtml
	echo Converting $< to HTML...
	./mantohtml $< >$@


#
# Make everything...
#

all:


#
# Make library targets...
#

libs:


#
# Make unit tests...
#

unittests:


#
# Clean all config and object files...
#

clean:
	$(RM) mantohtml mantohtml.o $(HTML)


#
# Dummy depend target...
#

depend:


#
# Install all targets...
#

install:	all install-data install-headers install-libs install-exec


#
# Install data files...
#

install-data: all
	$(INSTALL_DIR) -m 755 $(MANDIR)/man1
	for file in $(MAN1); do \
		echo Installing $$file in $(MANDIR)/man1...; \
		$(INSTALL_MAN) $$file $(MANDIR)/man1; \
	done
	$(INSTALL_DIR) -m 755 $(MANDIR)/man5
	for file in $(MAN5); do \
		echo Installing $$file in $(MANDIR)/man5...; \
		$(INSTALL_MAN) $$file $(MANDIR)/man5; \
	done
	$(INSTALL_DIR) -m 755 $(MANDIR)/man8
	for file in $(MAN8); do \
		echo Installing $$file in $(MANDIR)/man8...; \
		$(INSTALL_MAN) $$file $(MANDIR)/man8; \
	done
	$(RM) $(MANDIR)/man8/cupsreject.8
	$(LN) cupsaccept.8 $(MANDIR)/man8/cupsreject.8
	$(RM) $(MANDIR)/man8/cupsdisable.8
	$(LN) cupsenable.8 $(MANDIR)/man8/cupsdisable.8


#
# Install programs...
#

install-exec:


#
# Install headers...
#

install-headers:


#
# Install libraries...
#

install-libs:


#
# Uninstall files...
#

uninstall:
	for file in $(MAN1); do \
		$(RM) $(MANDIR)/man1/$$file; \
	done
	-$(RMDIR) $(MANDIR)/man1
	for file in $(MAN5); do \
		$(RM) $(MANDIR)/man5/$$file; \
	done
	-$(RMDIR) $(MANDIR)/man5
	for file in $(MAN8); do \
		$(RM) $(MANDIR)/man8/$$file; \
	done
	$(RM) $(MANDIR)/man8/cupsreject.8
	$(RM) $(MANDIR)/man8/cupsdisable.8
	-$(RMDIR) $(MANDIR)/man8


#
# Local programs (not built when cross-compiling...)
#

local:	html


#
# Make html versions of man pages...
#

html:	$(HTML)

mantohtml:	mantohtml.o ../cups/$(LIBCUPSSTATIC)
	$(LD_CC) $(ARCHFLAGS) $(LDFLAGS) -o $@ mantohtml.o \
		../cups/$(LIBCUPSSTATIC) $(TLSLIBS) \
		$(DNSSDLIBS) $(COMMONLIBS) $(LIBZ)
	$(CODE_SIGN) -s "$(CODE_SIGN_IDENTITY)" $@
