/*
 * Copyright (c) 2016-2020 Ataraxia Linux <ataraxialinux@protonmail.com>
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define VERSION "current"

int main(int argc, char *argv[]) {
	int c;
	int force, needed = 0;
	int depends, conflicts, scripts, triggers = 1;
	char *subarg = argv[1];
	char *config = "/etc/neko/make.conf";
	char *maskfile = "/etc/neko/mask";
	char *rootfs = "/";

	if (argc < 2) {
		fprintf(stderr, "Specify command\n");
		return 1;
	}

	if (strstr(subarg, "emerge") != NULL) {
		c = 0;
	} else if (strstr(subarg, "help") != NULL) {
		usg_help();
	} else if (strstr(subarg, "info") != NULL) {
		c = 1;
	} else if (strstr(subarg, "install") != NULL) {
		c = 2;
	} else if (strstr(subarg, "list") != NULL) {
		usg_list();
	} else if (strstr(subarg, "remove") != NULL) {
		c = 3;
	} else if (strstr(subarg, "upgrade") != NULL) {
		usg_upgrade();
	} else if (strstr(subarg, "version") != NULL) {
		usg_version();
	} else {
		fprintf(stderr, "Unknown command\n");
		return 1;
	}

	// getopt or smh like that goes here

	for (int i = 2; i < argc; i++) {
		switch (c) {
			case 0:
				usg_emerge(argv[i]);
				break;
			case 1:
				usg_info(argv[i]);
				break;
			case 2:
				usg_install(argv[i]);
				break;
			case 3:
				usg_remove(argv[i]);
				break;
		}
	}

	return 0;
}
