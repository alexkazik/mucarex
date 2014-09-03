	;
	; Copyright (c) 2014 ALeX Kazik
	; All rights reserved.
	;
	; Redistribution and use in source and binary forms, with or without
	; modification, are permitted provided that the following conditions are met:
	;
	; * Redistributions of source code must retain the above copyright notice, this
	;   list of conditions and the following disclaimer.
	;
	; * Redistributions in binary form must reproduce the above copyright notice,
	;   this list of conditions and the following disclaimer in the documentation
	;   and/or other materials provided with the distribution.
	;
	; * Neither the names MuCaREX, p1x3l.net nor the names of its
	;   contributors may be used to endorse or promote products derived from
	;   this software without specific prior written permission.
	;
	; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	; IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	; DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
	; FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	; DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
	; SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	; CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
	; OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	; OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
	;

	;
	; This driver is compatible with these flash chips:
	; SST39SF040
	;


FLASH_NAME = "SST39SF040"
FLASH_VERSION = 1

	;
	; all FLASH_* routines have the page 30 activated on enter
	; page 30 = begin of last 64K of both flash
	; (if changed the page should be set to 30 before exit)
	;

FLASH_CHECK_TYPE macro
	
	;
	; IN:
	;   U: status "unknown"
	; OUT:
	;   U: status
	; CAN BE USED:
	;   D, X, Y

	; enable auto-select mode
	ldb # $aa
	stb $5555
	ldb # $55
	stb $2aaa
	ldb # $90
	stb $5555

	; get flash type
	ldx $0000
	cmpx # $bfb7 ; SST39SF040
	bne reset_flash_exit
/

	; everything is ok
	ldu # text_flash_ok

reset_flash_exit:
	; reset to normal operation (write $f0 to any address)
	ldb # $f0
	stb $0000

	endm


FLASH_WRITE_BYTE macro

	;
	; IN:
	;   A: byte to write
	;   X: address to write to
	; OUT:
	;   -
	; CAN BE USED:
	;   B

	ldb # $aa
	stb $5555
	ldb # $55
	stb $2aaa
	ldb # $a0
	stb $5555
	sta 0, x

	; wait for write to be done
/
	ldb 0, x
	eorb 0, x
	andb # %01000000
	bne -

	endm


FLASH_ERASE_SECTOR macro

	;
	; IN:
	;   -
	; OUT:
	;   -
	; CAN BE USED:
	;   D, X, Y, U

	; sector to erase
	ldx # $0000

	; erase a sector
/
	ldb # $aa
	stb $5555
	ldb # $55
	stb $2aaa
	ldb # $80
	stb $5555
	ldb # $aa
	stb $5555
	ldb # $55
	stb $2aaa
	ldb # $30
	stb 0, x

	; wait for erase to be done
/
	ldb $0000
	eorb $0000
	bitb # %01000000
	bne -

	; next sector
	leax $1000, x

	; repeat until 32K are erased
	cmpx # $8000
	bne --

	endm

	include "mds-seq.lib"
