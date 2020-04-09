#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

struct usg_main {
	bool force, needed, nodepends, noconflicts, noscripts, notriggers;
	char *config, *maskfile, *rootfs;
};
