/*

Copyright (c) 2014 ALeX Kazik
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

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <math.h>
#include <stdlib.h>

#include "mdir.h"
#include "launcher.h"

const uint8_t crt_header[] = {0x67, 0x20, 0x47, 0x43, 0x45, 0x20}; // "g GCE "
const uint8_t vmc_header[] = {0x20, 0x0a, 0x4d, 0x44, 0x69, 0x72}; // bra start; text "MDir"

void extract_launcher(const uint8_t *indata, const int length, struct launcher_data *data){
	uint16_t font_ptr;
	
	if(length >= MAX_LAUNCHER_LEN){
		memcpy(data->bin, indata, MAX_LAUNCHER_LEN);
	}else{
		memcpy(data->bin, indata, length);
		memset(data->bin+length, 0xff, MAX_LAUNCHER_LEN-length);
	}
	
	// check vectrex cartridge header
	if(memcmp(data->bin+0, crt_header, 6) || data->bin[10] < 0x80){
		fprintf(stderr, "Error: invalid cartridge header\n");
		exit(1);
	
	}
	
	// skip vectrex cartridge header
	int pos = 11+2; // header + music ptr
	
	// skip texts
	do{
		pos += 4; // skip coords
		// search end of string
		while(data->bin[pos] < 0x80){
			pos++;
			if(pos > MAX_LAUNCHER_LEN/2){
				fprintf(stderr, "Error: can't find the end of header texts\n");
				exit(1);
			}
		}
		// skip end of string marker
		pos++;
		// loop until
	}while(data->bin[pos] != 0x00);
	// skip end of all strings marker
	pos++;
	
	// check vectrex cartridge header
	if(memcmp(data->bin+pos, vmc_header, 6)){
		fprintf(stderr, "Error: directory header not found\n");
		exit(1);
	}
	
	data->version = ntohs(*(uint16_t*)(data->bin+pos+6));
	font_ptr = ntohs(*(uint16_t*)(data->bin+pos+8));
	data->dir_ptr = ntohs(*(uint16_t*)(data->bin+pos+10));
	
	if(font_ptr < pos || font_ptr > data->dir_ptr){
		fprintf(stderr, "Error: can't find the font\n");
		exit(1);
	}
	if(data->dir_ptr < font_ptr || data->dir_ptr > MAX_LAUNCHER_LEN/2){
		fprintf(stderr, "Error: can't find the directory\n");
		exit(1);
	}
	
	for(int i=0x20; i<=0x5f; i++){
		uint16_t char_addr = ntohs(*(uint16_t*)(data->bin+font_ptr+(i-64)*2));
		if(char_addr < pos || char_addr > data->dir_ptr){
			fprintf(stderr, "Error: can't find the font\n");
			exit(1);
		}
		
		int width = 0;
		while(data->bin[char_addr] != 0x01){
			if(char_addr < pos || char_addr > data->dir_ptr){
				fprintf(stderr, "Error: can't find the font\n");
				exit(1);
			}
			width += (int8_t) data->bin[char_addr+2];
			char_addr += 3;
		}
		
		data->char_width[i] = char_addr > font_ptr ? (0x8000 | width) : width;
	}
}

uint8_t string_width(struct launcher_data *data, uint8_t *string, int scale){
	int width = 0;
	uint8_t c;
	uint8_t *s = string;
	while((c = *s++)){
		uint16_t w = data->char_width[c];
		if(w & 0x8000){
			fprintf(stderr, "Notice: char '%c' (in string \"%s\") is not in the font, a replacement will be shown\n", c, string);
			w &= 0x7fff;
		}
		width += w;
	}
	width = ((scale == MDIR_SCALE_HEAD ? 1.1 : 1.15) * width * scale) / 2;
	width = -round(width / 126);
	if(width < -127){
		return -127;
	}else{
		return width;
	}
}
