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
#include <stdint.h>
#include <getopt.h>
#include <stdlib.h>

#include "launcher_bin.h"
#include "launcher.h"
#include "directory.h"
#include "binary.h"

void usage(const char *progname){
	fprintf(stderr, "Usage: %s [options]\n", progname);
	fprintf(stderr, "--help                                show this help\n");
	fprintf(stderr, "Input Options:\n");
	fprintf(stderr, "-b, --in-binary <file.bin>            read from a single .bin file, use \"-\" for stdin\n");
	fprintf(stderr, "-l, --in-lorom <lorom.bin>\n");
	fprintf(stderr, "-h, --in-hirom <hirom.bin>            read from two files, one for each flash chip\n");
	fprintf(stderr, "-d, --in-directory <dir/index.txt>    read from a indexfile which links all the binaries\n");
	fprintf(stderr, "Misc Options:\n");
	fprintf(stderr, "-s, --store-laucher <launcher.bin>    stores the launcher to a file (stores the builtin launcher on --in-diretory)\n");
	fprintf(stderr, "-t, --trim                            trim all modules by removing (hopefully) unnecessary empty banks at the end  (no effect on --out-diretory)\n");
	fprintf(stderr, "-S, --load-laucher <launcher.bin>     loads the launcher from a file to not use the launcher inside the read binary (no effect on --out-diretory)\n");
	fprintf(stderr, "-A, --default-launcher                uses the builtin launcher instead of the launcher inside the read binary (no effect on --out-diretory)\n");
	fprintf(stderr, "-1, --enable-1mb                      use the full 1 MiB of flash, otherwise 64 KiB are reserved for highscore\n");
	fprintf(stderr, "Output Options:\n");
	fprintf(stderr, "-B, --out-binary <file.bin>           write to a single .bin file, use \"-\" for stdout\n");
	fprintf(stderr, "-L, --out-lorom <lorom.bin>\n");
	fprintf(stderr, "-H, --out-hirom <hirom.bin>           write to two files, one for each flash chip\n");
	fprintf(stderr, "-D, --out-directory <dir/index.txt>   write to a indexfile which links all the binaries\n");
	fprintf(stderr, "-E, --out-easyflash <ef.crt>          write to a single EasyFlash crt file for programming the flash chips on a C64\n");
}

