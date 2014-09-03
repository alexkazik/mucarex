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

	ifndef MDIR_INC
MDIR_INC = 1

	;
	; directory id
	;

MDIR_ID = "MDir"

	;
	; DIRECTORY STRUCTURE
	;

	; cat: flags,entptr(16bit),dx,name(+),[dx,name(+)],$00

MDIR_CAT_LENGTH = 32
MDIR_CAT_FLAGS = 0
MDIR_CAT_ENT_PTR = 1
MDIR_CAT_NAME = 3

	; ent: flags,bank,dx,name(+),$ff,4 byte size marker,16 byte game id
	; the first byte size marker may replaces the $ff marker. (still end of text because the topmost bit is set)

MDIR_ENT_LENGTH = 48
MDIR_ENT_FLAGS = 0
MDIR_ENT_BANK = 1
MDIR_ENT_NAME = 2
MDIR_ENT_FILESIZE = 28
MDIR_ENT_BANKSIZE = 31
MDIR_ENT_GAME_ID = 32

	; size marker
	;   bit 31: always set (this way it may be used as an end of text marker)
	;   bit 30: if the filesize is greater than banksize then the trimmed bytes are $00/$ff depending on wether this bit is 0/1
	;   bit 29..8: the filesize in bytes
	;   bit 7..0: the banksize in 4 KiB banks



	; flags cat+ent:
	;   bit 7: first entry
	;   bit 6: second entry
	;   bit 5: second last entry
	;   bit 4: last entry
	; flags cat:
	;   bit 3..0: 0 (reserved)
	; flags ent:
	;   bit 3,2: 0 (reserved)
	;   bit 1,0: mode

MDIR_FLAG_FIRST   = $80
MDIR_FLAG_SECOND  = $40
MDIR_FLAG_SECLAST = $20
MDIR_FLAG_LAST    = $10
MDIR_FLAG_MODE    = $03

MDIR_MODE_32K  = $00
MDIR_MODE_64K  = $01
MDIR_MODE_SRAM = $02
MDIR_MODE_PAGE = $03

	;
	; font-size
	;

MDIR_SCALE_HEAD	= 12*2
MDIR_SCALE_BODY	= 8*2

	endif
