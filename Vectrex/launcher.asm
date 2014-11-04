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


	cpu 6809

	page 0

	include "utils.inc"
	include "custom-data.inc"
	include "vectrex.inc"
	include "mdir.inc"
	include "mucarex.inc"
	include "mds.inc"
	include "draw.inc"

	;
	; variables
	;

Variable_Start = $c880
Variable_End := Variable_Start

Variable macro name, size
name = Variable_End
Variable_End := Variable_End + size
	endm

	Variable v_ptr_cat, 2
	Variable v_ptr_ent, 2
	Variable v_dir_ptr_cat, 2
	Variable v_dir_ptr_ent, 2
	Variable v_input_delay, 1
	Variable v_last_bank, 1
	Variable v_game_id, 16
	Variable v_settings_game_id, 16
	Variable v_old_score, 7
	Variable v_customdata_flags, 1
	Variable v_settings, 3
	Variable v_config, 2
	Variable v_use_3linemode, 1
	Variable v_string_scale_factor, 1
	Variable v_irq_code, 50 ; way too high - but we have enough ram

v_settings_default_bank = v_settings+0
v_settings_startup = v_settings+1
v_settings_3linemode = v_settings+2

v_config_store_score = v_config+0
v_config_startup = v_config+1

v_reloc_code = $9000 ; use the same space as the mds - which is not used anymore
v_reloc_submenu = $b000 ; part of the mds-data space ($a000-$afff is used for laoding score/data)

	;
	; START!
	;

	org $0000
	assume dpr:nothing

	;
	; rom header
	;

	byt "g GCE MCRX", $80
	adr no_music + reloc_start - v_reloc_code
	byt $f8, $50, $20, -$58
	byt "MUCAREX", $80
	byt $f8, $50, $00, -$30
	byt "BY P1X3L.NET", $80, $00

	;
	; directory identification, version and pointers
	;

	bra start ; skip this section
	byt MDIR_ID ; identification
d_version:
	adr 43  ; software version
	adr t_font
	adr d_dir

	;
	; init routine
	;

start:
	ldab $01, $03
	std V_Joy_Mux+0
	ldab $00, $00
	std V_Joy_Mux+2
	sta v_input_delay
	sta v_customdata_flags
	ldb # 16
	ldx # v_settings_game_id
/
	sta , x+
	decb
	bne -
	ldx # d_dir
	stx v_ptr_cat
	ldx # $0000
	stx v_ptr_ent

	; irq/nmi code
	ldab $7e, $3e ; a = opcode jmp extended, b = opcode reset
	sta $cbf8
	stb $cbfb
	ldx # irq_code_start
	ldu # v_irq_code
	stu $cbf9
	ldb # (irq_code_end - irq_code_start)-1
/
	lda b, x
	sta b, u
	decb
	bpl -

	; reload timer & reset irq flag (little endian)
	ldd # swap(1500000/100)
	std VIA_t2_lo

	lda # $a0
	sta VIA_int_enable

	andcc i

	;
	; set configuration
	;

	sta MUCAREX_SET | MCR_SET_MODE0_BOOTUP | MCR_SET_RAM_BANK0 | MCR_SET_LED_OFF | MCR_SET_DO_PAGE_ON | MCR_SET_ID | MCR_SET_MASTER

	;
	; verify configuration
	;

	ldb # 7
	ldx # MUCAREX_READ + MCR_READ_MODE_B0
/
	asl b, x ; the read+shift pushes d7 into carry, the write has no effect
	rola
	decb
	bpl -
	cmpa # MCR_SET_MODE0_BOOTUP | MCR_SET_RAM_BANK0 | MCR_SET_LED_OFF | MCR_SET_DO_PAGE_ON | MCR_SET_ID | MCR_SET_MASTER
	beq +
	; this is not the expected configuration -> do a reset in order to fix it
	reset
/

	;
	; read last bank
	;

	ldb # 7
	ldx # MUCAREX_READ + MCR_READ_BANK_B0
/
	asl b, x ; the read+shift pushes d7 into carry, the write has no effect
	rola
	decb
	bpl -

	sta v_last_bank

	;
	; init MDS
	;

	; copy loader
	ldx # mds_loader_reloc_start
	ldu # mds_loader_reloc_dst
/
	ldd , x++
	std , u++
	cmpx # mds_loader_reloc_end
	blo -

	; call mds-init
	clra ; short for lda # MDS_FUNC_INIT
	jsr [MDS_ADDR_DISPATCHER]

	;
	; store score+data
	;

	; is there a last bank?
	lda v_last_bank
	beq +
	; find the entry
	jsr f_find_last_bank
	bne +
	; we have a last bank and found the correct entry (entry ptr in U)
	jsr F_store_game