int main(int argc, char **argv){
	
	/* options descriptor */
	static const struct option longopts[] = {
		{"in-binary",	required_argument,	NULL,	'b'},
		{"in-lorom",	required_argument,	NULL,	'l'},
		{"in-hirom",	required_argument,	NULL,	'h'},
		{"in-directory",	required_argument,	NULL,	'd'},
		
		{"store-launcher",	required_argument,	NULL,	's'},
		{"trim",	no_argument,	NULL,	't'},
		{"load-launcher",	required_argument,	NULL,	'S'},
		{"default-launcher",	no_argument,	NULL,	'A'},
		{"enable-1mb",	no_argument,	NULL,	'1'},
		
		{"out-binary",	required_argument,	NULL,	'B'},
		{"out-lorom",	required_argument,	NULL,	'L'},
		{"out-hirom",	required_argument,	NULL,	'H'},
		{"out-directory",	required_argument,	NULL,	'D'},
		{"out-easyflash",	required_argument,	NULL,	'E'},
		
		{"help",	no_argument,	NULL,	'#'},
		
		{NULL,	0,	NULL,	0}
	};
	
	char *in_binary = NULL;
	char *in_lorom = NULL;
	char *in_hirom = NULL;
	char *in_directory = NULL;
	char *in_easyflash = NULL;
	
	char *out_binary = NULL;
	char *out_lorom = NULL;
	char *out_hirom = NULL;
	char *out_directory = NULL;
	char *out_easyflash = NULL;
	
	char *store_launcher = NULL;
	char *load_launcher = NULL;
	int trim = 0;
	int default_launcher = 0;
	int enable_1mb = 0;
	
	int ch;
	while((ch = getopt_long(argc, argv, "b:l:h:d:B:L:H:D:E:s:S:tTA1#", longopts, NULL)) != -1){
		switch(ch){
		case 'b':
			in_binary = optarg;
			break;
		case 'l':
			in_lorom = optarg;
			break;
		case 'h':
			in_hirom = optarg;
			break;
		case 'd':
			in_directory = optarg;
			break;
		case 's':
			store_launcher = optarg;
			break;
		case 't':
			trim = 1;
			break;
		case 'B':
			out_binary = optarg;
			break;
		case 'L':
			out_lorom = optarg;
			break;
		case 'H':
			out_hirom = optarg;
			break;
		case 'D':
			out_directory = optarg;
			break;
		case 'E':
			out_easyflash = optarg;
			break;
		case 'S':
			load_launcher = optarg;
			break;
		case 'A':
			default_launcher = 1;
			break;
		case '1':
			enable_1mb = 1;
			break;
		case '#':
			usage(argv[0]);
			exit(0);
			break;
		default:
			usage(argv[0]);
			exit(1);
			break;
		}
	}
	
	if(argc != optind){
		usage(argv[0]);
		exit(1);
	}
	
	if(!in_lorom != !in_hirom){
		fprintf(stderr, "Error: --in-lorom or --in-hirom is missing\n");
		exit(1);
	}
	
	if(!out_lorom != !out_hirom){
		fprintf(stderr, "Error: --out-lorom or --out-hirom is missing\n");
		exit(1);
	}
	
	ch = 0;
	if(in_binary){
		ch++;
	}
	if(in_lorom){
		ch++;
	}
	if(in_directory){
		ch++;
	}
	if(ch == 0){
		fprintf(stderr, "Error: no input source specified\n");
		exit(1);
	}else if(ch > 1){
		fprintf(stderr, "Error: to many input sources specified\n");
		exit(1);
	}
	
	ch = 0;
	if(out_binary){
		ch++;
	}
	if(out_lorom){
		ch++;
	}
	if(out_directory){
		ch++;
	}
	if(out_easyflash){
		ch++;
	}
	if(ch == 0){
		fprintf(stderr, "Error: no output source specified\n");
		exit(1);
	}else if(ch > 1){
		fprintf(stderr, "Error: to many output sources specified\n");
		exit(1);
	}
	
	// variables
	
	struct launcher_data data;
	struct dir_category *root;
	const char *err;
	
	// load the default launcher (will be overwritten in some cases)
	extract_launcher(launcher_bin, launcher_bin_len, &data);
	
	uint16_t builtin_launcher_version = data.version;
	
	if(err != NULL){
		fprintf(stderr, "Error: %s\n", err);
		exit(1);
	}
	
	// load the input
	if(in_binary){
		root = binary_in(in_binary, &data);
	}else if(in_lorom){
		root = split_in(in_lorom, in_hirom, &data);
	}else if(in_directory){
		root = directory_in(in_directory);
	}else{
		fprintf(stderr, "Error: method not implemented yet\n");
		exit(1);
	}
	
	// in between options
	if(trim){
		trim_modules(root);
	}
	if(store_launcher){
		write_data(store_launcher, NULL, data.bin, data.dir_ptr);
	}
	if(load_launcher){
		uint8_t lbin[MAX_LAUNCHER_LEN];
		int lsize = read_data(load_launcher, NULL, lbin, MAX_LAUNCHER_LEN);
		extract_launcher(lbin, lsize, &data);
	}
	if(default_launcher){
		extract_launcher(launcher_bin, launcher_bin_len, &data);
	}
	
	// check for an old launcher
	if(!out_directory && builtin_launcher_version > data.version){
		fprintf(stderr, "Notice: the used launcher is older than the default, consider using -A to update it\n");
	}
	
	// store the output
	if(out_binary){
		binary_out(out_binary, &data, root, enable_1mb);
	}else if(out_lorom){
		split_out(out_lorom, out_hirom, &data, root, enable_1mb);
	}else if(out_directory){
		directory_out(out_directory, root);
	}else if(out_easyflash){
		easyflash_out(out_easyflash, &data, root, enable_1mb);
	}else{
		fprintf(stderr, "Error: method not implemented yet\n");
		exit(1);
	}
	
	return 0;
	
}