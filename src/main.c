#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "pm.h"

void usg_garbage() {}
void usg_info(const char *pkg) {}
void usg_install(const char *pkg) {}
void usg_listpkg() {}
void usg_remove(const char *pkg) {}
void usg_rollback() {}

static void usage() {
	printf("PIPE - Simple package manager\n\n");
	printf("Usage: pipe [ACTION] [OPTIONS] [PACKAGE]\n\n");
	printf("Actions:\n");
	printf("   garbage		Garbage collector\n");
	printf("   info			Show information about package\n");
	printf("   install		Install package from file\n");
	printf("   list			List all installed packages\n");
	printf("   remove		Remove installed package\n");
	printf("   rollback		Rollback the system\n");
	printf("   version		Show usagi version\n\n");
	printf("Options for package management:\n");
	printf("   -c [FILE]		Specify configuration file for PIPE\n");
	printf("   -r [PATH]		Specify root filesystem path for PIPE\n");
	printf("   -f			Force installation\n");
	printf("   -n			Do not reinstall the package\n");
	printf("   -d			Do not check for dependencies and conflicts\n");
	printf("   -s			Do not run scripts\n");
	printf("   -t			Do not run triggers\n\n");
	printf("BUG TRACKER: https://github.com/protonesso/usagi/issues\n\n");
}

int main(int argc, char* argv[]) {
	bool pkgarr = false;
	char* subarg = argv[1];
	unsigned char mode;
	int c;
	struct options opts;

	if (argc == 1) {
		fprintf(stderr, "Command was not specified\n");
		return 1;
	}

	if (strcmp(subarg, "gargbage") == 0) {
		mode = 0; pkgarr = false;
	} else if (strcmp(subarg, "info") == 0) {
		mode = 1; pkgarr = true;
	} else if (strcmp(subarg, "install") == 0) {
		mode = 2; pkgarr = true;
	} else if (strcmp(subarg, "list") == 0) {
		mode = 3; pkgarr = false;
	} else if (strcmp(subarg, "remove") == 0) {
		mode = 4; pkgarr = true;
	} else if (strcmp(subarg, "rollback") == 0) {
		mode = 5; pkgarr = false;
	} else if (strcmp(subarg, "version") == 0) {
		printf("usagi version is %s\n", VERSION);
	} else {
		usage();
		return 1;
	}

	while ((c = getopt(argc, argv, "c:r:")) != -1) {
		switch (c) {
			case 'c': printf("Config file is %s\n", optarg); break;
			case 'r': printf("Rootfs is %s\n", optarg); break;
			case 'f': opts.force = true; break;
			case 'n': opts.needed = true; break;
			case 'd': opts.nodeps = true; break;
			case 's': opts.noscripts = true; break;
			case 't': opts.notriggers = true; break;
			case ':': fprintf(stderr, "Option needs a value\n"); break;
			case '?': fprintf(stderr, "Unknown option: %s\n", optarg); break;
		}
	}

	if (pkgarr == true) {
		if (argc < 3) {
			fprintf(stderr, "Not enough arguments\n");
			return 1;
		}

		for (int i = optind + 1; i < argc; i++) {
			switch (mode) {
				case 1: usg_info(argv[i]); break;
				case 2: usg_install(argv[i]); break;
				case 4: usg_remove(argv[i]); break;
				default: usage(); return 1;
			}
		}
	} else {
		switch (mode) {
			case 0: usg_garbage(); break;
			case 3: usg_listpkg(); break;
			case 5: usg_rollback(); break;
			default: usage(); return 1;
		}
	}

	return 0;
}
