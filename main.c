#include <stdio.h>
#include <stdlib.h>
#include "ext/argp/argp.h"

const char *argp_program_version = "usagi 0.1";
const char *argp_program_bug_address = "<ataraxialinux@protonmail.com>";
static char doc[] = "Lighweight package manager";
static char args_doc[] = "[PACKAGE]...";
static struct argp_option options[] = {
	{ "install", 'i', 0, 0, "Install binary usagi/neko package"},
	{ 0 } 
};

struct arguments {
	char *args[8];
	int silent, verbose;
	char *output_file;
};

static int usg_install() {
	printf("Installing!\n");
	return 0;
}

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
	struct arguments *arguments = state->input;
	switch (key) {
		case 'i':
			usg_install();
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };

int main(int argc, char **argv) {
	struct arguments arguments;

	argp_parse(&argp, argc, argv, 0, 0, &arguments);
	return 0;
}
