The PCB
=======


Board V0.9 "Prototype"
----------------------

This PCB is slightly different to the V1.0 and every owner has an manual
at hand. It is not here available to reduce confusion.


Board V1.0
----------

### Assemble

Pitch: 2.54mm (0.100")

The following components have to be soldered:

* "C1"-"C4" Ceramic Capacitor 100nF
* "C5" Tantalum Capacitor, 4.7µF/10V
* "D1" LED, 3mm, 1.8V, 2mA, yellow
* "J1" Header, 1*3
* "P2" Fully Shrouded Box Headers, 2*5
* "R1" Resistor, 0.6W, 0.1%, 220 Ohm
* "U1", "U2" Socket, 32 pins, PLCC
* "U3" Socket, 28 pins, DIP
* "U4" Socket, 44 pins, PLCC
* "U5" REG LDO +3,3V, 0.15A, TO92

And place the chips on it:

* "J1" Jumper, 1*2 (see Options below)
* "U1","U2" Flash 4M (512K*8), 70ns, PLCC32 (see below)
* "U3" SRAM 62256-80 32K*8, DIP28
* "U4" CPLD XC9572XL or XC9572, PLCC44

Here is a prefilled shopping basket at
[reichelt.de](http://www.reichelt.de/?ACTION=20;AWKID=934915;PROVID=2084).

### Flash Chips

The following flash chips can be used:

* Am29F040 (2)
* Am29F040B (1,2) (only chip actually tested, recommended)
* AT49F040
* M29F040 (2)
* M29F040B (1,2)
* MX29F040C (2)
* SST39SF040 (2)

Notes:

1. Can be programmed with an EasyFlash
2. High score/data can be stored

The AT49F040 can not be used to store high score/data due to the memory
layout of it. It's possible to write an EasyFlash driver for all other
missing chips.

### Options

The XC9572XL needs a 3.3V source and the XC9572 (without XL) needs
5V. You can switch between these two with the jumper "J1".

If you want to use only a 3.3V or a 5V CPLD you can drop "J1" and bridge
the two pins directly. If you only want to use the 5V CPLD then also "U5"
and "C5" can be left out.

If you don't want to program the CPLD on the PCB because you got an
already programmed (or program it otherwise) you can drop "P2".

### Programming

The socket is AVR-JTAG compatible and has the following pinout:

	TCK 1  2 GND
	TDO 3  4 VCC
	TMS 5  6 N/C
	N/C 7  8 N/C
	TDI 9 10 GND
