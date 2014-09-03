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

#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>

#include "binary.h"
#include "launcher.h"
#include "mdir.h"

/*
** helper functions
*/

int read_data(char *filename, FILE *in, uint8_t *buffer, int maxlength){
	int filesize = 0;
	if(in == NULL){
		in = fopen(filename, "rb");
		if(!in){
			fprintf(stderr, "Error: error opening the file \"%s\": %s\n", filename, strerror(errno));
			exit(1);
		}
	}
	while(!feof(in) && filesize < maxlength){
		int n = fread(buffer+filesize, 1, maxlength-filesize, in);
		if(n < 0){
			fclose(in);
			fprintf(stderr, "Error: error reading file \"%s\": %s\n", filename, strerror(errno));
			exit(1);
		}
		filesize += n;
	}
	
	uint8_t tmpbuf;
	if(!feof(in) && fread(&tmpbuf, 1, 1, in) == 1){
		fclose(in);
		fprintf(stderr, "Error: error reading file \"%s\": file too large (%d)\n", filename, maxlength);
		exit(1);
	}
	
	fclose(in);
	return filesize;
}

void write_data(char *filename, FILE *out, uint8_t *buffer, int length){
	if(out == NULL){
		out = fopen(filename, "wb");
		if(!out){
			fprintf(stderr, "Error: error opening the file \"%s\": %s\n", filename, strerror(errno));
			exit(1);
		}
	}
	int n = fwrite(buffer, 1, length, out);
	if(n < 0){
		fclose(out);
		fprintf(stderr, "Error: error reading file \"%s\": %s\n", filename, strerror(errno));
		exit(1);
	}
}

/*
** input
*/

struct dir_category *binary_in(char *filename, struct launcher_data *launcher){
	int filesize;
	
	if(strcmp(filename, "-") == 0){
		filesize = read_data("stdin", stdin, global_buffer, TOTAL_MODULE_SIZE);
	}else{
		filesize = read_data(filename, NULL, global_buffer, TOTAL_MODULE_SIZE);
	}
	
	return binary_parse_in(launcher, filesize);
}

struct dir_category *split_in(char *filename_lo, char *filename_hi, struct launcher_data *launcher){
	int filesize_lo, filesize_hi;
	
	filesize_lo = read_data(filename_lo, NULL, global_buffer, TOTAL_MODULE_SIZE/2);
	filesize_hi = read_data(filename_hi, NULL, global_buffer+TOTAL_MODULE_SIZE/2, TOTAL_MODULE_SIZE/2);
	
	if(filesize_lo != TOTAL_MODULE_SIZE/2 && filesize_hi){
		fprintf(stderr, "Error: error reading file \"%s\", \"%s\": hirom should be empty since lorom is not full", filename_lo, filename_hi);
		exit(1);
	}
	
	return binary_parse_in(launcher, filesize_lo+filesize_hi);
}

/*
** output
*/

void binary_out(char *filename, struct launcher_data *launcher, struct dir_category *root, int enable_1mb){
	uint32_t length = binary_gen_out(launcher, root, enable_1mb);
	
	if(strcmp(filename, "-") == 0){
		write_data("stdout", stdout, global_buffer, length);
	}else{
		write_data(filename, NULL, global_buffer, length);
	}
}

void split_out(char *filename_lo, char *filename_hi, struct launcher_data *launcher, struct dir_category *root, int enable_1mb){
	uint32_t length = binary_gen_out(launcher, root, enable_1mb);
	uint32_t length_lo = length < TOTAL_MODULE_SIZE/2 ? length : TOTAL_MODULE_SIZE/2;
	uint32_t length_hi = length - length_lo;
	
	write_data(filename_lo, NULL, global_buffer, length_lo);
	write_data(filename_hi, NULL, global_buffer+TOTAL_MODULE_SIZE/2, length_hi);
}

const uint8_t ef_crt_header[0x40] = {
	0x43, 0x36, 0x34, 0x20, 0x43, 0x41, 0x52, 0x54, 0x52, 0x49, 0x44, 0x47, 0x45, 0x20, 0x20, 0x20,
	0x00, 0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x56, 0x45, 0x43, 0x54, 0x52, 0x45, 0x58, 0x20, 0x53, 0x4f, 0x46, 0x54, 0x57, 0x41, 0x52, 0x45,
	0x20, 0x2d, 0x20, 0x4e, 0x4f, 0x54, 0x20, 0x46, 0x4f, 0x52, 0x20, 0x43, 0x36, 0x34, 0x00, 0x00
};

