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
#include <stdlib.h>
#include <string.h>

#include "mdir.h"

uint8_t global_buffer[GLOBAL_BUFFER_LENGTH];

struct dir_category *add_new_category(struct dir_category **cat){
	struct dir_category *new_cat = malloc(sizeof(struct dir_category));
	
	if(!new_cat){
		return NULL;
	}
	
	new_cat->next = NULL;
	new_cat->first = NULL;
	
	if(*cat == NULL){
		*cat = new_cat;
	}else{
		struct dir_category *last_cat = *cat;
		while(last_cat->next){
			last_cat = last_cat->next;
		}
		last_cat->next = new_cat;
	}
	
	return new_cat;
}

struct dir_entry *add_new_entry(struct dir_category *cat){
	struct dir_entry *new_ent = malloc(sizeof(struct dir_entry));
	
	if(!new_ent){
		return NULL;
	}
	
	new_ent->next = NULL;
	new_ent->data = NULL;
	
	if(cat->first == NULL){
		cat->first = new_ent;
	}else{
		struct dir_entry *last_ent = cat->first;
		while(last_ent->next){
			last_ent = last_ent->next;
		}
		last_ent->next = new_ent;
	}
	
	return new_ent;
}

void free_category(struct dir_category *cat){
	while(cat){
		struct dir_category *next_cat = cat->next;
		struct dir_entry *ent = cat->first;
		while(ent){
			struct dir_entry *next_ent = ent->next;
			if(ent->data){
				free(ent->data);
			}
			free(ent);
			ent = next_ent;
		}
		free(cat);
		cat = next_cat;
	}
}

void trim_modules(struct dir_category *cat){
	memset(global_buffer, 0xff, BANK_SIZE);
	memset(global_buffer+BANK_SIZE, 0x00, BANK_SIZE);
	
	while(cat){
		struct dir_entry *ent = cat->first;
		while(ent){
			int new_num_banks = ent->numbanks;
			int mode = ent->data[new_num_banks * BANK_SIZE - 1] == 0x00 ? 0 : 0xff;
			while(new_num_banks > 0 && 0 == memcmp(ent->data + (new_num_banks-1) * BANK_SIZE, global_buffer + (mode == 0x00 ? BANK_SIZE : 0), BANK_SIZE)){
				new_num_banks--;
			}
		
			if(new_num_banks != ent->numbanks){
				fprintf(stderr, "Notice: Trimmed %s from %d to %d by %d KiB, fill byte : 0x%02x\n", ent->name, ent->numbanks*BANK_SIZE/1024, new_num_banks*BANK_SIZE/1024, (ent->numbanks-new_num_banks)*BANK_SIZE/1024, mode);
				ent->numbanks = new_num_banks;
				ent->fill_byte = mode;
			}
			
			ent = ent->next;
		}
		
		cat = cat->next;
	}
	
}

