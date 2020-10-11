#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "archive.h"

void usagi_fexpand(FILE *file, size_t amount, int val) {
	while (amount--) {
		printf("writing %d\n", val);
		fputc(val, file);
	}
}

int usagi_write_cpio(FILE *cpio_file, const char *file, const char *iname) {
	struct stat st;
	struct cpioArchive cpio;

	size_t index = ftell(cpio_file);
	size_t offset = index % 512;

	FILE *fd = fopen(file, "rb");;
	int ret = fstat(fileno(fd), &st);
	if (ret < 0) {
		fprintf(stderr, "Cannot open file: %s\n", file);
		fclose(fd);
		return 1;
	}

	fseek(fd, 0, SEEK_END);
	int nsz = ftell(fd);

	snprintf(cpio.c_magic, sizeof(cpio.c_magic), "%s", "070701");
	snprintf(cpio.c_ino, sizeof(cpio.c_ino), "\012%ld", st.st_ino);
	snprintf(cpio.c_mode, sizeof(cpio.c_mode), "\012%d", st.st_mode);
	snprintf(cpio.c_uid, sizeof(cpio.c_uid), "\012%d", st.st_uid);
	snprintf(cpio.c_gid, sizeof(cpio.c_gid), "\012%d", st.st_gid);
	snprintf(cpio.c_nlink, sizeof(cpio.c_nlink), "\012%ld", st.st_nlink);
	snprintf(cpio.c_mtime, sizeof(cpio.c_mtime), "\012%ld", st.st_mtime);
	snprintf(cpio.c_filesize, sizeof(cpio.c_filesize), "\012%ld", st.st_size);
	snprintf(cpio.c_devmajor, sizeof(cpio.c_devmajor), "\012%d", major(st.st_dev));
	snprintf(cpio.c_devminor, sizeof(cpio.c_devmajor), "\012%d", minor(st.st_dev));
	snprintf(cpio.c_rdevmajor, sizeof(cpio.c_devmajor), "\012%d", major(st.st_rdev));
	snprintf(cpio.c_rdevminor, sizeof(cpio.c_devmajor), "\012%d", minor(st.st_rdev));
	snprintf(cpio.c_namesize, sizeof(cpio.c_namesize), "\012%d", nsz);
	// snprintf(cpio.c_check, sizeof(cpio.c_check), "\012%d", checksum);

	fseek(cpio_file, index, SEEK_SET);
	fwrite(&cpio, 1, sizeof(struct cpioArchive), cpio_file);
	fclose(fd);

	FILE *input = fopen(file, "rb");
	if (!input) {
		fprintf(stderr, "Cannot open file: %s\n", file);
		fclose(input);
		return 1;
	}

	while (!feof(input)) {
		char *buf = malloc(sizeof(char) * 1024);
		size_t read = fread(buf, 1, sizeof(buf), input);
		printf("a writing %s\n", file);
		fwrite(buf, 1, read, cpio_file);
	}

	size_t end = ftell(cpio_file);

	fseek(cpio_file, end, SEEK_SET);
	fclose(input);

	return 0;
}
