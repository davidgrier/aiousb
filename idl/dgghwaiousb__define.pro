;+
; NAME:
;    DGGhwAIOusb
;
; PURPOSE:
;    Interface for ACCES I/O modules connected to the USB bus
;
; PROPERTIES:
; [IGS] DEVICE: ID number of the ACCES I/O device on the USB bus
;           Default: 0
; [ GS] CHANNEL: Channel of device to operate.
; [ GS] DACRANGE: Range setting for digital-to-analog outputs:
;           0: 0 to 5V
;           1: -5 to 5V
;           2: 0 to 10V
;           3: -10 to 10V
; [ GS] VALUE: floating point value read from input, or presently
;           begin output.
; [ GS] TIMEOUT: Communications timeout period [ms]
; [ G ] NAME: String name of module
; [ G ] SERIALNUMBER: Serial number of device
; [ G ] DIOPORTS: Number of digital I/O ports in device
; [ G ] COUNTERS: Number of digital counters
; [ G ] TRISTATES: Number of tristate ports
; [ G ] ROOTCLOCK:
; [ G ] DACCHANNELS: Number of digital-to-analog channels
; [ G ] ADCCHANNELS: Number of analog-to-digital channels
; [ G ] ADCMUXCHANNELS: Number of multiplexed analog-to-digital channels
;
; METHODS:
;
; REQUIREMENTS:
;    Calls routines from the aiousb library and DLM.  That
;    library and installation instructions are available at
;    https://github.com/davidgrier/aiousb
;
; MODIFICATION HISTORY:
; 03/28/2015 Written by David G. Grier, New York University
;
; Copyright (c) 2015 David G. Grier
;-
;;;;;
;
; DGGhwAIOusb::SetProperty
;
pro DGGhwAIOusb::SetProperty, device = device, $
                              channel = channel, $
                              dacrange = dacrange, $
                              value = value, $
                              timeout = timeout

  COMPILE_OPT IDL2, HIDDEN

  if isa(device, /number, /scalar) && (device gt 0) then $
     self.device = long(device)

  if isa(channel, /number, /scalar) && (channel gt 0) then $
     self.channel = long(channel)

  if isa(dacrange, /number, /scalar) && (dacrange ge 0) && (dacrange le 3) then $
     aoiusb_setdacrange, self.device, self.dacrange

  if isa(value, /number, /scalar) then begin
     self.value = float(value)
     aiousb_setdacvalue(self.device, self.channel, self.value)
  endif
  
  if isa(timeout, /number, /scalar) then $
     void = aiousb_commtimeout(self.device, timeout)
end

;;;;;
;
; DGGhwAIOusb::GetProperty
;
pro DGGhwAIOusb::GetProperty, device = device, $
                              channel = channel, $
                              dacrange = dacrange, $
                              value = value, $
                              timeout = timeout, $
                              name = name, $
                              serialnumber = serialnumber, $
                              dioports = dioports, $
                              counters = counters, $
                              tristates = tristates, $
                              rootclock = rootclock, $
                              dacchannels = dacchannels, $
                              adcchannels = adcchannels, $
                              adcmuxchannels = adcmuxchannels

  COMPILE_OPT IDL2, HIDDEN

  if arg_present(device) then device = self.device
  if arg_present(channel) then channel = self.channel
  if arg_present(dacrange) then dacrange = self.dacrange
  if arg_present(value) then value = self.value
  if arg_present(timeout) then timeout = aiousb_commtimeout(self.device)

  p = aiousb_getdeviceproperties(self.device)
  if arg_present(name)           then name           = p.name
  if arg_present(serialnumber)   then serialnumber   = p.serialnumber
  if arg_present(dioports)       then dioports       = p.dioports
  if arg_present(counters)       then counters       = p.counters
  if arg_present(tristates)      then tristates      = p.tristates
  if arg_present(rootclock)      then rootclock      = p.rootclock
  if arg_present(dacchannels)    then dacchannels    = p.dacchannels
  if arg_present(adcchannels)    then adcchannels    = p.adcchannels
  if arg_present(adcmuxchannels) then adcmuxchannels = p.adcmuxchannels
end

;;;;;
;
; DGGhwAIOusb::Cleanup
;
pro DGGhwAIOusb::Cleanup

  COMPILE_OPT IDL2, HIDDEN

  aiousb_exit
end

;;;;;
;
; DGGhwAIOusb::Init()
;
function DGGhwAIOusb::Init

  COMPILE_OPT IDL2, HIDDEN

  return (err = aiousb_init()) ? 0B : 1B
end

;;;;;
;
; DGGhwAIOusb__define
;
pro DGGhwAIOusb__define

  COMPILE_OPT IDL2, HIDDEN

  struct = {DGGhwAIOusb,   $
            device = 0L,   $
            channel = 0L,  $
            dacrange = 0L, $
            value = 0.     $
           }
end
