#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <stdint.h>

struct payloadHeader {
	char extension[16];
	char magic[18];
	unsigned char compress[1];
	unsigned char version[2];
};

struct infoHeader {
	/* Required fields */
	char name[255];
	char version[255];
	char release[255];
	char summary[255];
	char section[255];
	char priority[255];

	/* Optional fields */
	char depends[255];
	char conflicts[255];
	char provides[255];
	char obsoletes[255];
	char url[255];
};

int usagi_add_payloadHeader(const char *file);

#endif
