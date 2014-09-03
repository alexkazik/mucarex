High Score
==========

The Launcher (the menu on the Vectrex) is able to store the high score
on the flash. Additionally the games can load/store own data on flash
but must be programmed in order to do so (see
Docs/Developer/Custom-Data.md).


Preparations
------------

In order to store data on the flash the flash has to be prepared. The
last 64 KiB of flash will be reserved for the hogh score/data and the
code to write it.

This will reduce the size useable for games. The created flash binaries
will not cover the last 64 KiB and though not overwrite the data even if
you flash new games onto it. (There is an option to also use that region
and use the full 1 MiB but delete the stored high score and data and
disabling the option to store it, see Docs/User/vectrexpack.md.)

Before the games are flashed onto it at first the high score/data module
has to be installed, once.


Drivers
-------

### mds-am29f040-updater.bin

This driver is compatible with the following flash chips:

* Am29F040
* Am29F040B
* M29F040
* M29F040B
* MX29F040C

Please note that the Am29F040 and M29F040 (both without B) and MX29F040C
are not compatible with the EasyFlash, in case you want to use the
EasyFlash to program it.

Only the Am29F040B chip was acutally tested.

### mds-sst39sf040-updater.bin

This driver is compatible with the following flash chips:

* SST39SF040

Please note that the SST39SF040 is currently not compatible with the
EasyFlash, in case you want to use the EasyFlash to program it.

### Download

The drivers can be found at the
[Releases](https://github.com/alexkazik/mucarex/releases/latest) section.


Installation
------------

Flash the driver (see above) to the `LOROM`, plug both flash chips it
into the Vectrex and start it.

On the screen you'll see the detected flash chip, the version of new
module and the version of the already installed module and the usage (if
there is one installed). At the bottom you'll see what will happen if
you press any button.

Press a button to flash the module.

Once it completed press the button again to reset it and check if the
software is installed corretcly.

Now the module is installed on the `HIROM` chip, so don't swap them when
you flash the games on it because it would erase the stored data.

Flash the games on the chips and have fun.


Update
------

Just like Installation.

Move the joystick up or down fo force a installation, which erases all
stored data.


Usage
-----

A "Game ID" is used to keep track of the different scores/data (see
Docs/User/Custom-Data.md for details).

The launcher will load/store the high score/data by itself but you can
delete it if you want (see Docs/User/Launcher.md for details).
