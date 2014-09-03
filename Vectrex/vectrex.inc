
        ifndef VECTREX_INC
VECTREX_INC = 1

	;
	; RAM
	;

V_Snd_Shadow  EQU     $C800   ;Shadow of sound chip registers (15 bytes)
V_Btn_State   EQU     $C80F   ;Current state of all joystick buttons
V_Prev_Btns   EQU     $C810   ;Previous state of all joystick buttons
V_Buttons     EQU     $C811   ;Current toggle state of all buttons
V_Button_1_1  EQU     $C812   ;Current toggle state of stick 1 button 1
V_Button_1_2  EQU     $C813   ;Current toggle state of stick 1 button 2
V_Button_1_3  EQU     $C814   ;Current toggle state of stick 1 button 3
V_Button_1_4  EQU     $C815   ;Current toggle state of stick 1 button 4
V_Button_2_1  EQU     $C816   ;Current toggle state of stick 2 button 1
V_Button_2_2  EQU     $C817   ;Current toggle state of stick 2 button 2
V_Button_2_3  EQU     $C818   ;Current toggle state of stick 2 button 3
V_Button_2_4  EQU     $C819   ;Current toggle state of stick 2 button 4
V_Joy_Resltn  EQU     $C81A   ;Joystick A/D resolution ($80=min $00=max)
V_Joy_1_X     EQU     $C81B   ;Joystick 1 left/right
V_Joy_1_Y     EQU     $C81C   ;Joystick 1 up/down
V_Joy_2_X     EQU     $C81D   ;Joystick 2 left/right
V_Joy_2_Y     EQU     $C81E   ;Joystick 2 up/down
V_Joy_Mux     EQU     $C81F   ;Joystick enable/mux flags (4 bytes)
V_Joy_Mux_1_X EQU     $C81F   ;Joystick 1 X enable/mux flag (=1)
V_Joy_Mux_1_Y EQU     $C820   ;Joystick 1 Y enable/mux flag (=3)
V_Joy_Mux_2_X EQU     $C821   ;Joystick 2 X enable/mux flag (=5)
V_Joy_Mux_2_Y EQU     $C822   ;Joystick 2 Y enable/mux flag (=7)
V_Misc_Count  EQU     $C823   ;Misc counter/flag byte, zero when not in use
V_0Ref_Enable EQU     $C824   ;Check0Ref enable flag
V_Loop_Count  EQU     $C825   ;Loop counter word (incremented in Wait_Recal)
V_Brightness  EQU     $C827   ;Default brightness
V_Dot_Dwell   EQU     $C828   ;Dot dwell time?
V_Pattern     EQU     $C829   ;Dot pattern (bits)
V_Text_HW     EQU     $C82A   ;Default text height and width
V_Text_Height EQU     $C82A   ;Default text height
V_Text_Width  EQU     $C82B   ;Default text width
V_Str_Ptr     EQU     $C82C   ;Temporary string pointer for Print_Str
V_Counters    EQU     $C82E   ;Six bytes of counters
V_Counter_1   EQU     $C82E   ;First  counter byte
V_Counter_2   EQU     $C82F   ;Second counter byte
V_Counter_3   EQU     $C830   ;Third  counter byte
V_Counter_4   EQU     $C831   ;Fourth counter byte
V_Counter_5   EQU     $C832   ;Fifth  counter byte
V_Counter_6   EQU     $C833   ;Sixth  counter byte
V_RiseRun_Tmp EQU     $C834   ;Temp storage word for rise/run
V_Angle       EQU     $C836   ;Angle for rise/run and rotation calculations
V_Run_Index   EQU     $C837   ;Index pair for run
;                     $C839   ;Pointer to copyright string during startup
V_Rise_Index  EQU     $C839   ;Index pair for rise
V_High_Score_F EQU    $C83B   ;High score cold-start flag (=0 if valid)
V_RiseRun_Len EQU     $C83B   ;length for rise/run
;                     $C83C   ;temp byte
V_Rfrsh       EQU     $C83D   ;Refresh time (divided by 1.5MHz)
V_Rfrsh_lo    EQU     $C83D   ;Refresh time low byte
V_Rfrsh_hi    EQU     $C83E   ;Refresh time high byte
V_Music_Work  EQU     $C83F   ;Music work buffer (14 bytes, backwards?)
V_Music_Wk_A  EQU     $C842   ;        register 10
;                     $C843   ;        register 9
;                     $C844   ;        register 8
V_Music_Wk_7  EQU     $C845   ;        register 7
V_Music_Wk_6  EQU     $C846   ;        register 6
V_Music_Wk_5  EQU     $C847   ;        register 5
;                     $C848   ;        register 4
;                     $C849   ;        register 3
;                     $C84A   ;        register 2
V_Music_Wk_1  EQU     $C84B   ;        register 1
;                     $C84C   ;        register 0
V_Freq_Table  EQU     $C84D   ;Pointer to note-to-frequency table (normally $FC8D)
V_Max_Players EQU     $C84F   ;Maximum number of players for Select_Game
V_Max_Games   EQU     $C850   ;Maximum number of games for Select_Game
V_ADSR_Table  EQU     $C84F   ;Storage for first music header word (ADSR table)
V_Twang_Table EQU     $C851   ;Storage for second music header word ('twang' table)
V_Music_Ptr   EQU     $C853   ;Music data pointer
V_Expl_ChanA  EQU     $C853   ;Used by Explosion_Snd - bit for first channel used?
V_Expl_Chans  EQU     $C854   ;Used by Explosion_Snd - bits for all channels used?
V_Music_Chan  EQU     $C855   ;Current sound channel number for Init_Music
V_Music_Flag  EQU     $C856   ;Music active flag ($00=off $01=start $80=on)
V_Duration    EQU     $C857   ;Duration counter for Init_Music
V_Music_Twang EQU     $C858   ;3 word 'twang' table used by Init_Music
V_Expl_1      EQU     $C858   ;Four bytes copied from Explosion_Snd's U-reg parameters
V_Expl_2      EQU     $C859   ;
V_Expl_3      EQU     $C85A   ;
V_Expl_4      EQU     $C85B   ;
V_Expl_Chan   EQU     $C85C   ;Used by Explosion_Snd - channel number in use?
V_Expl_ChanB  EQU     $C85D   ;Used by Explosion_Snd - bit for second channel used?
V_ADSR_Timers EQU     $C85E   ;ADSR timers for each sound channel (3 bytes)
V_Music_Freq  EQU     $C861   ;Storage for base frequency of each channel (3 words)
;                     $C85E   ;Scratch 'score' storage for Display_Option (7 bytes)
V_Expl_Flag   EQU     $C867   ;Explosion_Snd initialization flag?
;             $C868...$C876   ;Unused?
V_Expl_Timer  EQU     $C877   ;Used by Explosion_Snd
;                     $C878   ;Unused?
V_Num_Players EQU     $C879   ;Number of players selected in Select_Game
V_Num_Game    EQU     $C87A   ;Game number selected in Select_Game
V_Seed_Ptr    EQU     $C87B   ;Pointer to 3-byte random number seed (=$C87D)
V_Random_Seed EQU     $C87D   ;Default 3-byte random number seed
                              ;
