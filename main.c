/*
 * Copyright (c) 2001-2003 USAGI Technologies Japan
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

#include "main.h"

#define VERSION "current"

static void usg_install(const char *pkg) {
	printf("installing: %s\n", pkg);
}

int main(int argc, char *argv[]) {
	struct usg_main u;

	int d;
	unsigned char c;
	char *subarg = argv[1];

	u.force, u.needed, u.nodepends, u.noconflicts, u.noscripts, u.notriggers = false;
	u.config = "/etc/neko/make.conf";
	u.maskfile = "/etc/neko/mask";
	u.rootfs = "/";

	if (argc < 2) {
		fprintf(stderr, "Specify command\n");
		return 1;
	}

	if (strstr(subarg, "emerge") != NULL) {
		c = 0;
	} else if (strstr(subarg, "help") != NULL) {
		//usg_help();
	} else if (strstr(subarg, "info") != NULL) {
		c = 1;
	} else if (strstr(subarg, "install") != NULL) {
		c = 2;
	} else if (strstr(subarg, "list") != NULL) {
		//usg_list();
	} else if (strstr(subarg, "remove") != NULL) {
		c = 3;
	} else if (strstr(subarg, "upgrade") != NULL) {
		//usg_upgrade();
	} else if (strstr(subarg, "version") != NULL) {
		//usg_version();
	} else {
		fprintf(stderr, "Unknown command\n");
		return 1;
	}

	while ((d = getopt(argc, argv, ":fwndestCDEBPSc:m:r:")) != -1) {
		switch (d) {
			case 'c':
				u.config = strdup(optarg);
				break;
			case 'm':
				u.maskfile = strdup(optarg);
				break;
			case 'r':
				u.rootfs = strdup(optarg);
				break;
			case 'f':
				u.force = true;
				break;
			case 'n':
				u.needed = true;
				break;
			case 'd':
				u.nodepends = true;
				break;
			case 'e':
				u.noconflicts = true;
				break;
			case 's':
				u.noscripts = true;
				break;
			case 't':
				u.notriggers = true;
				break;
			case ':':
				printf("option needs a value\n");
				break;  
			case '?':
				printf("unknown option: %c\n", optopt);
				break;
		}
	}

	argc--;
	argv++;

	for (int i = 2; i < argc; i++) {
		switch (c) {
			case 0:
				//usg_emerge(argv[i]);
				break;
			case 1:
				//usg_info(argv[i]);
				break;
			case 2:
				usg_install(argv[i]);
				break;
			case 3:
				//usg_remove(argv[i]);
				break;
		}
	}

	return 0;
}
