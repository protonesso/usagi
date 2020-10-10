#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <stdint.h>

struct payloadHeader {
	char extension[18];
	char magic[18];
	unsigned char compress[1];
	unsigned char version[2];
};

typedef enum {
	/* Required fields */
	name = 1,
	version = 2,
	release = 3,
	summary = 4,
	section = 5,
	priority = 6,
	url = 7,

	/* Optional fields */
	depends = 8,
	conflicts = 9,
	provides = 10,
	suggests = 11,
	obsoletes = 12
} metaHeader;

int usagi_write_payloadHeader(const char *file);
int usagi_write_metaHeader(const char *file, metaHeader meta, const char *str);

#endif
