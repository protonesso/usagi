#include <stdio.h>
#include <string.h>

#include "payload.h"

int usagi_add_payloadHeader(const char *file) {
	FILE *fp = fopen(file, "wb");
	char buf[16];

	if (!fp) {
		fprintf(stderr, "Cannot open file: %s\n", file);
		fclose(fp);
		return 1;
	}

	struct payloadHeader payload;

	memset(&payload, 0, sizeof(struct payloadHeader));
	snprintf(payload.dotusagi, sizeof(payload.dotusagi), "%s", ".USAGI");
	snprintf(payload.magic, sizeof(payload.magic), "%d", 0x1037);
	snprintf(payload.compress, sizeof(payload.compress), "%d", 1);
	snprintf(payload.version, sizeof(payload.version), "%f", 1.0);

	fwrite(&payload, 1, sizeof(struct payloadHeader), fp);

	fclose(fp);

	return 0;
}
