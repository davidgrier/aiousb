;;;;;
;
; compile_aiousb.pro
;
; IDL batch file to compile the shared library that provides
; an IDL interface for ACCESIO usb analog output devices
;
; Modification History
; 01/30/2013 Written by David G. Grier, New York University
; 03/27/2015 DGG revised for DLM 
;
; Copyright (c) 2013-2015 David G. Grier
;
project_directory = './'
compile_directory = './build'
infiles = 'aiousb'
outfile = 'aiousb'

;;; accesio support
extra_cflags = '-I/usr/local/include/aiousb -std=gnu99 -D_GNU_SOURCE -pthread'
extra_lflags = '-laiousb'

;;; libusb-1.0 support
; Make sure that libusb-1.0 is installed
spawn, 'pkg-config --modversion libusb-1.0', version, err
if strlen(err) gt 0 then begin $
   print, 'libusb-1.0 not installed' & $
   exit & $
   endif
print, 'Building aiousb with libusb-1.0 version '+version
; CC flags
spawn, 'pkg-config --cflags libusb-1.0', cflags
extra_cflags += ' '+cflags
; LD flags
spawn, 'pkg-config --libs libusb-1.0', lflags
extra_lflags +=  ' '+lflags

;;;;
; Build the library
make_dll, infiles, outfile, 'IDL_Load', $
          extra_cflags = extra_cflags, $
          extra_lflags = extra_lflags, $
          input_directory = project_directory, $
          output_directory = project_directory, $
          compile_directory = compile_directory, $
          /platform_extension

exit
