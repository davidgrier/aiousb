# aiousb

**IDL interface for ACCES I/O modules**

IDL is the Interactive Data Language, and is a product of
[Exelis Visual Information Solutions](http://www.exelisvis.com)

[ACCES I/O Products](http://accesio.com)
manufactures I/O modules.

*aiousb* is licensed under the
[GPLv3](http://www.gnu.org/licenses/licenses.html#GPL)

## What it does

This package provides an IDL interface for the category
of ACCES I/O modules that are connected to host computers through
a USB bus.
The preferred interface is through the `DGGhwAIOusb`
object:

    module = DGGhwAIOusb()

To use this package, make sure that the environment variables
`IDL_PATH` and `IDL_DLM_PATH` include `/usr/local/IDL/accesio`.

This package is written and maintained by David G. Grier
(david.grier@nyu.edu)

## INSTALLATION

### Install the ACCESIO libraries and API
The library, firmware, driver and installation instructions
 are available from the
[ACCES I/O download page](http://accesio.com/go.cgi?p=../usb/usb-ao16-16a.html)

### Install aiousb

1. unpack the distribution in a convenient directory.
2. `cd aiousb`
3. `make`
4. `make install`

Installation requires super-user privileges.

## UNINSTALLATION

1. `cd aiousb`
2. `make uninstall`