const uint8_t ef_chip_header[0x10] = {
	0x43, 0x48, 0x49, 0x50, 0x00, 0x00, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00,
};

void easyflash_out(char *filename, struct launcher_data *launcher, struct dir_category *root, int enable_1mb){
	uint32_t length = binary_gen_out(launcher, root, enable_1mb);
	
	uint8_t *buffer = malloc(TOTAL_MODULE_SIZE + 0x40 + 2*64*0x10);
	
	// c64-crt header
	memcpy(buffer, ef_crt_header, 0x40);
	uint32_t pos = 0x40;
	uint32_t bank = 0; // 4k mucarex banks, not easyflash banks
	
	while(bank*BANK_SIZE < length){
		// copy chip-header
		memcpy(buffer+pos, ef_chip_header, 0x10);
		// set address (lo/hi chip)
		buffer[pos+0xc] = bank*BANK_SIZE < 512*1024 ? 0x80 : 0xa0;
		// set bank
		buffer[pos+0xb] = (bank/2) & 0x3f;
		pos += 0x10;
		// copy bank
		memcpy(buffer+pos, global_buffer+bank*BANK_SIZE, 8192);
		pos += 8192;
		bank += 2;
	}
	
	write_data(filename, NULL, buffer, pos);
	free(buffer);
}

/*
** generate/parse binary from/to binary
*/

struct dir_category *binary_parse_in(struct launcher_data *launcher, uint32_t length){
	
	extract_launcher(global_buffer, length, launcher);
	
	struct dir_category *root = NULL;
	
	uint16_t cat_ptr = launcher->dir_ptr;
	while(1){
		/*
		** add the category to the tree
		*/
		if(cat_ptr + MDIR_CAT_LENGTH > MAX_LAUNCHER_LEN){
			free_category(root);
			fprintf(stderr, "Error: damaged structure\n");
			exit(1);
		}
		struct dir_category *cat = add_new_category(&root);
		if(!cat){
			free_category(root);
			fprintf(stderr, "Error: out of memory\n");
			exit(1);
		}
		// get entry pointer
		uint16_t ent_ptr = ntohs(*(uint16_t*)&global_buffer[cat_ptr+MDIR_CAT_ENT_PTR]);
		// get name
		if(global_buffer[cat_ptr+MDIR_CAT_NAME] < 0x80){
			free_category(root);
			fprintf(stderr, "Error: damaged structure\n");
			exit(1);
		}
		if(global_buffer[cat_ptr+MDIR_CAT_NAME+1] == 0x1e){
			// two line category name
			int i = MDIR_CAT_NAME+2;
			int j = 0;
			uint8_t c;
			while((c = global_buffer[cat_ptr+i]) < 0x80){
				cat->name[j++] = c;
				i++;
				if(i > MDIR_CAT_LENGTH || c < 0x20 || c > 0x7e){
					free_category(root);
					fprintf(stderr, "Error: damaged structure\n");
					exit(1);
				}
			}
			cat->name[j] = 0;
			// second line
			j=0;
			i++;
			if(global_buffer[cat_ptr+i] != 0x1f){
				free_category(root);
				fprintf(stderr, "Error: damaged structure\n");
				exit(1);
			}
			i++;
			while((c = global_buffer[cat_ptr+i]) != 0x00){
				cat->name2[j++] = c;
				i++;
				if(i > MDIR_CAT_LENGTH || c < 0x20 || c > 0x7e){
					free_category(root);
					fprintf(stderr, "Error: damaged structure\n");
					exit(1);
				}
			}
			cat->name2[j] = 0;
		}else{
			// one line category name
			int i = MDIR_CAT_NAME+1;
			int j = 0;
			uint8_t c;
			while((c = global_buffer[cat_ptr+i]) != 0x00){
				cat->name[j++] = c;
				i++;
				if(i > MDIR_CAT_LENGTH || c < 0x20 || c > 0x7e){
					free_category(root);
					fprintf(stderr, "Error: damaged structure\n");
					exit(1);
				}
			}
			cat->name[j] = 0;
		}
		
		/*
		** add the entries to the tree
		*/
		while(1){
			if(ent_ptr + MDIR_ENT_LENGTH > MAX_LAUNCHER_LEN){
				free_category(root);
				fprintf(stderr, "Error: damaged structure\n");
				exit(1);
			}
			struct dir_entry *ent = add_new_entry(cat);
			if(!ent){
				free_category(root);
				fprintf(stderr, "Error: out of memory\n");
				exit(1);
			}
			// get data
			uint32_t size = ntohl(*(uint32_t*)&global_buffer[ent_ptr+MDIR_ENT_SIZE]);
			ent->numbanks = size & 0xff;
			ent->filesize = (size >> 8) & 0x3fffff;
			ent->fill_byte = (size & 0x40000000) ? 0xff : 0x00;
			
			int bank_size = ent->numbanks * BANK_SIZE;
			int alloc_size = bank_size;
			if(ent->filesize > alloc_size){
				ent->numbanks = ((ent->filesize + BANK_SIZE-1) / BANK_SIZE);
				alloc_size = BANK_SIZE * ent->numbanks;
			}
			uint32_t offset = global_buffer[ent_ptr+MDIR_ENT_BANK] * BANK_SIZE;
			if(offset <= launcher->dir_ptr || offset+bank_size > length){
				free_category(root);
				fprintf(stderr, "Error: damaged structure\n");
				exit(1);
			}
			ent->data = malloc(alloc_size);
			if(!ent->data){
				free_category(root);
				fprintf(stderr, "Error: out of memory\n");
				exit(1);
			}
			memset(ent->data, ent->fill_byte, alloc_size);
			memcpy(ent->data, &global_buffer[offset], bank_size);
			
			// get name
			int i=MDIR_ENT_NAME, j=0;
			uint8_t c;
			if(global_buffer[ent_ptr+i++] < 0x80){
				free_category(root);
				fprintf(stderr, "Error: damaged structure\n");
				exit(1);
			}
			while((c = global_buffer[ent_ptr+i]) < 0x80){
				ent->name[j++] = c;
				i++;
				if(i > MDIR_ENT_LENGTH || c < 0x20 || c > 0x7e){
					free_category(root);
					fprintf(stderr, "Error: damaged structure\n");
					exit(1);
				}
			}
			ent->name[j] = 0;
			
			// copy game id
			memcpy(ent->game_id, &global_buffer[ent_ptr+MDIR_ENT_GAME_ID], 16);
			
			// next entry?
			if((global_buffer[ent_ptr+MDIR_ENT_FLAGS] & MDIR_FLAG_LAST) != 0){
				break;
			}
			ent_ptr += MDIR_ENT_LENGTH;
		}
		/*
		** next category?
		*/
		if((global_buffer[cat_ptr+MDIR_CAT_FLAGS] & MDIR_FLAG_LAST) != 0){
			break;
		}
		cat_ptr += MDIR_CAT_LENGTH;
	}
	
