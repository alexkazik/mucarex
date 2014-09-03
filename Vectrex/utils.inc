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

	ifndef UTILS_INC
UTILS_INC = 1

	; libararies
	; - bin2ascii
	; - bin2hex
	; you may define UTILS_NO_BIN2HEX do exclude the function

	; round an float towards zero

round function val, sgn(val) * int(1.0*abs(val) + 0.5)

	; swap lo/hi byte (convert little <-> big endian)

swap function val, (((val)&$ff)<<8) | (((val)>>8)&$ff)

	; load a and b with an immediate (using "ldd #" - easier to use)

ldab macro a, b
	ldd # (((a) & $ff) << 8) | ((b) & $ff)
	endm

	; the opcode for reset

reset macro
	byt $3e
	endm

	; macro for set scale + move to
	; the scale is reduced, if possible without changing the total coordinates

Moveto_xys macro xx, yy, ss
x set xx
y set yy
s set ss

mxy set abs(x)
	if abs(y) > mxy
mxy set abs(y)
	endif

xn set round(1.0 * s / mxy)
yn set round(1.0 * s / mxy)

	if (s > mxy) && (xn*mxy == x*s) && (yn*mxy == y*s)
x set xn
y set yn
s set mxy
	endif

	lda # s
	sta VIA_t1_cnt_lo
	ldab y, x
	BIOS_Moveto_d
	endm

	endif
