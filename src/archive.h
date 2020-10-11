#ifndef ARCHIVE_H
#define ARCHIVE_H

struct cpioArchive {
	char c_magic[8];
	char c_ino[8];
	char c_mode[8];
	char c_uid[8];
	char c_gid[8];
	char c_nlink[8];
	char c_mtime[8];
	char c_filesize[8];
	char c_devmajor[8];
	char c_devminor[8];
	char c_rdevmajor[8];
	char c_rdevminor[8];
	char c_namesize[8];
	char c_check[8];
};

void usagi_fexpand(FILE *file, size_t amount, int val);
int usagi_write_cpio(FILE *cpio_file, const char *file, const char *iname);

#endif
