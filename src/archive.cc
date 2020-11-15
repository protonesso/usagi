#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <iostream>
#include <fstream>
#include <cstring>

#include "archive.h"

int usagi_write_cpio(std::string archive, std::string file) {
	struct stat st;
	struct cpioArchive cpio;
	std::string trailer = "TRAILER!!!";

	std::ofstream archive_rw(archive,
			std::ios::out | std::ios::binary | std::ios::app);
	std::ifstream input(file, std::ifstream::in);

	int ret = stat(file.c_str(), &st);
	if (ret < 0) {
		std::cout << "Cannot open file: " << file << std::endl;
		input.close();
		return 1;
	}

	size_t nsz = file.size() + 1;

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
	sprintf(cpio.c_check, "%07x", 0);
	archive_rw.write(reinterpret_cast<char *>(&cpio), sizeof(struct cpioArchive));
	archive_rw.write(file.c_str(), file.size() + 3);

	while (input.good()) {
		char c;
		while (input.get(c)) {
			archive_rw << c;
		}
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
	sprintf(cpio.c_check, "%07x", 0);
	archive_rw.write(reinterpret_cast<char *>(&cpio), sizeof(struct cpioArchive));
	archive_rw.write(trailer.c_str(), trailer.size() + 1);

	input.close();
	archive_rw.close();

	return 0;
}

int main() {
	usagi_write_cpio("fuck", "niggers");
	return 0;
}
