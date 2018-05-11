#
# Example files makefile for CUPS.
#
# Copyright © 2007-2018 by Apple Inc.
# Copyright © 2002-2005 by Easy Software Products.
#
# Licensed under Apache License v2.0.  See the file "LICENSE" for more
# information.
#

#
# Include standard definitions...
#

include ../Makedefs


#
# Example files...
#

DATAFILES	=	\
			color.jpg \
			document-a4.pdf \
			document-a4.ps \
			document-letter.pdf \
			document-letter.ps \
			gray.jpg \
			onepage-a4.pdf \
			onepage-a4.ps \
			onepage-letter.pdf \
			onepage-letter.ps \
			testfile.jpg \
			testfile.pcl \
			testfile.pdf \
			testfile.ps \
			testfile.txt
TESTFILES	=	\
			create-printer-subscription.test \
			get-completed-jobs.test \
			get-jobs.test \
			get-notifications.test \
			get-printer-attributes.test \
			get-subscriptions.test \
			ipp-1.1.test \
			ipp-2.0.test \
			ipp-2.1.test \
			ipp-2.2.test \
			ipp-everywhere.test \
			print-job.test \
			print-job-deflate.test \
			print-job-gzip.test \
			validate-job.test


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
# Clean everything...
#

clean:


#
# Dummy depend...
#

depend:


#
# Install all targets...
#

install:	all install-data install-headers install-libs install-exec


#
# Install data files...
#

install-data:
	echo Installing sample ipptool files in $(DATADIR)/ipptool...
	$(INSTALL_DIR) -m 755 $(DATADIR)/ipptool
	for file in $(DATAFILES); do \
		$(INSTALL_COMPDATA) $$file $(DATADIR)/ipptool; \
	done
	for file in $(TESTFILES); do \
		$(INSTALL_DATA) $$file $(DATADIR)/ipptool; \
	done


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
	echo Uninstalling sample ipptool files from $(DATADIR)/ipptool...
	for file in $(DATAFILES); do \
		$(RM) $(DATADIR)/ipptool/$$file; \
	done
	for file in $(TESTFILES); do \
		$(RM) $(DATADIR)/ipptool/$$file; \
	done
	-$(RMDIR) $(DATADIR)/ipptool
