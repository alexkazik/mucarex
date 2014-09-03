MuCaREX
=======

Multi Cartridge for Vectrex

by p1x3l.net

[https://github.com/alexkazik/mucarex/](https://github.com/alexkazik/mucarex/)


Features
--------

* Has 1 MiB of flash memory
* Has 32 KiB of RAM
* Can emulate the following modules
  * Regular modules with up to 32 KiB ROM
  * 64 KiB modules with bank switching (using PB6)
  * "SRAM" modules, where the contents of the ROM is loaded into the RAM and then used instead of the ROM
  * "PAGE" modules with up to 31 pages of 32 KiB each (up to 992 KiB) and 16 KiB RAM (see Docs/Developer/PAGE.md)
* The flash can be programmed from the Vectrex, e.g. for storing high score
* Changing the registers of the MuCaREX and programming the flash can only be done while in
  master mode. The slave mode is activated when starting a module and deactivated on reset.

In the directory Docs/User are the manuals to use the MuCaREX.

In the directory Docs/Developer are the manuals on how to compile your
own firmware (CPLD), Launcher (Vectrex menu) and how to use the
functions of the MuCaREX.


Basic Usage
-----------

1. Assemble the PCB (if necessary)
2. Program the CPLD (see Docs/Developer/CPLD.md, if necessary)
3. Grab a game collection (see [Releases](https://github.com/alexkazik/mucarex/releases/latest)) or create a new one
4. Optional: Modify the collection, see Docs/User/vectrexpack.md
5. Optional: Initialize the high score/data saver, see Docs/User/High-Score.md
6. Program the collection on to the flash chips
7. Place the Flashs in the appropriate sockets
8. Plug the MuCaREX in your Vectrex and have fun
