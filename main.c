#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static void usage() {
	printf("usagi - Simple package manager\n\n");
	printf("Usage: usagi [ACTION] [OPTIONS] [PACKAGE]\n\n");
	printf("Actions:\n");
	printf("   build		Build package from source\n");
	printf("   emerge		Build package and install it\n");
	printf("   info			Show information about package\n");
	printf("   install		Install package from file\n");
	printf("   list			List all installed packages\n");
	printf("   remove		Remove installed package\n");
	printf("   search		Search for packages\n");
	printf("   sync			Synchronize repositories\n");
	printf("   upgrade		Upgrade all of installed packages\n");
	printf("   version		Show usagi version\n\n");
	printf("Options:\n");
	printf("In dev!\n\n");
	printf("BUG TRACKER: https://github.com/protonesso/usagi/issues\n\n");
}

int main(int argc, char* argv[]) {
	bool pkgarr = false;
	char* subarg = argv[1];
	unsigned char mode;

	if (argc == 1) {
		fprintf(stderr, "Command was not specified\n");
		return 1;
	}

	if (strstr(subarg, "build") != NULL) {
		mode = 0;
	} else if (strstr(subarg, "emerge") != NULL) {
		mode = 1;
		pkgarr = true;
	} else if (strstr(subarg, "info") != NULL) {
		mode = 2;
		pkgarr = true;
	} else if (strstr(subarg, "install") != NULL) {
		mode = 3;
		pkgarr = true;
	} else if (strstr(subarg, "list") != NULL) {
		mode = 4;
	} else if (strstr(subarg, "remove") != NULL) {
		mode = 5;
		pkgarr = true;
	} else if (strstr(subarg, "search") != NULL) {
		mode = 6;
		pkgarr = true;
	} else if (strstr(subarg, "sync") != NULL) {
		mode = 7;
	} else if (strstr(subarg, "upgrade") != NULL) {
		mode = 8;
	} else if (strstr(subarg, "version") != NULL) {
		printf("Version is unknown\n");
	} else {
		usage();
		return 1;
	}

	if (pkgarr == true) {
		if (argc < 3) {
			fprintf(stderr, "Not enough arguments\n");
			return 1;
		}

		for (int i = 2; i < argc; i++) {
			switch (mode) {
				case 1: printf("Emerging package: %s\n", argv[i]); break;
				case 2: printf("Information for %s\n", argv[i]); break;
				case 3: printf("Installing package: %s\n", argv[i]); break;
				case 5: printf("Removing package: %s\n", argv[i]); break;
				case 6: printf("Searching for package %s\n", argv[i]); break;
				default: usage(); return 1;
			}
		}
	} else {
		switch (mode) {
			case 0: printf("Building package\n"); break;
			case 4: printf("Listing packages\n"); break;
			case 7: printf("Syncing repos\n"); break;
			case 8: printf("Upgrading system\n"); break;
			default: usage(); return 1;
		}
	}

	return 0;
}
