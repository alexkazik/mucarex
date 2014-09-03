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

#ifndef MDIR_H
#define MDIR_H

#include <stdint.h>

#define BANK_SIZE 4096
#define TOTAL_MODULE_SIZE (1024*1024)

#define MDIR_CAT_LENGTH 32
#define MDIR_CAT_FLAGS 0
#define MDIR_CAT_ENT_PTR 1
#define MDIR_CAT_NAME 3
#define MAX_CAT_NAME_LENGTH (MDIR_CAT_LENGTH - 4)

struct dir_category {
	// internal pointers
	struct dir_category *next;
	struct dir_entry *first;

	// has to be always valid
	uint8_t name[MDIR_CAT_LENGTH]; // must be smaller
	uint8_t name2[MDIR_CAT_LENGTH]; // must be smaller
};


#define MDIR_ENT_LENGTH 48
#define MDIR_ENT_FLAGS 0
#define MDIR_ENT_BANK 1
#define MDIR_ENT_NAME 2
#define MDIR_ENT_SIZE (MDIR_ENT_LENGTH - (4+16))
#define MAX_ENT_NAME_LENGTH (MDIR_ENT_LENGTH - (5+16))
#define MDIR_ENT_GAME_ID (MDIR_ENT_LENGTH - 16)

struct dir_entry {
	// internal pointers
	struct dir_entry *next;

	// has to be always valid
	uint8_t name[MDIR_ENT_LENGTH]; // must be smaller
	int32_t filesize;
	uint16_t numbanks;
	uint8_t *data; // must be at least max(filesize, numbanks*BANK_SIZE)
	uint8_t fill_byte;
	uint8_t game_id[16];
};


// common flags
#define MDIR_FLAG_FIRST   0x80
#define MDIR_FLAG_SECOND  0x40
#define MDIR_FLAG_SECLAST 0x20
#define MDIR_FLAG_LAST    0x10
#define MDIR_FLAG_MODE    0x03

#define MDIR_MODE_32K  0x00
#define MDIR_MODE_64K  0x01
#define MDIR_MODE_SRAM 0x02
#define MDIR_MODE_PAGE 0x03

// font-size
#define MDIR_SCALE_HEAD	12*2
#define MDIR_SCALE_BODY	8*2


// global buffer
#define GLOBAL_BUFFER_LENGTH TOTAL_MODULE_SIZE

extern uint8_t global_buffer[];
#define char_global_buffer ((char*) global_buffer)

// functions
struct dir_category *add_new_category(struct dir_category **cat);
struct dir_entry *add_new_entry(struct dir_category *cat);
void trim_modules(struct dir_category *cat);

void free_category(struct dir_category *cat);

#endif
