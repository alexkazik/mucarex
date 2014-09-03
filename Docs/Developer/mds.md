MuCaREX Data Storage (mds)
==========================

You want to use this Manual only if you either want to adapt the code to
use another type of flash, improve/modify the Launcher or write an
Game/Application which is directly stored on the MuCaREX (without the
Launcher) and use this module to load/store data.

This component provides the code to load/store data from/to the flash.
It is used by the loader to load/store the high scores, custom data and
configuration.

It will only function while the MuCaREX is in master mode (see
mucarex.md).

It can not be used by a game which is started by the Launcher because it
will set the MuCaREX to slave mode. See custom-data.md for information
about the functions provided by the loader.


The Structure
-------------


The mds has to be loaded into the MuCaREX additional RAM (named MDS_HEAD
= $8000). It consists of a header, version, some information and a
dispatcher which has to be called in order to invoke the functions.

See Vectrex/mds.inc for the addresses and functions.

* HEAD = 24 Bytes, ID String
* DATA_MODEL = 2 Bytes, currently only squential "SQ" is known
* VERSION = 2 Bytes, version of the mds Software
* FIRST\_DATA\_IN\_ROM = 2 Bytes, ptr to the first data, must be an even address,
	checksumming is done from the start to up to (excluding) this address
* INIT\_IN\_ROM = 2 Bytes, ptr to the real init routine, will be called by mds-loader.asm


Bootstrap
---------

The launcher will load a mds-loader program into ram and then calls the
init routine. The loader will then try to find the real mds on the flash
and invoke it, in that step the real mds will be loaded over that ram
area.


RAM Usage
---------

The mds program will use all of the additional MuCaREX RAM ($8000-$bfff)
on both banks. Additionally up to 50 bytes of stack will be used.

The functions INIT, STAUS and LOAD/STORE/DELETE DATA will prevent the
contents of the mds data area (MDS\_DATA\_AREA\_START), the other
functions (REORG, DIR) use all of that memory.


Dispatcher
----------

The number of the function which should be called has to be loaded in
the A register. It is safe to call functions the dispatcher do not know,
but in those cases the contents of the registers is undefined, except
hat C will be 1.

Example for INIT:

	lda # MDS_FUNC_NIT
	jsr [MDS_ADDR_DISPATCHER]

Example for STAUTS:

	lda # MDS_FUNC_STATUS
	jsr [MDS_ADDR_DISPATCHER]


Functions
---------

All registers except DP and S (Stack Pointer) will be destroyed if not
noted otherwise.

See Custom-Data.md for information about the game id.

### INIT
Initializes the mds.

IN:

OUT:

* A = highest function supported

### STATUS
Returns some status information.

IN:

OUT:

* U = ptr to status-text (ASCII uppercase, $ff terminated)
* A = 3 (number of entries in the table, see below)
* X = ptr to a table of three 16-bit values for: free, user and deleted space

### LOAD
Loads the data for a game represented by the game id and the type into
the specified buffer. When the data to load does not fit into the buffer
nothing is loaded as if there were no data.

IN:

* B = type of the data (e.g. MDS\_TYPE\_GAME\_SCORE)
* X = length of the buffer
* Y = ptr to the game id (e.g. `ldy # game_id`)
* U = ptr to buffer

OUT:

* Y is kept
* D contains the length of the data (if found, otherwise undefined)
* C is 0 when data is loaded, 1 otherwise

### STORE
Stores data for a game represented by the game id and the type into the
flash. When the length exceeds the maximum length or there is not enough
free space nohting happens.

IN:

* B = type of the data (e.g. MDS\_TYPE\_GAME\_SCORE)
* X = length of the data
* Y = ptr to the game id (e.g. `ldy # game_id`)
* U = ptr to buffer

OUT:

* Y is kept

### DELETE
Deletes data for a game represented by the game id and the type in
flash.

IN:

* B = type of the data (e.g. MDS\_TYPE\_GAME\_SCORE)
* Y = ptr to the game id (e.g. `ldy # game_id`)

OUT:

* Y is kept

### REORG
Checks if a reorg is necessary and performs one if needed. This function
should be called after each store call.

Note: uses all MuCaREX RAM ($8000-$bfff on both banks).

IN:

OUT:

### REORG_FORCE
Does a reorg even if not needed. This function is used by the mds
updater program to flash a new version without loosing the data.

Note: uses all MuCaREX RAM ($8000-$bfff on both banks).

IN:

OUT:

### REORG_CLEAN
Does a reorg (even if not needed) and deleting ALL score/data. This
function is used by the mds updater program to flash a version, deleting
all score/data.

Note: uses all MuCaREX RAM ($8000-$bfff on both banks).

IN:

OUT:

### DIR
Generates dierectory listing.

Format: Byte 0 contains the type, byte 1,2 contains the size, bytes 3-18
contains the game id. Then the next entry continues.

The directory will be within the mds data area ($a000-$bfff).

IN:

OUT:

* X = ptr to directory
* U = ptr to first byte behind directory
* C is 0 on success or 1 on failure (in case of failure X, U are undefined)