;  $C880 - $CBEA is user RAM  ;
                              ;
V_Default_Stk EQU     $CBEA   ;Default top-of-stack
V_High_Score  EQU     $CBEB   ;High score storage (7 bytes)
V_SWI3_Vector EQU     $CBF2   ;SWI2/SWI3 interrupt vector (3 bytes)
V_SWI2_Vector EQU     $CBF2   ;SWI2/SWI3 interrupt vector (3 bytes)
V_FIRQ_Vector EQU     $CBF5   ;FIRQ interrupt vector (3 bytes)
V_IRQ_Vector  EQU     $CBF8   ;IRQ interrupt vector (3 bytes)
V_SWI_Vector  EQU     $CBFB   ;SWI/NMI interrupt vector (3 bytes)
V_NMI_Vector  EQU     $CBFB   ;SWI/NMI interrupt vector (3 bytes)
V_Cold_Flag   EQU     $CBFE   ;Cold start flag (warm start if = $7321)

	;
	; VIA
	;

VIA_port_b      EQU     $D000   ;VIA port B data I/O register
;       0 sample/hold (0=enable  mux 1=disable mux)
;       1 mux sel 0
;       2 mux sel 1
;       3 sound BC1
;       4 sound BDIR
;       5 comparator input
;       6 external device (slot pin 35) initialized to input
;       7 /RAMP
VIA_port_a      EQU     $D001   ;VIA port A data I/O register (handshaking)
VIA_DDR_b       EQU     $D002   ;VIA port B data direction register (0=input 1=output)
VIA_DDR_a       EQU     $D003   ;VIA port A data direction register (0=input 1=output)
VIA_t1_cnt_lo   EQU     $D004   ;VIA timer 1 count register lo (scale factor)
VIA_t1_cnt_hi   EQU     $D005   ;VIA timer 1 count register hi
VIA_t1_lch_lo   EQU     $D006   ;VIA timer 1 latch register lo
VIA_t1_lch_hi   EQU     $D007   ;VIA timer 1 latch register hi
VIA_t2_lo       EQU     $D008   ;VIA timer 2 count/latch register lo (refresh)
VIA_t2_hi       EQU     $D009   ;VIA timer 2 count/latch register hi
VIA_shift_reg   EQU     $D00A   ;VIA shift register
VIA_aux_cntl    EQU     $D00B   ;VIA auxiliary control register
;       0 PA latch enable
;       1 PB latch enable
;       2 \                     110=output to CB2 under control of phase 2 clock
;       3  > shift register control     (110 is the only mode used by the Vectrex ROM)
;       4 /
;       5 0=t2 one shot                 1=t2 free running
;       6 0=t1 one shot                 1=t1 free running
;       7 0=t1 disable PB7 output       1=t1 enable PB7 output
VIA_cntl        EQU     $D00C   ;VIA control register
;       0 CA1 control     CA1 -> SW7    0=IRQ on low 1=IRQ on high
;       1 \
;       2  > CA2 control  CA2 -> /ZERO  110=low 111=high
;       3 /
;       4 CB1 control     CB1 -> NC     0=IRQ on low 1=IRQ on high
;       5 \
;       6  > CB2 control  CB2 -> /BLANK 110=low 111=high
;       7 /
VIA_int_flags   EQU     $D00D   ;VIA interrupt flags register
;               bit                             cleared by
;       0 CA2 interrupt flag            reading or writing port A I/O
;       1 CA1 interrupt flag            reading or writing port A I/O
;       2 shift register interrupt flag reading or writing shift register
;       3 CB2 interrupt flag            reading or writing port B I/O
;       4 CB1 interrupt flag            reading or writing port A I/O
;       5 timer 2 interrupt flag        read t2 low or write t2 high
;       6 timer 1 interrupt flag        read t1 count low or write t1 high
;       7 IRQ status flag               write logic 0 to IER or IFR bit
VIA_int_enable  EQU     $D00E   ;VIA interrupt enable register
;       0 CA2 interrupt enable
;       1 CA1 interrupt enable
;       2 shift register interrupt enable
;       3 CB2 interrupt enable
;       4 CB1 interrupt enable
;       5 timer 2 interrupt enable
;       6 timer 1 interrupt enable
;       7 IER set/clear control
VIA_port_a_nohs EQU     $D00F   ;VIA port A data I/O register (no handshaking)

	;
	; built in music
	;