/

	;
	; restart immediadly
	;

	lda v_customdata_flags
	bita # CUSTOMDATA_FLAG_DO_RESTART
	beq +
	; we should restart
	; add flag "did restart"
	ora # CUSTOMDATA_FLAG_DID_RESTART
	sta v_customdata_flags
	ldy v_ptr_ent
	bra launch_game
/
	; no restart: clear flags
	clr v_customdata_flags

	;
	; read configuration
	;

	jsr F_read_settings

	;
	; if there is no last bank, use the default and search for the entry
	;

	lda v_last_bank
	bne +
	lda v_settings_default_bank
	sta v_last_bank
	jsr f_find_last_bank
/

	;
	; the main loop!
	;

	assume DPR:nothing
/
	lda v_settings_3linemode
	jsr f_menu
	bita # %1001
	bne launch_game
	jsr f_submenu
	bra -

	;
	; launch game: copy code to ram
	;

	section launch_game
	public launch_game
	public no_music
	public reloc_start

	assume dpr:nothing

launch_game:
	; disable interrupt & timer
	lda # $7f
	sta VIA_int_enable
	orcc i

	; load game score/data/config
	jsr F_load_game
	jsr F_read_config

	; copy code to v_reloc_code
	ldx # reloc_start
	ldu # v_reloc_code
/
	ldd , x++
	std , u++
	cmpx # reloc_end
	blo -
	jmp v_reloc_code

	;
	; relocated code
	;

reloc_start:
	phase v_reloc_code

	; load A = flags; B = bank
	ldd [v_ptr_ent]

	; activate correct bank (bank is unsigend but register B is used as signed = fix it by adding $80 to the address and the register)
	ldx # MUCAREX_BANK + $80
	addb # $80
	sta b, x

	; switch to page 0 (in modes other than "page" it will not be changeable)
	sta MUCAREX_PAGE | 0

	; check mode
	anda # MDIR_FLAG_MODE
	beq is_32k
	deca
	beq is_64k
	deca
	beq is_sram

is_page:
	; is 32k page mode
	sta MUCAREX_SET | MCR_SET_MODE2_32K | MCR_SET_RAM_BANK0 | MCR_SET_LED_OFF | MCR_SET_DO_PAGE_ON | MCR_SET_ID | MCR_SET_SLAVE
	bra start_game

is_32k:
	; is 32k (non page) mode
	sta MUCAREX_SET | MCR_SET_MODE2_32K | MCR_SET_RAM_BANK0 | MCR_SET_LED_OFF | MCR_SET_DO_PAGE_OFF | MCR_SET_ID | MCR_SET_SLAVE
	bra start_game

is_64k:
	; is 64k mode
	sta MUCAREX_SET | MCR_SET_MODE3_64K | MCR_SET_RAM_BANK0 | MCR_SET_LED_OFF | MCR_SET_DO_PAGE_OFF | MCR_SET_ID | MCR_SET_SLAVE
	bra start_game

is_sram:
	; is SRAM mode -> copy to ram

	; activate bank + swap to ram bank 0
	sta MUCAREX_SET | MCR_SET_MODE2_32K | MCR_SET_RAM_BANK0 | MCR_SET_LED_OFF | MCR_SET_DO_PAGE_ON | MCR_SET_ID | MCR_SET_MASTER

	ldu # $0000
/
	ldx # $8000
/
	ldd , u++
	std , x++
	cmpx # $c000
	bne -
	; finished 16k -> swap to ram bank 1
	sta MUCAREX_SET | MCR_SET_MODE2_32K | MCR_SET_RAM_BANK1 | MCR_SET_LED_OFF | MCR_SET_DO_PAGE_ON | MCR_SET_ID | MCR_SET_MASTER
	; restart if it was the first half
	cmpu # $8000
	bne --

	; activate ram mode
	sta MUCAREX_SET | MCR_SET_MODE1_RAM | MCR_SET_LED_OFF | MCR_SET_DO_PAGE_OFF | MCR_SET_ID | MCR_SET_SLAVE
	; bra start_game

start_game:
	; if special mode -> use it always!
	ldb v_config_startup
	bne +
	; auto-restart? (yes: immediate, no: system default)
	ldb # 3
	lda v_customdata_flags
	bita # CUSTOMDATA_FLAG_DO_RESTART
	bne +
	; use default
	ldb v_settings_startup
