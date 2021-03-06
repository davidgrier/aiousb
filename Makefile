# Makefile for aiousb
#
# Modification history
# 06/25/2010: Written by David G. Grier, New York University
# 06/28/2015 DGG Updated for DLM version
# 
# Copyright (c) 2010-2015 David G. Grier
#
IDLDIR = /usr/local/IDL
PRODIR = $(IDLDIR)/accesio
LIBDIR = $(PRODIR)

all:
	make -C lib

install: all
#	make -C idl install DESTINATION=$(PRODIR)
	make -C lib install DESTINATION=$(LIBDIR)

uninstall:
#	make -C idl uninstall DESTINATION=$(PRODIR)
	make -C lib uninstall DESTINATION=$(LIBDIR)

clean:
#	make -C idl clean
	make -C lib clean
