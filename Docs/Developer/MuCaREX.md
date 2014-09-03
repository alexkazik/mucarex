MuCaREX
=======


Identification
--------------

In order to distinguish the new module format from other ones the year
in the copyright of the powerup message (the first bytes of the rom)
should be "MCRX".


Modes
----

* Mode 0: Bootup

  Vectrex address $0000-$7fff accesses the flash at address $00000-$07fff.

  Vectrex address $8000-$bfff accesses the ram at address $0000-$3fff or $4000-$7fff depending on "Ram-Bank".

* Mode 1: RAM

  Vectrex address $0000-$7fff accesses the ram at address $0000-$7fff.

  Vectrex address $8000-$bfff is open (read/write has no effect).

* Mode 2: 32k

  Vectrex address $0000-$7fff accesses the flash at address `vectrex + bank*4k + page*32k`.

  Vectrex address $8000-$bfff accesses the ram at address $0000-$3fff or $4000-$7fff depending on "Ram-Bank".

* Mode 3: 64k

  Vectrex address $0000-$7fff accesses the flash at address `vectrex + bank*4k + pb6*32k`.

  Vectrex address $8000-$bfff accesses the ram at address $0000-$3fff or $4000-$7fff depending on "Ram-Bank".

  "pb6" is a pin from the VIA6522A which is in this case used for the bank switching.


Memory Map
----------

* $0000 - $7fff ROM or RAM, see modes
* $8000 - $bfff RAM or nothing, see modes
* $c000 - $c01f Set Page
* $c020 - $c0ff Reserved
* $c100 - $c00f Read Registers
* $c110 - $c1ff Reserved
* $c200 - $c2ff Set Registers
* $c300 - $c3ff Set Bank
* $c400 - $c7ff Reserved
* $c800 - $ffff Regular Vectrex Memory Map


Master/Slave
------------

While in master mode ("Master" is 1) write accesses to the flash are
executed, when in slave mode ("Master" is 0) write to the flash has no
effect.

This does allows it to reprogram the flashs, but only while in master
mode. The launcher menu does use it to store the high score and more
data if requested.

It is also required to be in master mode in order to change the most
registers, only the Page register may be changed on slave mode (see "Do
Page" below).


Registers
---------

*	"Mode" (2 bit): see above
*	"Ram-Bank" (1 bit): select lower(0)/upper(1) ram bank (see modes)
*	"LED" (1 bit): switch the LED off(0)/on(1)
*	"Do Page" (1 bit): If the paging register should be changeable(1) or frozen(0).
*	"Master" (1 bit): Master(1) or Slave(0) mode
*	"Page" (5 bit): The page offset (0-31 / $00-$1f) (see mode 2)
*	"Bank" (8 bit): The bank offset (0-255 / $00-$ff) (see mode 2+3)

\*) Accessing a register means that it has to be read or written. The written data is not used
and the read data is undefined.

The file Vectrex/mucarex.inc contains constants for all the registers.

### $c000 - $c01f Page Register

By accessing* this register the Page register is set to the lowest 5
address bits.

Only possible when "Do Page" is 1 otherwise read/write has no effect.

E.g. "sta $c002" will set the "Page" register to 2.

See also Docs/Developrt/PAGE.md.

### $c100 - $c10f Read Register

On each address only a single bit is read into the topmost bit, all
other bits are undefined. Writing to this area has no effect.

This registers can be read on master and slave mode.

* $c100 "Mode, bit 0"
* $c101 "Mode, bit 1"
* $c102 "Ram-Bank"
* $c103 "LED"
* $c104 "Do Page"
* $c105 ID, bit 0, always `0`
* $c106 ID, bit 1, always `0`
* $c107 "Master"
* $c108 "Bank, bit 0"
* $c109 "Bank, bit 1"
* $c10a "Bank, bit 2"
* $c10b "Bank, bit 3"
* $c10c "Bank, bit 4"
* $c10d "Bank, bit 5"
* $c10e "Bank, bit 6"
* $c10f "Bank, bit 7"

E.g. `lda $c103` will return the led bit in bit 7 ($00 or $80) all other
bits are undefined. A bmi/bpl can be used to jump conditionally. Since
write has no effect it's also possible to shift the read bit into the
carry directly, leaving other register unaffected, e.g. `rol $c108`. See
Vectrex/launcher.asm, section "verify configuration" and "read last
bank" on how it can be done.

### $c200 - $c2ff Set Registers

By accessing* this register the Registers are set to the lower 8 address
bits. Only possible while in master mode.

* "Mode (bit 0)" = address bit 0 ($01)
* "Mode (bit 1)" = address bit 1 ($02)
* "Ram-Bank" = address bit 2 ($04)
* "LED" = address bit 3 ($08)
* "Do Page" = address bit 4 ($10)
* ID (bit 0), always `0` = address bit 5 ($20)
* ID (bit 1), always `0` = address bit 6 ($40)
* "Master" = address bit 7 ($80)

If the two ID bits are not zero then an access has no effect.

E.g. `sta $c292` for Master, Do Page and 32k mode.

### $c300 - $c3ff Bank Register

By accessing* this register the Bank Registers are set to the lower 8
address bits. Only possible while in master mode.

E.g. `sta $c382` will set the "Bank" register to 130 ($82).


Powerup/Reset
-------------

On powerup the following is guaranteed:

* Mode 0 (Bootup)
* Master Mode
* Bank 0 (in order to differentiate from a reset)
* LED is on (this may change, do not rely on it)
* All other registers are undefined and should be set accordingly

On a reset the following occurs:

* Mode 0 (Bootup)
* Master Mode
* LED is on (this may change, do not rely on it)
* All other registers are unchanged


Reset Detection
---------------

A reset either by pressing the button or a `jmp [$fffe]` (calling the
reset vector directly) detected. A `jmp $f000` (calling the bios bootup
routine) is not identified as such.

When the bios is modified this detection may not work! (It is assumed
that the reset vector points to $f000 and that the first instruction has
at least 3 bytes in total.)
