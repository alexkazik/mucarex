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

#ifndef BINARY_H
#define BINARY_H

#include "launcher.h"
#include "mdir.h"

int read_data(char *filename, FILE *in, uint8_t *buffer, int maxlength);
struct dir_category *binary_parse_in(struct launcher_data *launcher, uint32_t length);
struct dir_category *binary_in(char *filename, struct launcher_data *launcher);
struct dir_category *split_in(char *filename_lo, char *filename_hi, struct launcher_data *launcher);

void write_data(char *filename, FILE *out, uint8_t *buffer, int length);
uint32_t binary_gen_out(struct launcher_data *launcher, struct dir_category *cats, int enable_1mb);
void binary_out(char *filename, struct launcher_data *launcher, struct dir_category *root, int enable_1mb);
void split_out(char *filename_lo, char *filename_hi, struct launcher_data *launcher, struct dir_category *root, int enable_1mb);
void easyflash_out(char *filename, struct launcher_data *launcher, struct dir_category *root, int enable_1mb);

#endif
