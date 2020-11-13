#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "archive.h"

int usagi_write_cpio(FILE *cpio_file, const char *file) {
	struct stat st;
	struct cpioArchive cpio;

	FILE *input = fopen_s(file, "rb");;
	int ret = fstat(fileno(input), &st);
	if (ret < 0) {
		printf_s("Cannot open file: %s\n", file);
		fclose(input);
		return 1;
	}

	size_t index = ftell(cpio_file);
	fseek(input, 0, SEEK_SET);
	int nsz = ftell(input);

	sprintf_s(cpio.c_magic, "%s", "070701");
	sprintf_s(cpio.c_ino, "%08lX", st.st_ino);
	sprintf_s(cpio.c_mode, "%08X", st.st_mode);
	sprintf_s(cpio.c_uid, "%08X", st.st_uid);
	sprintf_s(cpio.c_gid, "%08X", st.st_gid);
	sprintf_s(cpio.c_nlink, "%08lX", st.st_nlink);
	sprintf_s(cpio.c_mtime, "%08lX", st.st_mtime);
	sprintf_s(cpio.c_filesize, "%08lX", st.st_size);
	sprintf_s(cpio.c_devmajor, "%08X", major(st.st_dev));
	sprintf_s(cpio.c_devminor, "%08X", minor(st.st_dev));
	sprintf_s(cpio.c_rdevmajor, "%08X", major(st.st_rdev));
	sprintf_s(cpio.c_rdevminor, "%08X", minor(st.st_rdev));
	sprintf_s(cpio.c_namesize, "%08X", nsz);

	fseek(cpio_file, index, SEEK_SET);
	fwrite(&cpio, 1, sizeof(struct cpioArchive), cpio_file);

	while (!feof(input)) {
		char *buf = malloc(sizeof(char) * 1024);
		size_t read = fread(buf, 1, sizeof(buf), input);
		fwrite(buf, 1, read, cpio_file);
	}

	sprintf_s(cpio.c_ino, "%08X", 0);
	sprintf_s(cpio.c_mode, "%08X", 0);
	sprintf_s(cpio.c_uid, "%08X", 0);
	sprintf_s(cpio.c_gid, "%08X", 0);
	sprintf_s(cpio.c_nlink, "%08X", 0);
	sprintf_s(cpio.c_mtime, "%08X", 0);
	sprintf_s(cpio.c_filesize, "%08X", 0);
	sprintf_s(cpio.c_devmajor, "%08X", 0);
	sprintf_s(cpio.c_devminor, "%08X", 0);
	sprintf_s(cpio.c_rdevmajor, "%08X", 0);
	sprintf_s(cpio.c_rdevminor, "%08X", 0);
	sprintf_s(cpio.c_namesize, "%08X", 0);

	fseek(cpio_file, index, SEEK_END);
	fwrite(&cpio, 1, sizeof(struct cpioArchive), cpio_file);

	fclose(input);

	return 0;
}
