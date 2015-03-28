//
// accesio.c
//
// IDL-callable interface for ACCES I/O devices.
//
// Modification history:
// 06/25/2010 Written by David G. Grier, New York University
// 01/30/2013 Updated idl_export.h
//
// Copyright (c) 2010-2013 David G. Grier
//
#include <stdio.h>
#include <stdlib.h>

// ACCES I/O support
#include <aiousb.h>

// IDL support
#include <idl_export.h>

//
// AIOUSB_INIT
//
// Initialize ACCES I/O Systems on USB
//
IDL_VPTR IDL_CDECL aiousb_init(int argc, IDL_VPTR argv[])
{
  return IDL_GettmpLong(AIOUSB_Init());
}

//
// AIOUSB_EXIT
//
// Deactivate ACCES I/O System
//
void IDL_CDECL aiousb_exit(int argc, IDL_VPTR argv[])
{
  AIOUSB_Exit();
}

//
// AIOUSB_GETDEVICEPROPERTIES
//
// Query ACCES I/O device
//
// command line arguments
// argv[0]: IN device number
//
IDL_VPTR IDL_CDECL aiousb_getdeviceproperties(int argc, IDL_VPTR argv[])
{
  unsigned long device;
  DeviceProperties properties;
  unsigned long result;

  device = IDL_ULongScalar(argv[0]);

  struct idlDeviceProperties {
    IDL_STRING name;
    IDL_ULONG64 serialnumber;
    IDL_UINT dioports;
    IDL_UINT counters;
    IDL_UINT tristates;
    IDL_LONG rootclock;
    IDL_UINT dacchannels;
    IDL_UINT adcchannels;
    IDL_UINT adcmuxchannels;
  };
  struct idlDeviceProperties *idl_properties;
  static IDL_STRUCT_TAG_DEF tags[] = {
    { "NAME",           0, (void *) IDL_TYP_STRING  },
    { "SERIALNUMBER",   0, (void *) IDL_TYP_ULONG64 },
    { "DIOPORTS",       0, (void *) IDL_TYP_UINT    },
    { "COUNTERS",       0, (void *) IDL_TYP_UINT    },
    { "TRISTATES",      0, (void *) IDL_TYP_UINT    },
    { "ROOTCLOCK",      0, (void *) IDL_TYP_LONG    },
    { "DACCHANNELS",    0, (void *) IDL_TYP_UINT    },
    { "ADCCHANNELS",    0, (void *) IDL_TYP_UINT    },
    { "ADCMUXCHANNELS", 0, (void *) IDL_TYP_UINT    },
    { 0 }
  };
  IDL_StructDefPtr sdef = IDL_MakeStruct("properties", tags);
  
  idl_properties = malloc(sizeof(struct idlDeviceProperties));

  result = AIOUSB_GetDeviceProperties(device, &properties);
  if (result == AIOUSB_SUCCESS) {
    IDL_StrStore(&(idl_properties->name), properties.Name);
    idl_properties->serialnumber = (IDL_ULONG64) properties.SerialNumber;
    idl_properties->dioports = (IDL_UINT) properties.DIOPorts;
    idl_properties->counters = (IDL_UINT) properties.Counters;
    idl_properties->tristates = (IDL_UINT) properties.Tristates;
    idl_properties->rootclock = (IDL_LONG) properties.RootClock;
    idl_properties->dacchannels = (IDL_UINT) properties.DACChannels;
    idl_properties->adcchannels = (IDL_UINT) properties.ADCChannels;
    idl_properties->adcmuxchannels = (IDL_UINT) properties.ADCMUXChannels;
  } else {
    IDL_Message(IDL_M_NAMED_GENERIC, IDL_MSG_LONGJMP,
		AIOUSB_GetResultCodeAsString(result));
  }
  
  IDL_MEMINT dims[] = {1};
  return IDL_ImportArray(1, dims, IDL_TYP_STRUCT,
			 (UCHAR *) idl_properties, NULL, sdef);
}  

//
// AIOUSB_COMMTIMEOUT
//
// Set or get the communication timeout interval
//
// command line arguments
// argv[0]: IN device number
// argv[1]: IN/OPTIONAL timeout interval in milliseconds
//
unsigned IDL_STDCALL
aiousb_commtimeout(int argc, char **argv)
{
  unsigned long result;
  unsigned long device;
  unsigned timeout;

  device = *(IDL_ULONG *) argv[0];

  if (argc == 2) {
    timeout = *(IDL_UINT *) argv[1];
    result = AIOUSB_SetCommTimeout(device, timeout);
    if (result != AIOUSB_SUCCESS) {
      printf("AIOUSB Error: %s\n", AIOUSB_GetResultCodeAsString(result));
      return -1;
    }
  }

  return AIOUSB_GetCommTimeout(device);
}

//
// AIOUSB_SETDACRANGE
//
// Set range for D/A conversions on specified ACCES I/O device.
//
// command line arguments
// argv[0]: device number
// argv[1]: range index
//          0: 0 to 5V
//          1: -5 to 5V
//          2: 0 to 10V
//          3: -10 to 10V
//
unsigned IDL_STDCALL
aiousb_setdacrange(int argc, char **argv)
{
  unsigned long result;
  unsigned long device;
  int range;

  device = *(IDL_ULONG *) argv[0];
  range = *(IDL_INT *) argv[1];
  
  result = DACSetBoardRange(device, range);
  if (result != AIOUSB_SUCCESS) {
    printf("AIOUSB Error: %s\n", AIOUSB_GetResultCodeAsString(result));
  }

  return result;
}

//
// AIOUSB_SETDACVALUE
//
// Set value for D/A convertion on specified channel
// on specified device.
//
// command line arguments
// argv[0]: IN device number
// argv[1]: IN channel number
// argv[2]: IN value: range 0 to 1 (full-scale)
//
aiousb_setdacvalue(int argc, char **argv)
{
  unsigned long result;
  unsigned long device;
  unsigned short channel;
  float value;

  device = *(IDL_ULONG *) argv[0];
  channel = *(IDL_UINT *) argv[1];
  value = *(float *) argv[2];

  result = DACDirect(device, channel, 
		     (unsigned short) (value * (float) 0xffff));
  if (result != AIOUSB_SUCCESS) {
    printf("AIOUSB Error: %s\n", AIOUSB_GetResultCodeAsString(result));
  }
   
  return result;
}

//
// IDL_Load
//
int IDL_Load(void)
{
  int status;
  int nfcns, npros;

  static IDL_SYSFUN_DEF2 function_addr[] = {
    { aiousb_init, "AIOUSB_INIT", 0, 0, 0, 0 },
    { aiousb_getdeviceproperties, "AIOUSB_GETDEVICEPROPERTIES", 1, 1, 0, 0 },
  };

  static IDL_SYSFUN_DEF2 procedure_addr[] = {
    { aiousb_exit, "AIOUSB_EXIT", 0, 0, 0, 0 },
  };

  nfcns = IDL_CARRAY_ELTS(function_addr);
  status = IDL_SysRtnAdd(function_addr, TRUE, nfcns);

  npros = IDL_CARRAY_ELTS(procedure_addr);
  status |= IDL_SysRtnAdd(procedure_addr, FALSE, npros);

  return status;
}
