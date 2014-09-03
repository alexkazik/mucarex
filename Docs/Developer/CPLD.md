CPLD Firmware
=============


Requirements
------------

* gnumake
* Xilinx ISE WebPACK (Linux version tested)
* openocd or other tool to program


XC9572 vs. XC9572XL
-------------------

In order to be able to compile a version for the XC9572 all occurrences
of `xc9572xl` and `xc9500xl` has to be stripped of the `xl` extension in
the following files: `CPLD/Makefile`, `CPLD/src/mucarex.xst`. Afterwards
a `make clean` and `make` will compile it accordingly.


Compiling
---------

	make

A precompiled version is available at the
[Releases](https://github.com/alexkazik/mucarex/releases/latest) section.


Programming
-----------

When using a openocd usb adapter `make prog` will do the magic. For
other adapters please modify the Makefile accordingly.

Notice: The JTAG socket on the prototype board is an "AVR-JTAG"
compatible (see also Docs/Developer/PCB.md).
