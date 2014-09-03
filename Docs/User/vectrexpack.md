vectrexpack
===========

The vectrexpack software can be used to create or modify game
compilations.


Usage
-----

	--help                                show this help
	Input Options:
	-b, --in-binary <file.bin>            read from a single .bin file, use "-" for stdin
	-l, --in-lorom <lorom.bin>
	-h, --in-hirom <hirom.bin>            read from two files, one for each flash chip
	-d, --in-directory <dir/index.txt>    read from a indexfile which links all the binaries
	Misc Options:
	-s, --store-laucher <launcher.bin>    stores the launcher to a file (stores the builtin launcher on --in-diretory)
	-t, --trim                            trim all modules by removing (hopefully) unnecessary empty banks at the end  (no effect on --out-diretory)
	-S, --load-laucher <launcher.bin>     loads the launcher from a file to not use the launcher inside the read binary (no effect on --out-diretory)
	-A, --default-launcher                uses the builtin launcher instead of the launcher inside the read binary (no effect on --out-diretory)
	-1, --enable-1mb                      use the full 1 MiB of flash, otherwise 64 KiB are reserved for high score
	Output Options:
	-B, --out-binary <file.bin>           write to a single .bin file, use "-" for stdout
	-L, --out-lorom <lorom.bin>
	-H, --out-hirom <hirom.bin>           write to two files, one for each flash chip
	-D, --out-directory <dir/index.txt>   write to a indexfile which links all the binaries
	-E, --out-easyflash <ef.crt>          write to a single EasyFlash crt file for programming the flash chips on a C64


Lorom/Hirom
-----------

This options is used to load/store from/to two binary files each with
the contents of one flash chip. Usage for loading:
`-l lorom.bin -h hirom.bin`.

After creating these files you have to flash each of them onto the
corresponding Flash chip.


Binary
------

Almost the same as Lorom/Hirom but all data is in one file. This format
is only for easy transportation because you can't flash it directly, you
have to split it at first.


Directory
---------

This format is useful for modifying the compilation.

The index file does contain all categories and entries.

Decode the example game compilation and look into it for better
understanding:

	mkdir compilation
	vectrexpack -b compilation.bin -D compilation/index.txt

Create a new compilation, two files, based on the example game
compilation.

	vectrexpack -d compilation/index.txt -t -L lorom.bin -H hirom.bin

The format is as follows:

* "`-;Name`" or "`-;Name;;Comment`" for a category with a single line "`Name`"
* "`-;Name1;Name2`" or "`-;Name1;Name2;Comment`" for a category with a name over two lines
* "`Name;File`" or "`Name;File;Comment`" for a entry withe the name "`Name`" and the file "`File`"
* "`;Comment`" for an comment

The "`Comment`" can be everything, including even more semicolon. The
comments are fully ignored and not stored (even if copying from and to
directory using `vectrexpack -d from/index.txt -D to/index.txt`).
The index file can have any name and extension, like "my-games.csv".


EasyFlash
---------

This is an write only format!

You can easily flash this file on a EasyFlash using the usual easyflash
tool "easyprog".

Be sure to switch the easyflash to not boot mode, otherwise the C64 will
try to boot the Vectrex (or even empty) software form the flash.

After programming just place the flashs into the MuCaREX.

Note: the Flash next to the C64 is the LOROM and the one farther away
the HIROM.


Other Options
-------------

With the `-t` option all modules are automatically trimmed if there is
an empty area at the end of the binary. Either $00 as also $ff's are
trimmed. This should work with all or at least most games, if you run in
some trouble don't use this option.

The options `-s`, `-S`, `-A` do have an effect on the Launcher (the menu
on the Vectrex). You can load and store the launcher from within a
binary or use the default one. If the launcher used is older than the
built in you'll get a notice.

Usually the last 64 KiB of the flash is reserved for high score/data. If
you don't want to use that feature you can use also those bytes for
games with the `-1` option. Note that you have to install an high score
module in order to be able to actually use it (see
Docs/User/High-Score).
