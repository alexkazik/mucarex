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
#include <errno.h>
#include <libgen.h>
#include <stdlib.h>
#include <ctype.h>

#include "directory.h"
#include "md5.h"

char *trim(char *str);
int copy_string_to_bin(uint8_t *out, char *in);

struct dir_category *directory_in(const char *indexfilename){
	FILE *indexfile = fopen(indexfilename, "r");
	
	if(!indexfile){
		fprintf(stderr, "error opening the indexfile \"%s\": %s\n", indexfilename, strerror(errno));
		exit(1);
	}
	
	char *directorynamebuffer = strdup(indexfilename);
	char *directoryname = dirname(directorynamebuffer);
	if(!directoryname){
		fprintf(stderr, "error accessing the directory \"%s\": %s\n", indexfilename, strerror(errno));
		exit(1);
	}
	
	struct dir_category *root = NULL;
	struct dir_category *cat = NULL;
	int line = 1;
	
	while(fgets(char_global_buffer, GLOBAL_BUFFER_LENGTH, indexfile)){
		char *buffer = char_global_buffer;
		char *ename = trim(strsep(&buffer, ";"));
		char *efile = trim(strsep(&buffer, ";"));
		char *edummy = trim(strsep(&buffer, ";"));
		
		if(*ename == 0){
			// empty row -> ignore
		}else if(strcmp(ename, "-") == 0){
			// a new category
			cat = add_new_category(&root);
			if(cat == NULL){
				free(directorynamebuffer);
				free_category(root);
				fclose(indexfile);
				fprintf(stderr, "Error: out of memory\n");
				exit(1);
			}
			if(*efile == 0){
				free(directorynamebuffer);
				free_category(root);
				fclose(indexfile);
				fprintf(stderr, "error in file \"%s\", line %d: category name is missing\n", indexfilename, line);
				exit(1);
			}
			if(*edummy != 0){
				// two line name
				if(2 + strlen(efile) + 2 + strlen(edummy) > MAX_CAT_NAME_LENGTH){
					free(directorynamebuffer);
					free_category(root);
					fclose(indexfile);
					fprintf(stderr, "error in file \"%s\", line %d: category names (\"%s\", \"%s\") are too long (max. %d together)\n", indexfilename, line, efile, edummy, MAX_CAT_NAME_LENGTH-4);
					exit(1);
				}
				if(!copy_string_to_bin(cat->name, efile)){
					free(directorynamebuffer);
					free_category(root);
					fclose(indexfile);
					fprintf(stderr, "error in file \"%s\", line %d: invalid char\n", indexfilename, line);
					exit(1);
				}
				if(!copy_string_to_bin(cat->name2, edummy)){
					free(directorynamebuffer);
					free_category(root);
					fclose(indexfile);
					fprintf(stderr, "error in file \"%s\", line %d: invalid char\n", indexfilename, line);
					exit(1);
				}
			}else{
				// one line name
				if(1 + strlen(efile) > MAX_CAT_NAME_LENGTH){
					free(directorynamebuffer);
					free_category(root);
					fclose(indexfile);
					fprintf(stderr, "error in file \"%s\", line %d: category name is too long (max. %d chars)\n", indexfilename, line, MAX_CAT_NAME_LENGTH-1);
					exit(1);
				}
				if(!copy_string_to_bin(cat->name, efile)){
					free(directorynamebuffer);
					free_category(root);
					fclose(indexfile);
					fprintf(stderr, "error in file \"%s\", line %d: invalid char\n", indexfilename, line);
					exit(1);
				}
				cat->name2[0] = 0; // empty string
			}
		}else{
			if(cat == NULL){
				free(directorynamebuffer);
				free_category(root);
				fclose(indexfile);
				fprintf(stderr, "error in file \"%s\", line %d: category is missing\n", indexfilename, line);
				exit(1);
			}
			if(1 + strlen(ename) + 1 > MAX_ENT_NAME_LENGTH){
				free(directorynamebuffer);
				free_category(root);
				fclose(indexfile);
				fprintf(stderr, "error in file \"%s\", line %d: entry name is too long (max. %d chars)\n", indexfilename, line, MAX_ENT_NAME_LENGTH-2);
				exit(1);
			}
			struct dir_entry* ent = add_new_entry(cat);
			if(ent == NULL){
				free(directorynamebuffer);
				free_category(root);
				fclose(indexfile);
				fprintf(stderr, "Error: out of memory\n");
				exit(1);
			}
			if(!copy_string_to_bin(ent->name, ename)){
				free(directorynamebuffer);
				free_category(root);
				fclose(indexfile);
				fprintf(stderr, "error: bad name \"%s\"\n\n", ename);
				exit(1);
			}
			
			sprintf(char_global_buffer+GLOBAL_BUFFER_LENGTH/2, "%s/%s", directoryname, efile);
			FILE *datafile = fopen(char_global_buffer+GLOBAL_BUFFER_LENGTH/2, "rb");
			if(!datafile){
				free(directorynamebuffer);
				free_category(root);
				fclose(indexfile);
				fprintf(stderr, "error opening the file \"%s\": %s\n", char_global_buffer+GLOBAL_BUFFER_LENGTH/2, strerror(errno));
				exit(1);
			}
			
			memset(global_buffer, 0xff, TOTAL_MODULE_SIZE);
			ent->filesize = fread(global_buffer, 1, TOTAL_MODULE_SIZE, datafile);
			if(ent->filesize < 20 || ent->filesize >= TOTAL_MODULE_SIZE){
				free(directorynamebuffer);
				free_category(root);
				fclose(indexfile);
				fclose(datafile);
				fprintf(stderr, "error reading the file \"%s\"\n", indexfilename);
				exit(1);
			}
			
			fclose(datafile);
			ent->numbanks = (ent->filesize + BANK_SIZE - 1) / BANK_SIZE;
			ent->data = malloc(ent->numbanks * BANK_SIZE);
			memcpy(ent->data, global_buffer, ent->numbanks * BANK_SIZE);
			
			// search game id
			if(ent->filesize > 24 && 0 == memcmp(&ent->data[ent->filesize - 24], "GAME-ID:", 8)){
				// copy game id
				memcpy(ent->game_id, &ent->data[ent->filesize - 16], 16);
			}else{
				// create md5
				MD5_CTX context;
				MD5_Init(&context);
				MD5_Update(&context, ent->data, ent->filesize);
				MD5_Final(ent->game_id, &context);
			}
		}
		
		line++;
	}
	
