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

	ifndef MUCAREX_INC
MUCAREX_INC = 1

	;
	; register description
	;

MUCAREX_PAGE = $c000
MUCAREX_READ = $c100
MUCAREX_SET  = $c200
MUCAREX_BANK = $c300

	;
	; read offsets
	;

MCR_READ_MODE_B0  = $00
MCR_READ_MODE_B1  = $01
MCR_READ_RAM_BANK = $02
MCR_READ_LED      = $03
MCR_READ_DO_PAGE  = $04
MCR_READ_ID_B0    = $05
MCR_READ_ID_B1    = $06
MCR_READ_MASTER   = $07
MCR_READ_BANK_B0  = $08
MCR_READ_BANK_B1  = $09
MCR_READ_BANK_B2  = $0a
MCR_READ_BANK_B3  = $0b
MCR_READ_BANK_B4  = $0c
MCR_READ_BANK_B5  = $0d
MCR_READ_BANK_B6  = $0e
MCR_READ_BANK_B7  = $0f

	;
	; set mask
	;

MCR_SET_MODE0_BOOTUP = $00
MCR_SET_MODE1_RAM    = $01
MCR_SET_MODE2_32K    = $02
MCR_SET_MODE3_64K    = $03
MCR_SET_RAM_BANK0    = $00
MCR_SET_RAM_BANK1    = $04
MCR_SET_LED_OFF      = $00
MCR_SET_LED_ON       = $08
MCR_SET_DO_PAGE_OFF  = $00
MCR_SET_DO_PAGE_ON   = $10
MCR_SET_ID           = $00
MCR_SET_SLAVE        = $00
MCR_SET_MASTER       = $80

	endif
