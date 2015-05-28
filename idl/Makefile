# Makefile for aiousb
#
# Shared object library to control ACCES I/O USB interfaces under IDL
#
# Modification history
# 06/25/2010: Written by David G. Grier, New York University
# 11/14/2011 DGG Updated to global install
# 01/28/2013 DGG Updated paths
# 01/30/2013 DGG updated for IDL based build
# 03/27/2015 DGG updated for DLM
#
# Copyright (c) 2010-2015 David G. Grier
#
FILES = dgghwaiousb__define.pro

INSTALL = install
DESTINATION = pro

all: 

install: $(FILES)
	sudo $(INSTALL) -d $(DESTINATION)
	sudo $(INSTALL) -m 644 $(FILES) $(DESTINATION)

uninstall:
	sudo rm $(DESTINATION)/$(FILES)
	sudo rmdir $(DESTINATION)

clean:
	@rm core $(OBJS) $(TARGET).so *~
