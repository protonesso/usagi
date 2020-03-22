#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	char *subarg = argv[1];
	char *operation = NULL;

	if (argc < 2) {
		fprintf(stderr, "fuk yo\n");
		return 1;
	}

	if (strstr(subarg, "info") != NULL) {
		operation = "us_info";
	} else if (strstr(subarg, "install") != NULL) {
		operation = "us_install";
	} else if (strstr(subarg, "list") != NULL) {
		operation = "us_list";
	} else if (strstr(subarg, "remove") != NULL) {
		operation = "us_remove";
	} else if (strstr(subarg, "version") != NULL) {
		operation = "us_verion";
	} else {
		fprintf(stderr, "Unknown command\n");
		return 1;
	}

	printf("%s\n", operation);

	return 0;
}
