<?php
	
	/*
	
	Copyright (c) ALeX Kazik
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
	
	$PRESCALE = 5;
	
	require_once('font_dat.php');
	
	uksort($font, function($a, $b){
		return ord($a) - ord($b);
	});
	
	$out_all = ''; $out = '';
	$width = array();
	$min_char = 0x20; $max_char = 0x5f;
	$total_width = 0;
	foreach($font AS $char => $def){
		$out_all .= $out;
		$out = '';
		if(count($def) == 0){
			unset($font[$char]);
			continue;
		}
		$char = ord($char);
		if($char != 0x80){
			$min_char = min($min_char, $char);
			$max_char = max($max_char, $char);
		}
		$out .= 'char_'.($char == 0x80 ? 'un' : sprintf('%02x', $char)).':'."\n";
		$tx = 0;
		for($i=0; $i<count($def); $i+=3){
			$dx = $def[$i+2]*$PRESCALE;
			$dy = $def[$i+1]*$PRESCALE;
			$scale = 1;
			while(round($dx/$scale) < -128 || round($dx/$scale) > 127 || round($dy/$scale) < -128 || round($dy/$scale) > 127){
				$scale ++;
				if($scale == 3){
					$scale = 4;
				}
			}
			$lx = 0;
			$ly = 0;
			for($j=0; $j<$scale; $j++){
				$x = round(($j+1)*$dx/$scale) - $lx;
				$y = round(($j+1)*$dy/$scale) - $ly;
				$lx += $x;
				$ly += $y;
				$tx += $x;
				$out .= "\t".'byt '.sprintf('$%02x, %4d, %4d', $def[$i] ? 0xff : 0, $y, $x)."\n";
			}
		}
		$out .= "\t".'byt $01'."\n";
		$out .= "\t".'; width '.$tx."\n";
		$width[$char] = $tx;
		if(ord($char) >= 0x20){
			$total_width += $tx / $PRESCALE;
		}
		echo ($char >= 0x20 && $char <= 0x7e ? chr($char) : sprintf('0x%02x', $char)).': '.sprintf('%2d', count($def)/3).' vectors, width: '.($tx/10)."\n";
	}
	
	for($i=$min_char; $i<=$max_char; $i++){
		if(isset($font[chr($i)])){
			$c = 'char_'.sprintf('%02x', $i);
		}else{
			$c = 'char_un';
		}
		if($i < 0x40){
			$tabLO[$i] = $c;
		}else{
			$tabHI[$i] = $c;
		}
		if(!isset($width[$i])){
			$width[$i] = $width[0x80];
		}
	}
	
	file_put_contents('font.lib',
		"\tsection font_lib\n".
		"\tpublic t_font\n".
		$out_all."\n\n".
		out_tab($tabLO).
		't_font:'."\n".
		out_tab($tabHI)."\n".
		$out."\n".
		"\tendsection\n"
	);
	
	$scale = 10;
	$yofs = 13; // left-top align
	$ysize = 14;
	$img = imagecreate((2+$total_width) * $scale, $ysize * $scale);
	$col_bg = imagecolorallocate($img, 0, 0, 0);
	$col_fg = imagecolorallocate($img, 255, 255, 255);
	$col_sep = imagecolorallocate($img, 128, 0, 0);
	$posx = 1;
	foreach($font AS $char => $def){
		if(ord($char) < 0x20){
			continue;
		}
		imageline($img, $posx*$scale, 0, $posx*$scale, $ysize*$scale-1, $col_sep);
		$posy = $yofs;
		for($i=0; $i<count($def); $i+=3){
			$fromx = $posx;
			$fromy = $posy;
			$posy -= $def[$i+1]; // reverse y
			$posx += $def[$i+2];
			if($def[$i+0]){
				imageline($img, $fromx*$scale, $fromy*$scale, $posx*$scale, $posy*$scale, $col_fg);
			}
		}
		imageline($img, ($posx-3)*$scale, 0, ($posx-3)*$scale, 1*$scale-1, $col_sep);
		imageline($img, ($posx-3)*$scale, ($ysize-1)*$scale+1, ($posx-3)*$scale, $ysize*$scale-1, $col_sep);
		imageline($img, ($posx-3)*$scale, $posy*$scale, ($posx)*$scale, $posy*$scale, $col_sep);
	}
	imageline($img, $posx*$scale, 0, $posx*$scale, $ysize*$scale-1, $col_sep);
	imagepng($img, 'font.png');
	
	
	
	function out_tab($t){
		$o = '';
		reset($t);
		$min = key($t);
		for($i=$min & 0xf8; $i < $min || isset($t[$i]); $i+=8){
			$l = '';
			$c = '';
			for($j=0; $j<8; $j++){
				if(isset($t[$i+$j])){
					$l .= $t[$i+$j].(isset($t[$i+$j+1]) && $j<7 ? ',' : ' ').' ';
				}else{
					$l .= '         ';
				}
				if($i+$j >= 0x20 && $i+$j <= 0x7e){
					$c .= chr($i+$j);
				}else{
					$c .= '.';
				}
			}
			$o .= "\t".'adr '.$l.'; '.$c."\n";
		}
		return $o;
	}
	
?>