	return root;
}

uint32_t binary_gen_out(struct launcher_data *launcher, struct dir_category *root, int enable_1mb){
	// renders the launcher + data into the global buffer
	
	uint32_t position;
	int num_cats = 0;
	int num_ents = 0;
	
	struct dir_category *cat = root;
	while(cat){
		num_cats++;
		
		struct dir_entry *ent = cat->first;
		if(ent == NULL){
			free_category(root);
			fprintf(stderr, "Error: a category is empty\n");
			exit(1);
		}
		while(ent){
			num_ents++;
			ent = ent->next;
		}
		
		cat = cat->next;
	}
	
	if(launcher->dir_ptr + MDIR_CAT_LENGTH*num_cats + MDIR_ENT_LENGTH*num_ents > MAX_LAUNCHER_LEN){
		free_category(root);
		fprintf(stderr, "Error: there are too many categories+entries\n");
		exit(1);
	}
	
	// erase all memory
	memset(global_buffer, 0xff, GLOBAL_BUFFER_LENGTH);
	// add launcher
	memcpy(global_buffer, launcher->bin, launcher->dir_ptr);
	position = launcher->dir_ptr;
	
	// add categories
	uint16_t category_ptr = position;
	position += MDIR_CAT_LENGTH*num_cats;
	
	// add entries
	uint16_t entry_ptr = position;
	position += MDIR_ENT_LENGTH*num_ents;
	
	// first free bank
	uint16_t bank_num = (position + BANK_SIZE - 1) / BANK_SIZE;
	position = bank_num * BANK_SIZE;
	
	// add everything
	cat = root;
	int cat_num = 0;
	while(cat){
		// add a category
		global_buffer[category_ptr + MDIR_CAT_FLAGS] =
			(cat_num == 0 ? MDIR_FLAG_FIRST : 0) |
			(cat_num == 1 ? MDIR_FLAG_SECOND : 0) |
			(cat_num == num_cats-2 ? MDIR_FLAG_SECLAST : 0) |
			(cat_num == num_cats-1 ? MDIR_FLAG_LAST : 0)
		;
		global_buffer[category_ptr + MDIR_CAT_ENT_PTR + 0] = entry_ptr >> 8;
		global_buffer[category_ptr + MDIR_CAT_ENT_PTR + 1] = entry_ptr & 0xff;
		uint8_t *name = &global_buffer[category_ptr + MDIR_CAT_NAME];
		// add first line: dx
		*name++ = string_width(launcher, cat->name, MDIR_SCALE_HEAD);
		// when two lines: move up
		if(cat->name2[0]){
			*name++ = 0x1e;
		}
		// the name
		for(int i=0; cat->name[i]; i++){
			*name++ = cat->name[i];
		}
		// add second line:
		if(cat->name2[0]){
			// dx
			*name++ = string_width(launcher, cat->name2, MDIR_SCALE_HEAD);
			// when two lines: move down
			*name++ = 0x1f;
			// the name
			for(int i=0; cat->name2[i]; i++){
				*name++ = cat->name2[i];
			}
		}
		// add eof
		*name = 0;
		
		category_ptr += MDIR_CAT_LENGTH;
		
		// count entries
		num_ents = 0;
		struct dir_entry *ent = cat->first;
		while(ent){
			num_ents++;
			ent = ent->next;
		}
		
		ent = cat->first;
		int ent_num = 0;
		while(ent){
			int mode;
			if( memcmp(ent->data+6, "SRAM", 4) == 0 && ent->numbanks*BANK_SIZE <= 32*1024 ){
				// is sure a SRAM module
				mode = MDIR_MODE_SRAM;
			}else if( memcmp(ent->data+6, "PAGE", 4) == 0 ){
				// is sure a PAGE module
				mode = MDIR_MODE_PAGE;
			}else if( memcmp(ent->data+32*1024, crt_header, 6) == 0 && ent->numbanks*BANK_SIZE > 32*1024 && ent->numbanks*BANK_SIZE <= 64*1024 ){
				// is sure a 64k module
				mode = MDIR_MODE_64K;
			}else if( ent->numbanks*BANK_SIZE <= 32*1024 ){
				// is sure a (up to) 32k module
				mode = MDIR_MODE_32K;
			}else{
				// is not really known, let's assume PAGE mode
				mode = MDIR_MODE_PAGE;
			}
			// add an entry
			global_buffer[entry_ptr + MDIR_ENT_FLAGS] =
				(ent_num == 0 ? MDIR_FLAG_FIRST : 0) |
				(ent_num == 1 ? MDIR_FLAG_SECOND : 0) |
				(ent_num == num_ents-2 ? MDIR_FLAG_SECLAST : 0) |
				(ent_num == num_ents-1 ? MDIR_FLAG_LAST : 0) |
				mode
			;
			global_buffer[entry_ptr + MDIR_ENT_BANK] = bank_num;
			
			uint8_t *name = &global_buffer[entry_ptr + MDIR_ENT_NAME];
			// add first line: dx
			*name++ = string_width(launcher, ent->name, MDIR_SCALE_BODY);
			// the name
			for(int i=0; ent->name[i]; i++){
				*name++ = ent->name[i];
			}
			*name = 0xff;
			
			*(uint32_t*)&global_buffer[entry_ptr + MDIR_ENT_SIZE] = htonl(0x80000000 | ((ent->fill_byte & 0x01) << 30) | (ent->filesize << 8) | ent->numbanks);
			
			// copy game id
			memcpy(&global_buffer[entry_ptr + MDIR_ENT_GAME_ID], ent->game_id, 16);
			
			// add the data
			if(position + ent->numbanks*BANK_SIZE > (enable_1mb ? TOTAL_MODULE_SIZE : (TOTAL_MODULE_SIZE - 64*1024))){
				free_category(root);
				if(enable_1mb){
					fprintf(stderr, "Error: too much data\n");
				}else{
					fprintf(stderr, "Error: too much data, you can disable/erase highscore data to gain 64 KiB\n");
				}
				exit(1);
			}
			memcpy(global_buffer + position, ent->data, ent->numbanks*BANK_SIZE);
			position += ent->numbanks*BANK_SIZE;
			bank_num += ent->numbanks;
			
			entry_ptr += MDIR_ENT_LENGTH;
			
			// next entry
			ent = ent->next;
			ent_num++;
		}
		
		
		// next category
		cat = cat->next;
		cat_num++;
	}
	
	return position;
}