D_music1  EQU $FD0D
D_music2  EQU $FD1D
D_music3  EQU $FD81
D_music4  EQU $FDD3
D_music5  EQU $FE38
D_music6  EQU $FE76
D_music7  EQU $FEC6
D_music8  EQU $FEF8
D_music9  EQU $FF26
D_musica  EQU $FF44
D_musicb  EQU $FF62
D_musicc  EQU $FF7A
D_musicd  EQU $FF8F

D_copyright_str EQU $F101

	;
	; macros for DPR
	;

Set_DPR macro dpr
	if ASSUMEDVAL(DPR) <> dpr
		pshs a
		lda # dpr
		tfr a, dp
		assume DPR:dpr
		puls a
	endif
	endm

Set_DPR_kill_A macro dpr
	if ASSUMEDVAL(DPR) <> dpr
		lda # dpr
		tfr a, dp
		assume DPR:dpr
	endif
	endm

Set_DPR_kill_B macro dpr
	if ASSUMEDVAL(DPR) <> dpr
		ldb # dpr
		tfr b, dp
		assume DPR:dpr
	endif
	endm

	;
	; macros for bios function creation
	;

BIOS_Create_Set_DP_D0 macro name, addr
name macro
	jsr addr
	assume DPR:$d0
	endm
	endm

