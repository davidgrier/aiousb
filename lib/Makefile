# Makefile for accesio.so
#
# Shared object library to control ACCES I/O USB interfaces under IDL
#
# Modification history
# 06/25/2010: Written by David G. Grier, New York University
# 11/14/2011 DGG Updated to global install
# 01/28/2013 DGG Updated paths
# 01/30/2013 DGG updated for IDL based build
#
TARGET = accesio
FILES = $(TARGET).c
DESTINATION = lib

IDL = idl -quiet
INSTALL = install

all: $(TARGET).so

$(TARGET).so: $(FILES)
	@$(IDL) compile_accesio

install: all
	sudo $(INSTALL) -d $(DESTINATION)
	sudo $(INSTALL) build/$(TARGET).so $(DESTINATION)

uninstall:
	sudo rm $(DESTINATION)/$(TARGET).so
	sudo rm $(DESTINATION)

clean:
	@rm core $(OBJS) $(TARGET).so *~