/
	; select mode
	decb
	beq start_slow
	decb
	stb smc_startup_mode

	;
	; common startup code (maybe not needed for both)
	;

	BIOS_Init_OS
	BIOS_DP_to_C8

	; search for cartridge header
	ldu # $0000
	stu V_Loop_Count ; Clear loop counter
	ldx # D_copyright_str
	ldb # 10 ; 11 bytes long
cd_loop:
	lda b, u
	cmpa b, x
	beq cd_match ; okay if match
	cmpb # 10 ; not okay if last byte wrong
	beq cd_bad
	cmpb # 6 ; okay if date wrong
	bhs cd_match
cd_bad:
	; bad cart: use real cold start routine
start_slow:
	BIOS_Cold_Start
cd_match:
	decb
	bpl cd_loop

	lda # $cc
	sta V_Pattern
	inc V_Music_Flag
	ldu # no_music

smc_startup_mode = *+1
	lda # $ff
	bne start_imm

	;
	; fast
	;

start_fast:

loop:
	BIOS_DP_to_C8
	ldd # $F848
	std V_Text_HW
	BIOS_Init_Music_chk
	BIOS_Wait_Recal
	BIOS_Do_Sound

	; Display cartridge GCE copyright string
	BIOS_Intensity_7F
	ldab -$40, -$40
	ldu # $0000
	BIOS_Print_Str_d

	; Display current high score (always valid)
	ldu # V_High_Score
	ldab $68, -$30
	BIOS_Print_Str_d

	; Display cartridge name
	ldu # 11+2 ; Get cartridge header addr (copyright + music skipped)
	BIOS_Print_List_hw
	ldx V_Loop_Count
	cmpx # 40
	bls loop

	; jump into the cartridge
	jmp 1, u


	;
	; immediate
	;

	assume dpr:$C8

start_imm:

	ldd # $F848
	std V_Text_HW
	BIOS_Init_Music_chk
	BIOS_Wait_Recal
	BIOS_Do_Sound

	; skip cartridge name
	ldu # 11+2 ; Get cartridge header addr (copyright + music skipped)
string_loop:
	leau 4, u
char_loop:
	lda , u+
	bpl char_loop
	lda 0, u
	bne string_loop

	; jump into the cartridge
	jmp 1, u

	assume dpr:nothing

	; "no music" music routine

no_music:
	adr $fee8
	adr $feb6
	byt $0, $80
	byt $0, $80

	dephase
reloc_end:

	endsection launch_game

	;
	; search entry for last bank
	;

f_find_last_bank:
	section find_last_bank

	ldx # d_dir
cat_loop:
	ldu MDIR_CAT_ENT_PTR, x
ent_loop:
	cmpa MDIR_ENT_BANK, u
	beq found_last
	ldb MDIR_ENT_FLAGS, u
	andb # MDIR_FLAG_LAST
	bne ent_exit
	leau MDIR_ENT_LENGTH, u
	bra ent_loop
ent_exit:
	ldb MDIR_CAT_FLAGS, x
	andb # MDIR_FLAG_LAST
	bne cat_exit
	leax MDIR_CAT_LENGTH, x
	bra cat_loop

found_last:
	stx v_ptr_cat
	stu v_ptr_ent
	clrb

cat_exit:
	; jmp to here from ent_exit, if B <> 0 (Z = 0)
	; or walk trough (B = 0, Z = 1)
	rts

	endsection find_last_bank

irq_code_start:
	section irq_code
	phase v_irq_code

	; unknown when the irq happend... could be everything
	assume dpr:nothing

	; dec wait counter
	lda v_input_delay
	beq +
	dec v_input_delay
/

	; reload timer & reset irq flag (by only rewriting the hi byte, the lo byte is latched)
	lda # (1500000/100) >> 8
	sta VIA_t2_hi

	rti

	dephase
	endsection irq_code
irq_code_end:


	;
	; externals
	;

	include "draw.lib"
	include "menu.lib"
	; use zero-width spaces (`) for the leading zeroes replacement
UTILS_BIN2ASCII_SPACE = '`'
	include "utils.lib"
	include "mds-loader.lib"
	include "submenu.lib"
	include "font.lib"
	include "config.lib"
	include "data.lib"

	;
	; check ram usage
	;

	if Variable_End >= ($cbea - 80)
		error "the variables take to many ram"
	endif

Variables_Used = Variable_End - Variable_Start

	; align to 16 bytes (to make the dump better readable)

	align 16

	;
	; here starts the directory listing
	;

d_dir:

