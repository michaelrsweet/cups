#
# IPP tools makefile for CUPS.
#
# Copyright © 2007-2018 by Apple Inc.
# Copyright © 1997-2006 by Easy Software Products, all rights reserved.
#
# Licensed under Apache License v2.0.  See the file "LICENSE" for more
# information.
#

include ../Makedefs



#
# Programs...
#

OBJS		=	\
			ippfind.o \
			ippserver.o \
			ipptool.o
TARGETS		=	\
			ippfind \
			ippserver \
			ipptool
UNITTARGETS	=	\
			ippfind-static \
			ippserver-static \
			ipptool-static


#
# Make all targets...
#

all:		$(TARGETS)


#
# Make library targets...
#

libs:


#
# Make unit tests...
#

unittests:	$(UNITTARGETS)


#
# Clean all object files...
#

clean:
	$(RM) $(TARGETS) $(UNITTARGETS) $(OBJS)


#
# Update dependencies (without system header dependencies...)
#

depend:
	$(CC) -MM $(ALL_CFLAGS) $(OBJS:.o=.c) >Dependencies


#
# Install all targets...
#

install:	all install-data install-headers install-libs install-exec


#
# Install data files...
#

install-data:


#
# Install programs...
#

install-exec:
	echo Installing tools in $(BINDIR)...
	$(INSTALL_DIR) -m 755 $(BINDIR)
	for file in $(TARGETS); do \
		$(INSTALL_BIN) $$file $(BINDIR); \
	done
	if test "x$(SYMROOT)" != "x"; then \
		$(INSTALL_DIR) $(SYMROOT); \
		for file in $(TARGETS); do \
			cp $$file $(SYMROOT); \
			dsymutil $(SYMROOT)/$$file; \
		done; \
	fi


#
# Install headers...
#

install-headers:


#
# Install libraries...
#

install-libs:


#
# Unnstall all targets...
#

uninstall:
	for file in $(TARGETS); do \
		$(RM) $(BINDIR)/$$file; \
	done
	$(RMDIR) $(BINDIR)


#
# ippfind
#

ippfind:	ippfind.o ../cups/$(LIBCUPS)
	echo Linking $@...
	$(LD_CC) $(LDFLAGS) -o $@ ippfind.o $(LIBS)

ippfind-static:	ippfind.o ../cups/$(LIBCUPSSTATIC)
	echo Linking $@...
	$(LD_CC) $(LDFLAGS) -o $@ ippfind.o $(STATICLIBS)


#
# ippserver
#

ippserver:	ippserver.o ../cups/$(LIBCUPS)
	echo Linking $@...
	$(LD_CC) $(LDFLAGS) -o $@ ippserver.o $(LIBS)

ippserver-static:	ippserver.o ../cups/$(LIBCUPSSTATIC)
	echo Linking $@...
	$(LD_CC) $(LDFLAGS) -o $@ ippserver.o $(STATICLIBS)


#
# ipptool
#

ipptool:	ipptool.o ../cups/$(LIBCUPS)
	echo Linking $@...
	$(LD_CC) $(LDFLAGS) -o $@ ipptool.o $(LIBS)

ipptool-static:	ipptool.o ../cups/$(LIBCUPSSTATIC)
	echo Linking $@...
	$(LD_CC) $(LDFLAGS) -o $@ ipptool.o $(STATICLIBS)


#
# Dependencies...
#

include Dependencies
