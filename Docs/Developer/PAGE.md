PAGE Module
===========

This is a new mode for Vectrex modules.

The MuCaREX is the first but hopefully not the last hardware to support
it. It is a standardized format on how to use more than 32/64 KiB ROM on
a Vectrex.


Identification
--------------

In order to distinguish the new module format from other ones the year
in the copyright of the powerup message (the first bytes of the rom)
should be "PAGE".


Memory Map
----------

* $0000 - $7fff 32 KiB bankable ROM
* $8000 - $bfff 16 KiB RAM
* $c000 - $c0ff Page select registers
* $c1ff - $c7ff Reserved
* $c800 - $ffff Regular Vectrex Memory Map


Usage
-----

The module will have page 0 visible in the ROM area ($0000-$7fff) on
boot up.

By accessing `$c000+page` the ROM is switched to that page (i.e. $c00b
for page 11). It does not matter if it's a read or write access, on a
write the data is not used, on a read the data will be undefined.
Example: `sta $c00b`.
