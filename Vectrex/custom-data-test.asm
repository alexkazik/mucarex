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

	include "utils.inc"
	include "vectrex.inc"
	include "custom-data.inc"

c_max_text_len = 12
v_length = $c880
v_wait_release = $c881
v_my_text = $c882 ; length: c_max_text_len+1

	;
	; START!
	;

	org $0000
	assume dpr:nothing

	;
	; rom header
	;

	byt "g GCE 2014", $80
	adr d_music
	byt $f8, $50, $20, -$56
	byt "CUSTOM DATA TEST", $80
	byt $f8, $50, $00, $08
	byt "BY ALX", $80, $00

	;
	; init
	;

	lda # $01
	sta V_Joy_Mux_1_X
	lda # $03
	sta V_Joy_Mux_1_Y
	lda # $00
	sta V_Joy_Mux_2_X
	sta V_Joy_Mux_2_Y
	sta v_wait_release
	lda # ' '
	ldx # v_my_text
/
	sta , x+
	cmpx # v_my_text + c_max_text_len
	bne -
	lda # $ff
	sta 0, x

	;
	; check if custom data is available
	;

	ldx # CUSTOMDATA_ADDR_ID
	ldu # custom_data_id
	ldb # CUSTOMDATA_ID_LENGTH
/
	lda , x+
	cmpa , u+
	bne no_custom_data
	decb
	bne -

	; check for load/new
	lda CUSTOMDATA_ADDR_TYPE
	cmpa # CUSTOMDATA_TYPE_NEW
	beq is_new
	cmpa # CUSTOMDATA_TYPE_LOAD
	beq is_load

	;
	; no valid signature is found -> display "not found"
	;

no_custom_data:
	BIOS_Wait_Recal
	BIOS_Intensity_5F

	ldu # text_no_cust_data
	ldab $00, -$70
	BIOS_Print_Str_d

	BIOS_Read_Btns
	tsta
	beq no_custom_data

	reset

	;
	; found a valid signature
	;

is_new:
	; new length: 1
	lda # 1
	sta v_length
	; new string: "A"
	lda # 'A'
	sta v_my_text
	bra main

is_load:
	; copy into our string + length
	ldx CUSTOMDATA_ADDR_ADDR
	ldu # v_my_text
	ldd CUSTOMDATA_ADDR_LEN
	cmpd # c_max_text_len
	blo +
	; length > 12 = trim to 12
	ldb # c_max_text_len
/
	; length <= 12 = only use the lower byte (b)
	stb v_length
/
	lda , x+
	sta , u+
	decb
	bne -
/

	;
	; main routine: display and alter the string
	;
main:
	BIOS_Wait_Recal
	BIOS_Intensity_5F

	ldu # v_my_text
	ldab $00, -$70
	BIOS_Print_Str_d

	BIOS_Joy_Digital

	lda v_wait_release
	beq +
	; wait for joy-release
	lda V_Joy_1_X
	bne main
	lda V_Joy_1_Y
	bne main
	clr v_wait_release
/
	; check joy-movement
	lda V_Joy_1_X
	beq no_x
	bmi go_left

go_right:
	lda v_length
	; check max length
	cmpa # c_max_text_len
	beq main
	; add a new char
	ldx # v_my_text
	ldb # 'A'
	stb a, x
	inc v_length
	jmp calc_store_data

go_left:
	lda v_length
	; check min length
	deca
	beq main
	; remove last char
	ldx # v_my_text
	ldb # ' '
	stb a, x
	sta v_length
	jmp calc_store_data

no_x:
	; check joy-movement
	lda V_Joy_1_Y
	beq no_y
	bmi go_down
go_up:
	lda # 1
	bra +
go_down:
	lda # -1
/
	ldb v_length
	ldx # v_my_text-1
	adda b, x
	cmpa # 'A'-1
	bne +
	lda # 'Z'
/
	cmpa # 'Z'+1
	bne +
	lda # 'A'
/
	sta b, x
	jmp calc_store_data

no_y:
	BIOS_Read_Btns
	tsta
	beq main

	; mark for immediate restart
	lda # CUSTOMDATA_FLAG_DO_RESTART
	sta CUSTOMDATA_ADDR_FLAGS

	reset


calc_store_data:
	; next turn: wait release joystick button
	inc v_wait_release
	; make data invalid
	; (in case of a reset between here and the validation below no data is saved,
	;  which is probably better than corruped data)
	clr CUSTOMDATA_ADDR_TYPE
	; copy string
	clra
	ldb v_length
	std CUSTOMDATA_ADDR_LEN
	ldx # v_my_text
	ldu # CUSTOMDATA_AREA_START
	stu CUSTOMDATA_ADDR_ADDR
/
	ldb , x+
	stb , u+
	deca
	bne -
	; mark for save
	lda # CUSTOMDATA_TYPE_SAVE
	sta CUSTOMDATA_ADDR_TYPE
	; rerun main
	jmp main

custom_data_id:
	byt CUSTOMDATA_ID

text_no_cust_data:
	byt "NO CUSTOM DATA FOUND", $ff

d_music:
	adr $fee8
	adr $feb6
	byt $0, $80
	byt $0, $80

	;
	; game id (a 8 byte header and 16 byte id as the last bytes in the file)
	;

	byt GAME_ID_HEADER
	byt "CUSTOM DATA TEST"
