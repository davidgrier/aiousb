# Makefile for aiousb.so
#
# Shared object library to control ACCES I/O USB interfaces under IDL
#
# Modification history
# 06/25/2010: Written by David G. Grier, New York University
# 11/14/2011 DGG Updated to global install
# 01/28/2013 DGG Updated paths
# 01/30/2013 DGG updated for IDL based build
# 03/27/2015 DGG updated for DLM version
#
# Copyright (c) 2010-2015 David G. Grier
#
TARGET = aiousb
SRC = $(TARGET).c

SYS  = $(shell uname -s | tr '[:upper:]' '[:lower:]')
ARCH = $(shell uname -m)
LIBRARY = $(TARGET).$(SYS).$(ARCH).so

DLM = $(TARGET).dlm

IDL = idl -quiet
INSTALL = install

DESTINATION = lib

all: $(LIBRARY)

$(LIBRARY): $(SRC)
	@mkdir build 2>/dev/null ||:
	@$(IDL) compile_$(TARGET)

install: $(LIBRARY) $(DLM)
	sudo $(INSTALL) -d $(DESTINATION)
	sudo $(INSTALL) $(LIBRARY) $(DLM) $(DESTINATION)

uninstall:
	sudo rm -rf $(DESTINATION)

clean:
	-rm $(LIBRARY)
	-rm build
