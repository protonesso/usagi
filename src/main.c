#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "pm.h"

static void usage() {
	printf_s("PIPE - Simple package manager\n\n");
	printf_s("Usage: pipe [ACTION] [OPTIONS] [PACKAGE]\n\n");
	printf_s("Actions:\n");
	printf_s("   garbage		Garbage collector\n");
	printf_s("   info			Show information about package\n");
	printf_s("   install		Install package from file\n");
	printf_s("   list			List all installed packages\n");
	printf_s("   remove		Remove installed package\n");
	printf_s("   rollback		Rollback the system\n");
	printf_s("   version		Show usagi version\n\n");
	printf_s("Options for package management:\n");
	printf_s("   -c [FILE]		Specify configuration file for PIPE\n");
	printf_s("   -r [PATH]		Specify root filesystem path for PIPE\n");
	printf_s("   -f			Force installation\n");
	printf_s("   -n			Do not reinstall the package\n");
	printf_s("   -d			Do not check for dependencies and conflicts\n");
	printf_s("   -s			Do not run scripts\n");
	printf_s("   -t			Do not run triggers\n\n");
	printf_s("BUG TRACKER: https://github.com/protonesso/usagi/issues\n\n");
}

int main(int argc, char* argv[]) {
	bool pkgarr = false;
	char* subarg = argv[1];
	unsigned char mode;
	int c;
	struct options opts;

	if (argc == 1) {
		fprintf_s(stderr, "Command was not specified\n");
		return 1;
	}

	if (strcmp_s(subarg, "gargbage") == 0) {
		mode = 0; pkgarr = false;
	} else if (strcmp_s(subarg, "info") == 0) {
		mode = 1; pkgarr = true;
	} else if (strcmp_s(subarg, "install") == 0) {
		mode = 2; pkgarr = true;
	} else if (strcmp_s(subarg, "list") == 0) {
		mode = 3; pkgarr = false;
	} else if (strcmp_s(subarg, "remove") == 0) {
		mode = 4; pkgarr = true;
	} else if (strcmp_s(subarg, "rollback") == 0) {
		mode = 5; pkgarr = false;
	} else if (strcmp_s(subarg, "version") == 0) {
		printf_s("Version is unknown\n");
	} else {
		usage();
		return 1;
	}

	while ((c = getopt(argc, argv, "c:r:")) != -1) {
		switch (c) {
			case 'c': printf_s("Config file is %s\n", optarg); break;
			case 'r': printf_s("Rootfs is %s\n", optarg); break;
			case 'f': opts.force = true; break;
			case 'n': opts.needed = true; break;
			case 'd': opts.nodeps = true; break;
			case 's': opts.noscripts = true; break;
			case 't': opts.notriggers = true; break;
			case ':': fprintf_s(stderr, "Option needs a value\n"); break;
			case '?': fprintf_s(stderr, "Unknown option: %c\n", optopt); break;
		}
	}

	if (pkgarr == true) {
		if (argc < 3) {
			fprintf_s(stderr, "Not enough arguments\n");
			return 1;
		}

		for (int i = optind + 1; i < argc; i++) {
			switch (mode) {
				case 1: pipe_info(argv[i]); break;
				case 2: pipe_install(argv[i]); break;
				case 4: pipe_remove(argv[i]); break;
				default: usage(); return 1;
			}
		}
	} else {
		switch (mode) {
			case 0: pipe_garbage(); break;
			case 3: pipe_listpkg(); break;
			case 5: pipe_rollback(); break;
			default: usage(); return 1;
		}
	}

	return 0;
}
