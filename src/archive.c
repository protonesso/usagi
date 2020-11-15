#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "archive.h"

int usagi_write_cpio(FILE *archive, const char *file) {
	struct stat st;
	struct cpioArchive cpio;

	FILE *input = fopen(file, "rb");;
	int ret = fstat(fileno(input), &st);
	if (ret < 0) {
		printf("Cannot open file: %s\n", file);
		fclose(input);
		return 1;
	}

	size_t nsz = strlen(file) + 1;

	memset(&cpio, 0, sizeof(struct cpioArchive));
	sprintf(cpio.c_magic, "%s", "070701");
	sprintf(cpio.c_ino, "%08lX", st.st_ino);
	sprintf(cpio.c_mode, "%08X", st.st_mode);
	sprintf(cpio.c_uid, "%08X", st.st_uid);
	sprintf(cpio.c_gid, "%08X", st.st_gid);
	sprintf(cpio.c_nlink, "%08lX", st.st_nlink);
	sprintf(cpio.c_mtime, "%08lX", st.st_mtime);
	sprintf(cpio.c_filesize, "%08lX", st.st_size);
	sprintf(cpio.c_devmajor, "%08X", major(st.st_dev));
	sprintf(cpio.c_devminor, "%08X", minor(st.st_dev));
	sprintf(cpio.c_rdevmajor, "%08X", major(st.st_rdev));
	sprintf(cpio.c_rdevminor, "%08X", minor(st.st_rdev));
	sprintf(cpio.c_namesize, "%08zX", nsz);
	fwrite(&cpio, sizeof(struct cpioArchive), 1, archive);

	while (!feof(input)) {
		char *buf = malloc(sizeof(char) * 1024);
		size_t read = fread(buf, 1, sizeof(buf), input);
		fwrite(buf, 1, read, archive);
	}

	memset(&cpio, 0, sizeof(struct cpioArchive));
	sprintf(cpio.c_magic, "%s", "070701");
	sprintf(cpio.c_ino, "%08X", 0);
	sprintf(cpio.c_mode, "%08X", 0);
	sprintf(cpio.c_uid, "%08X", 0);
	sprintf(cpio.c_gid, "%08X", 0);
	sprintf(cpio.c_nlink, "%08X", 0);
	sprintf(cpio.c_mtime, "%08X", 0);
	sprintf(cpio.c_filesize, "%08X", 0);
	sprintf(cpio.c_devmajor, "%08X", 0);
	sprintf(cpio.c_devminor, "%08X", 0);
	sprintf(cpio.c_rdevmajor, "%08X", 0);
	sprintf(cpio.c_rdevminor, "%08X", 0);
	sprintf(cpio.c_namesize, "%08X", 0);
	fwrite(&cpio, sizeof(struct cpioArchive), 1, archive);

	fclose(input);

	return 0;
}
