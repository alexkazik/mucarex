<?php
	
	/*
	
	Copyright (c) Stefan Haddewig
	All rights reserved.
	
	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
	
	* Redistributions of source code must retain the above copyright notice, this
	  list of conditions and the following disclaimer.
	
	* Redistributions in binary form must reproduce the above copyright notice,
	  this list of conditions and the following disclaimer in the documentation
	  and/or other materials provided with the distribution.
	
	* Neither the names MuCaREX, p1x3l.net nor the names of its
	  contributors may be used to endorse or promote products derived from
	  this software without specific prior written permission.
	
	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
	
	*/
	
	$font = array(
		// internal: two line drawing
		chr(0x1e) => array(
			0, 9, 0,
		),
		chr(0x1f) => array(
			0, -9, 0,
		),
		// symbols
		' ' => array(
			0, 0, 10,
		),
		'-' => array(
			0, 6, 0,
			1, 0, 8,
			0, -6, 3,
		),
		'(' => array(
			0, -1, 2,
			1, 3, -2,
			1, 8, 0,
			1, 3, 2,
			0, -13, 6,
		),
		')' => array(
			0, -1, 3,
			1, 3, 2,
			1, 8, 0,
			1, 3, -2,
			0, -13, 5,
		),
		'\'' => array(
			0, 8, 0,
			1, 4, 1,
			0, -12, 3,
		),
		'"' => array(
			0, 8, 0,
			1, 4, 1,
			0, -4, 1,
			1, 4, 1,
			0, -12, 3,
		),
		'#' => array(
			0, 4, 0,
			1, 0, 10,
			0, 4, 0,
			1, 0, -10,
			0, 4, 3,
			1, -12, 0,
			0, 0, 4,
			1, 12, 0,
			0, -12, 6,
		),
		'.' => array(
			0, 0, 3,
			1, 2, 0,
			0, -2, 6,
		),
		':' => array(
			0, 0, 3,
			1, 2, 0,
			0, 5, 0,
			1, 2, 0,
			0, -9, 6,
		),
		'/' => array(
			1, 12, 6,
			0, -12, 3,
		),
		
		// numbers
		'0' => array(
			0, 10, 9,
			1, 2.5, -4.5,
			1, -2.5, -4.5,
			1, -8, 0,
			1, -2.5, 4.5,
			1, 2.5, 4.5,
			1, 8, 0,
			1, -8, -9,
			0, -2, 12,
		),
		'1' => array(
			0, 0, 3,
			1, 12, 0,
			1, 0, -2,
			0, -12, 7.5,
		),
		'2' => array(
			0, 0, 9,
			1, 0, -9,
			1, 3, 0,
			1, 3, 2,
			1, 0, 5,
			1, 3, 2,
			1, 3, -2,
			1, 0, -5,
			1, -3, -2,
			0, -9, 12,
		),
		'3' => array(
			0, 3, 0,
			1, -3, 2,
			1, 0, 5,
			1, 3, 2,
			1, 3, -2,
			1, 0, -3,
			0, 0, 3,
			1, 3, 2,
			1, 3, -2,
			1, 0, -5,
			1, -3, -2,
			0, -9, 12,
		),
		'4' => array(
			0, 0, 7,
			1, 12, 0,
			1, -8, -7,
			1, 0, 9,
			0, -4, 3,
		),
		'5' => array(
			0, 3, 0,
			1, -3, 2,
			1, 0, 5,
			1, 3, 2,
			1, 1, 0,
			1, 3, -2,
			1, 0, -6,
			1, 5, 1,
			1, 0, 7,
			0, -12, 3,
		),
		'6' => array(
			0, 11, 8,
			1, 1, -1,
			1, 0, -5,
			1, -3, -2,
			1, -6, 0,
			1, -3, 2,
			1, 0, 5,
			1, 3, 2,
			1, 1, 0,
			1, 3, -2,
			1, 0, -5,
			1, -3, -2,
			0, -4, 12,
		),
		'7' => array(
			0, 0, 2,
			1, 12, 6,
			1, 0, -9,
			0, -12, 11,
		),
		'8' => array(
			0, 6, 2,
			1, -3, -2,
			1, -3, 2,
			1, 0, 5.5,
			1, 3, 2,
			1, 3, -2,
			1, 0, -5.5,
			1, 3, -2,
			1, 3, 2,
			1, 0, 5.5,
			1, -3, 2,
			1, -3, -2,
			0, -6, 5,
		),
		'9' => array(
			0, 2, 0,
			1, -2, 2,
			1, 0, 5,
			1, 3, 2,
			1, 6, 0,
			1, 3, -2,
			1, 0, -5,
			1, -3, -2,
			1, -1, 0,
			1, -3, 2,
			1, 0, 5,
			1, 3, 2,
			0, -8, 3,
		),
		// letters
		'A' => array(
			0, 0, -1,
			1, 12, 5,
			1, -12, 5,
			1, 0, 0,
			0, 5, -2,
			1, 0, -6,
			0, -5, 10,
		),
		'B' => array(
			1, 12, 0,
			1, 0, 6,
			1, -3, 2,
			1, -3, -1,
			1, -3, 2,
			1, -3, -2,
			1, 0, -7,
			0, 6, 0,
			1, 0, 7,
			0, -6, 5,
		),
		'C' => array(
			0, 10, 9,
			1, 2.5, -4.5,
			1, -2.5, -4.5,
			1, 0-8, 0,
			1, -2.5, 4.5,
			1, 2.5, 4.5,
			0, -2, 3,
		),
		'D' => array(
			1, 12, 0,
			1, 0, 6.5,
			1, -3, 2,
			1, -6, 0,
			1, -3, -2,
			1, 0, -6.5,
			0, 0, 12,
		),
		'E' => array(
			0, 0, 7,
			1, 0, -7,
			1, 12, 0,
			1, 0, 7,
			0, -6, -2,
			1, 0, -5,
			0, -6, 10,
		),
		'F' => array(
			1, 12, 0,
			1, 0, 7,
			0, -6, -7,
			1, 0, 5,
			0, -6, 4,
		),
		'G' => array(
			0, 10, 9,
			1, 2.5, -4.5,
			1, -2.5, -4.5,
			1, 0-8, 0,
			1, -2.5, 4.5,
			1, 2.5, 4.5,
			1, 4, 0,
			1, 0, -4.5,
			0, -6, 7.5,
		),
		'H' => array(
			1, 12, 0,
			0, -6, 0,
			1, 0, 9,
			0, 6, 0,
			1, -12, 0,
			0, 0, 3,
		),
		'I' => array(
			0, 0, 2,
			1, 12, 0,
			1, 0, 0,
			0, -12, 5,
		),
		'J' => array(
			0, 3, -1,
			1, -3, 2,
			1, 0, 2,
			1, 3, 2,
			1, 9, 0,
			1, 0, -2,
			0, -12, 5,
		),
		'K' => array(
			1, 12, 0,
			0, -6, 0,
			1, 0, 4,
			1, 6, 4,
			0, -6, -4,
			1, -6, 4,
			0, 0, 3,
		),
		'L' => array(
			0, 12, 0,
			1, -12, 0,
			1, 0, 7,
			0, 0, 3,
		),
		'M' => array(
			1, 12, 0,
			1, -6, 5,
			1, 6, 5,
			1, -12, 0,
			1, 0, 0,
			0, 0, 3,
		),
		'N' => array(
			1, 12, 0,
			1, -12, 9,
			1, 12, 0,
			0, -12, 3,
		),
		'O' => array(
			0, 10, 9,
			1, 2.5, -4.5,
			1, -2.5, -4.5,
			1, -8, 0,
			1, -2.5, 4.5,
			1, 2.5, 4.5,
			1, 8, 0,
			0, -10, 3,
		),
		'P' => array(
			1, 12, 0,
			1, 0, 6,
			1, -3, 2,
			1, -3, -2,
			1, 0, -6,
			0, -6, 10.5,
		),
		'Q' => array(
			0, 10, 9,
			1, 2.5, -4.5,
			1, -2.5, -4.5,
			1, -8, 0,
			1, -2.5, 4.5,
			1, 2.5, 4.5,
			1, 8, 0,
			0, -8, -4,
			1, -2.5, 5,
			0, 0.5, 2,
		),
		'R' => array(
			1, 12, 0,
			1, 0, 6,
			1, -3, 2,
			1, -3, -2,
			1, -6, 3,
			0, 6, -9,
			1, 0, 6,
			0, -6, 6,
		),
		'S' => array(
			0, 2, 0,
			1, -2, 2,
			1, 0, 5,
			1, 3, 2,
			1, 3, -2,
			1, 0, -5,
			1, 3, -2,
			1, 3, 2,
			1, 0, 5,
			1, -1, 1,
			0, -11, 4,
		),
		'T' => array(
			0, 12, -1,
			1, 0, 8,
			1, 0, 0,
			0, 0, -4,
			1, -12, 0,
			1, 0, 0,
			0, 0, 6,
		),
		'U' => array(
			0, 12, 0,
			1, -9, 0,
			1, -3, 2,
			1, 0, 5,
			1, 3, 2,
			1, 9, 0,
			0, -12, 3,
		),
		'V' => array(
			0, 12, -1,
			1, -12, 5,
			1, 12, 5,
			0, -12, 2,
		),
		'W' => array(
			0, 12, -1,
			1, -12, 3,
			1, 7, 3,
			1, -7, 3,
			1, 12, 3,
			0, -12, 2,
		),
		'X' => array(
			1, 12, 10,
			1, 0, 0,
			0, 0, -10,
			1, -12, 10,
			1, 0, 0,
			0, 0, 3,
		),
		'Y' => array(
			0, 12, -1,
			1, -6, 5,
			1, 6, 5,
			0, -6, -5,
			1, -6, 0,
			0, 0, 7,
		),
		'Z' => array(
			0, 0, 8,
			1, 0, -8,
			1, 12, 8,
			1, 0, -8,
			0, -12, 11,
		),
		
		// specials
		'`' => array( // no width char
			0, 0, 0,
		),
		'a' => array( // box
			1, 12, 0,
			1, 0, 12,
			1, -12, 0,
			1, 0, -12,
			0, 0, 12+10,
		),
		'b' => array( // box, checked
			1, 12, 0,
			1, 0, 12,
			1, -12, 0,
			1, 0, -12,
			0, 6, 2,
			1, -4, 3,
			1, 8, 5,
			0, -10, 2+10,
		),
		'e' => array( // lower e
			0, 0, 6,
			1, 0, -4,
			1, 2, -2,
			1, 4, 0,
			1, 2, 2,
			1, 0, 3,
			1, -2, 2,
			1, -2, 0,
			1, 0, -7,
			0, -4, 10,
		),
		
		// unknown
		chr(0x80) => array(
			1, 12, 6,
			0, -12, 3,
		),
	);
	
?>