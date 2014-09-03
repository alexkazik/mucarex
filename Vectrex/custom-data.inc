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

	ifndef CUSTOM_DATA_INC
CUSTOM_DATA_INC = 1

	;
	; the place and contents of the custom data storage
	;

CUSTOMDATA_AREA_START = $a000
CUSTOMDATA_AREA_END = $bff0

CUSTOMDATA_ADDR_START = CUSTOMDATA_AREA_END
CUSTOMDATA_ADDR_ID = CUSTOMDATA_ADDR_START
CUSTOMDATA_ADDR_TYPE = CUSTOMDATA_ADDR_ID + 10
CUSTOMDATA_ADDR_FLAGS = CUSTOMDATA_ADDR_TYPE + 1
CUSTOMDATA_ADDR_LEN = CUSTOMDATA_ADDR_FLAGS + 1
CUSTOMDATA_ADDR_ADDR = CUSTOMDATA_ADDR_LEN + 2
CUSTOMDATA_ADDR_END = CUSTOMDATA_ADDR_ADDR + 2

CUSTOMDATA_ID = "CUSTOMDATA"
CUSTOMDATA_ID_LENGTH = 10
CUSTOMDATA_TYPE_NEW = 'n'
CUSTOMDATA_TYPE_LOAD = 'l'
CUSTOMDATA_TYPE_SAVE = 's'

CUSTOMDATA_FLAG_DO_RESTART = $01
CUSTOMDATA_FLAG_DID_RESTART = $02

CUSTOMDATA_MAX_SIZE = 1024

	;
	; the header for the game id
	;

GAME_ID_HEADER = "GAME-ID:"

	endif
