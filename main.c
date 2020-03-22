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
	char *config, *rootfs = NULL;

	if (argc < 2) {
		fprintf(stderr, "Specify command\n");
		return 1;
	}

	if (strstr(subarg, "info") != NULL) {
		printf("info\n");
	} else if (strstr(subarg, "install") != NULL) {
		printf("install\n");
	} else if (strstr(subarg, "list") != NULL) {
		printf("list\n");
	} else if (strstr(subarg, "remove") != NULL) {
		printf("remove\n");
	} else if (strstr(subarg, "version") != NULL) {
		printf("usagi version %s\n", VERSION);
	} else {
		fprintf(stderr, "Unknown command\n");
		return 1;
	}

	while ((c = getopt(argc, argv, ":fndestc:r:")) != -1) {
		switch (c) {
			case 'c':
				config = strdup(optarg);
				break;
			case 'r':
				rootfs = strdup(optarg);
				break;
			case 'f':
				force = 1;
				break;
			case 'n':
				needed = 1;
				break;
			case 'd':
				depends = 0;
				break;
			case 'e':
				conflicts = 0;
				break;
			case 's':
				scripts = 0;
				break;
			case 't':
				triggers = 0;
				break;
			case ':':
				printf("Option needs value\n");
				break;
			case '?':
				printf("Unknown option: %c\n");
				break;
		}

		argc -= optind;
		argv += optind;
	}

	return 0;
}