BIOS_Create_Set_DP_C8 macro name, addr
name macro
	jsr addr
	assume DPR:$c8
	endm
	endm

BIOS_Create_Chk_DP_D0 macro name, addr
name macro
	if ASSUMEDVAL(DPR) <> $d0
		error "the dp is not $d0"
	endif
	jsr addr
	endm
	endm

BIOS_Create_Chk_DP_C8 macro name, addr
name macro
	if ASSUMEDVAL(DPR) <> $c8
		error "the dp is not $c8"
	endif
	jsr addr
	endm
	endm

BIOS_Create_Any_DP macro name, addr
name macro
	jsr addr
	endm
	endm


	;
	; basic bios functions descriptions
	;

BIOS_Cold_Start macro
	jmp $F000
	endm

BIOS_Warm_Start macro
	jmp $F06C
	endm

	BIOS_Create_Set_DP_D0 BIOS_Init_VIA,         $F14C    ;
	BIOS_Create_Set_DP_C8 BIOS_Init_OS_RAM,      $F164    ;
	BIOS_Create_Set_DP_D0 BIOS_Init_OS,          $F18B    ;
	BIOS_Create_Set_DP_D0 BIOS_Wait_Recal,       $F192    ;
	BIOS_Create_Chk_DP_D0 BIOS_Set_Refresh,      $F1A2    ;
	BIOS_Create_Set_DP_D0 BIOS_DP_to_D0,         $F1AA    ;
	BIOS_Create_Set_DP_C8 BIOS_DP_to_C8,         $F1AF    ;
	BIOS_Create_Chk_DP_D0 BIOS_Read_Btns_Mask,   $F1B4    ;
	BIOS_Create_Chk_DP_D0 BIOS_Read_Btns,        $F1BA    ;
	BIOS_Create_Chk_DP_D0 BIOS_Joy_Analog,       $F1F5    ;
	BIOS_Create_Chk_DP_D0 BIOS_Joy_Digital,      $F1F8    ;
	BIOS_Create_Chk_DP_D0 BIOS_Sound_Byte,       $F256    ;
	BIOS_Create_Chk_DP_D0 BIOS_Sound_Byte_x,     $F259    ;
	BIOS_Create_Chk_DP_D0 BIOS_Sound_Byte_raw,   $F25B    ;
	BIOS_Create_Chk_DP_D0 BIOS_Clear_Sound,      $F272    ;
	BIOS_Create_Chk_DP_D0 BIOS_Sound_Bytes,      $F27D    ;
	BIOS_Create_Chk_DP_D0 BIOS_Sound_Bytes_x,    $F284    ;
	BIOS_Create_Chk_DP_D0 BIOS_Do_Sound,         $F289    ;
	BIOS_Create_Chk_DP_D0 BIOS_Do_Sound_x,       $F28C    ;
	BIOS_Create_Chk_DP_D0 BIOS_Intensity_1F,     $F29D    ;
	BIOS_Create_Chk_DP_D0 BIOS_Intensity_3F,     $F2A1    ;
	BIOS_Create_Chk_DP_D0 BIOS_Intensity_5F,     $F2A5    ;
	BIOS_Create_Chk_DP_D0 BIOS_Intensity_7F,     $F2A9    ;
	BIOS_Create_Chk_DP_D0 BIOS_Intensity_a,      $F2AB    ;
	BIOS_Create_Chk_DP_D0 BIOS_Dot_ix_b,         $F2BE    ;
	BIOS_Create_Chk_DP_D0 BIOS_Dot_ix,           $F2C1    ;
	BIOS_Create_Chk_DP_D0 BIOS_Dot_d,            $F2C3    ;
	BIOS_Create_Chk_DP_D0 BIOS_Dot_here,         $F2C5    ;
	BIOS_Create_Chk_DP_D0 BIOS_Dot_List,         $F2D5    ;
	BIOS_Create_Chk_DP_D0 BIOS_Dot_List_Reset,   $F2DE    ;
	BIOS_Create_Chk_DP_D0 BIOS_Recalibrate,      $F2E6    ;
	BIOS_Create_Chk_DP_D0 BIOS_Moveto_x_7F,      $F2F2    ;
	BIOS_Create_Chk_DP_D0 BIOS_Moveto_d_7F,      $F2FC    ;
	BIOS_Create_Chk_DP_D0 BIOS_Moveto_ix_FF,     $F308    ;
	BIOS_Create_Chk_DP_D0 BIOS_Moveto_ix_7F,     $F30C    ;
	BIOS_Create_Chk_DP_D0 BIOS_Moveto_ix_b,      $F30E    ;
	BIOS_Create_Chk_DP_D0 BIOS_Moveto_ix,        $F310    ;
	BIOS_Create_Chk_DP_D0 BIOS_Moveto_d,         $F312    ;
	BIOS_Create_Set_DP_D0 BIOS_Reset0Ref_D0,     $F34A    ;
	BIOS_Create_Chk_DP_D0 BIOS_Check0Ref,        $F34F    ;
	BIOS_Create_Chk_DP_D0 BIOS_Reset0Ref,        $F354    ;
	BIOS_Create_Chk_DP_D0 BIOS_Reset_Pen,        $F35B    ;
	BIOS_Create_Chk_DP_D0 BIOS_Reset0Int,        $F36B    ;
	BIOS_Create_Chk_DP_D0 BIOS_Print_Str_hwyx,   $F373    ;
	BIOS_Create_Chk_DP_D0 BIOS_Print_Str_yx,     $F378    ;
	BIOS_Create_Chk_DP_D0 BIOS_Print_Str_d,      $F37A    ;
	BIOS_Create_Chk_DP_D0 BIOS_Print_List_hw,    $F385    ;
	BIOS_Create_Chk_DP_D0 BIOS_Print_List,       $F38A    ;
	BIOS_Create_Chk_DP_D0 BIOS_Print_List_chk,   $F38C    ;
	BIOS_Create_Chk_DP_D0 BIOS_Print_Ships_x,    $F391    ;
	BIOS_Create_Chk_DP_D0 BIOS_Print_Ships,      $F393    ;
	BIOS_Create_Chk_DP_D0 BIOS_Mov_Draw_VLc_a,   $F3AD    ;count y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Mov_Draw_VL_b,    $F3B1    ;y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Mov_Draw_VLcs,    $F3B5    ;count scale y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Mov_Draw_VL_ab,   $F3B7    ;y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Mov_Draw_VL_a,    $F3B9    ;y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Mov_Draw_VL,      $F3BC    ;y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Mov_Draw_VL_d,    $F3BE    ;y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Draw_VLc,         $F3CE    ;count y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Draw_VL_b,        $F3D2    ;y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Draw_VLcs,        $F3D6    ;count scale y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Draw_VL_ab,       $F3D8    ;y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Draw_VL_a,        $F3DA    ;y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Draw_VL,          $F3DD    ;y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Draw_Line_d,      $F3DF    ;y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Draw_VLp_FF,      $F404    ;pattern y x pattern y x ... $01
	BIOS_Create_Chk_DP_D0 BIOS_Draw_VLp_7F,      $F408    ;pattern y x pattern y x ... $01
	BIOS_Create_Chk_DP_D0 BIOS_Draw_VLp_scale,   $F40C    ;scale pattern y x pattern y x ... $01
	BIOS_Create_Chk_DP_D0 BIOS_Draw_VLp_b,       $F40E    ;pattern y x pattern y x ... $01
	BIOS_Create_Chk_DP_D0 BIOS_Draw_VLp,         $F410    ;pattern y x pattern y x ... $01
	BIOS_Create_Chk_DP_D0 BIOS_Draw_Pat_VL_a,    $F434    ;y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Draw_Pat_VL,      $F437    ;y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Draw_Pat_VL_d,    $F439    ;y x y x ...
	BIOS_Create_Chk_DP_D0 BIOS_Draw_VL_mode,     $F46E    ;mode y x mode y x ... $01
	BIOS_Create_Chk_DP_D0 BIOS_Print_Str,        $F495    ;
	BIOS_Create_Any_DP    BIOS_Random_3,         $F511    ;
	BIOS_Create_Any_DP    BIOS_Random,           $F517    ;
	BIOS_Create_Any_DP    BIOS_Init_Music_Buf,   $F533    ;
	BIOS_Create_Any_DP    BIOS_Clear_x_b,        $F53F    ;
	BIOS_Create_Any_DP    BIOS_Clear_C8_RAM,     $F542    ;never used by GCE carts?
	BIOS_Create_Any_DP    BIOS_Clear_x_256,      $F545    ;
	BIOS_Create_Any_DP    BIOS_Clear_x_d,        $F548    ;
	BIOS_Create_Any_DP    BIOS_Clear_x_b_80,     $F550    ;
	BIOS_Create_Any_DP    BIOS_Clear_x_b_a,      $F552    ;
	BIOS_Create_Any_DP    BIOS_Dec_3_Counters,   $F55A    ;
	BIOS_Create_Any_DP    BIOS_Dec_6_Counters,   $F55E    ;
	BIOS_Create_Any_DP    BIOS_Dec_Counters,     $F563    ;
	BIOS_Create_Any_DP    BIOS_Delay_3,          $F56D    ;30 cycles
	BIOS_Create_Any_DP    BIOS_Delay_2,          $F571    ;25 cycles
	BIOS_Create_Any_DP    BIOS_Delay_1,          $F575    ;20 cycles
	BIOS_Create_Any_DP    BIOS_Delay_0,          $F579    ;12 cycles
	BIOS_Create_Any_DP    BIOS_Delay_b,          $F57A    ;5*B + 10 cycles
	BIOS_Create_Any_DP    BIOS_Delay_RTS,        $F57D    ;5 cycles
	BIOS_Create_Any_DP    BIOS_Bitmask_a,        $F57E    ;
	BIOS_Create_Any_DP    BIOS_Abs_a_b,          $F584    ;
	BIOS_Create_Any_DP    BIOS_Abs_b,            $F58B    ;
	BIOS_Create_Chk_DP_C8 BIOS_Rise_Run_Angle,   $F593    ;
	BIOS_Create_Any_DP    BIOS_Get_Rise_Idx,     $F5D9    ;
	BIOS_Create_Any_DP    BIOS_Get_Run_Idx,      $F5DB    ;
	BIOS_Create_Chk_DP_C8 BIOS_Rise_Run_Idx,     $F5EF    ;
	BIOS_Create_Chk_DP_C8 BIOS_Rise_Run_X,       $F5FF    ;
	BIOS_Create_Chk_DP_C8 BIOS_Rise_Run_Y,       $F601    ;
	BIOS_Create_Chk_DP_C8 BIOS_Rise_Run_Len,     $F603    ;
	BIOS_Create_Set_DP_C8 BIOS_Rot_VL_ab,        $F610    ;
	BIOS_Create_Set_DP_C8 BIOS_Rot_VL,           $F616    ;
	BIOS_Create_Chk_DP_C8 BIOS_Rot_VL_Mode_a,    $F61F    ;
	BIOS_Create_Chk_DP_C8 BIOS_Rot_VL_M_dft,     $F62B    ;
	BIOS_Create_Chk_DP_C8 BIOS_Xform_Run_a,      $F65B    ;
	BIOS_Create_Chk_DP_C8 BIOS_Xform_Run,        $F65D    ;
	BIOS_Create_Chk_DP_C8 BIOS_Xform_Rise_a,     $F661    ;
	BIOS_Create_Chk_DP_C8 BIOS_Xform_Rise,       $F663    ;
	BIOS_Create_Any_DP    BIOS_Move_Mem_a_1,     $F67F    ;
	BIOS_Create_Any_DP    BIOS_Move_Mem_a,       $F683    ;
	BIOS_Create_Chk_DP_C8 BIOS_Init_Music_chk,   $F687    ;
	BIOS_Create_Chk_DP_C8 BIOS_Init_Music,       $F68D    ;
	BIOS_Create_Chk_DP_C8 BIOS_Init_Music_dft,   $F692    ;
	BIOS_Create_Set_DP_C8 BIOS_Select_Game,      $F7A9    ;
	BIOS_Create_Chk_DP_D0 BIOS_Display_Option,   $F835    ;
	BIOS_Create_Any_DP    BIOS_Clear_Score,      $F84F    ;
	BIOS_Create_Any_DP    BIOS_Add_Score_a,      $F85E    ;
	BIOS_Create_Any_DP    BIOS_Add_Score_d,      $F87C    ;
	BIOS_Create_Any_DP    BIOS_Strip_Zeros,      $F8B7    ;
	BIOS_Create_Any_DP    BIOS_Compare_Score,    $F8C7    ;
	BIOS_Create_Any_DP    BIOS_New_High_Score,   $F8D8    ;
	BIOS_Create_Any_DP    BIOS_Obj_Will_Hit_u,   $F8E5    ;
	BIOS_Create_Any_DP    BIOS_Obj_Will_Hit,     $F8F3    ;
	BIOS_Create_Any_DP    BIOS_Obj_Hit,          $F8FF    ;
	BIOS_Create_Chk_DP_C8 BIOS_Explosion_Snd,    $F92E    ;
	BIOS_Create_Chk_DP_D0 BIOS_Draw_Grid_VL,     $FF9F    ;


	;
	; some combined macros
	;

BIOS_Reset0Ref_AUTO macro
	if ASSUMEDVAL(DPR) = $d0
		jsr $F354 ; BIOS_Reset0Ref
	else
		jsr $F34a ; BIOS_Reset0Ref_D0
		assume DPR:$d0
	endif
	endm


BIOS_Intensity macro i
	if i = $1f
		BIOS_Intensity_1F
	elseif i = $3f
		BIOS_Intensity_3F
	elseif i = $5f
		BIOS_Intensity_5F
	elseif i = $7f
		BIOS_Intensity_7F
	else
		lda # i
		BIOS_Intensity_a
	endif
	endm


	endif