	fclose(indexfile);
	free(directorynamebuffer);
	
	return root;
}


int copy_string_to_bin(uint8_t *out, char *in){
	char c;
	while((c = *in++)){
		if(c >= 'a' && c <= 'z'){
			*out++ = c - 0x20;
		}else if(c < 0x20 || c > 0x5f){
			return 0;
		}else{
			*out++ = c;
		}
	}
	*out++ = 0;
	return 1;
}

char *trim(char *str){
	char *end;
	
	if(str == NULL){
		return "";
	}
	
	// trim leading space
	while(isspace(*str)) str++;
	
	if(*str == 0)  // All spaces?
	return str;
	
	// trim trailing space
	end = str + strlen(str) - 1;
	while(end > str && isspace(*end)) end--;
	
	// write new null terminator
	*(end+1) = 0;
	
	return str;
}

void directory_out(char *indexfilename, struct dir_category *root){
	FILE *indexfile = fopen(indexfilename, "w");
	
	if(!indexfile){
		fprintf(stderr, "error opening the indexfile \"%s\": %s\n", indexfilename, strerror(errno));
		exit(1);
	}
	
	char *directorynamebuffer = strdup(indexfilename);
	char *directoryname = dirname(directorynamebuffer);
	if(!directoryname){
		fclose(indexfile);
		fprintf(stderr, "error accessing the directory \"%s\": %s\n", indexfilename, strerror(errno));
		exit(1);
	}
	
	struct dir_category *cat = root;
	int cat_num = 1;
	while(cat){
		if(cat != root){
			fprintf(indexfile, "\n");
		}
		if(cat->name2[0] == 0){
			fprintf(indexfile, "-; %s ;; --------\n", cat->name);
		}else{
			fprintf(indexfile, "-; %s ; %s ; --------\n", cat->name, cat->name2);
		}
		
		struct dir_entry *ent = cat->first;
		int ent_num = 1;
		while(ent){
			// build filename
			sprintf(char_global_buffer, "%s/%02d_%02d__", directoryname, cat_num, ent_num);
			// copy name, but only A-Z (as a-z), 0-9 and replace everything else with a "_" (but never two underscores in a row)
			char *buf = char_global_buffer + strlen(char_global_buffer);
			uint8_t *nam = ent->name;
			uint8_t ch;
			while((ch = *nam++)){
				if(ch >= '0' && ch <= '9'){
					*buf++ = ch;
				}else if(ch >= 'A' && ch <= 'Z'){
					*buf++ = ch-'A'+'a';
				}else if(*(buf-1) != '_'){
					*buf++ = '_';
				}
			}
			// remove a trailing underscore
			if(*(buf-1) == '_'){
				buf--;
			}
			// add ".bin"
			*buf++ = '.';
			*buf++ = 'b';
			*buf++ = 'i';
			*buf++ = 'n';
			*buf = 0;
			
			// print line (strip the directory name)
			fprintf(indexfile, "%s ; %s\n", ent->name, char_global_buffer + strlen(directoryname) + 1);
			
			// dump file
			FILE *out = fopen(char_global_buffer, "wb");
			if(!out){
				fprintf(stderr, "error opening the file \"%s\": %s\n", char_global_buffer, strerror(errno));
				exit(1);
			}
			fwrite(ent->data, 1, ent->filesize, out);
			fclose(out);
			
			// next entry
			ent = ent->next;
			ent_num++;
		}
		
		cat = cat->next;
		cat_num++;
	}
	
	fclose(indexfile);
	free(directorynamebuffer);
}
