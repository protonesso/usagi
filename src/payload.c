#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "payload.h"

int usagi_write_payloadHeader(const char *file) {
	FILE *fp = fopen(file, "wb");

	if (!fp) {
		fprintf(stderr, "Cannot open file: %s\n", file);
		fclose(fp);
		return 1;
	}

	struct payloadHeader payload;

	memset(&payload, 0, sizeof(struct payloadHeader));
	snprintf(payload.extension, sizeof(payload.extension), "%s", ".UPK");
	snprintf(payload.magic, sizeof(payload.magic), "%ld", 0x6174617261786961);
	snprintf(payload.compress, sizeof(payload.compress), "%d", 1);
	snprintf(payload.version, sizeof(payload.version), "%f", 1.0);

	fwrite(&payload, 1, sizeof(struct payloadHeader), fp);

	fclose(fp);

	return 0;
}

int usagi_write_metaHeader(const char *file, metaHeader meta, const char *str) {
	FILE *fp = fopen(file, "ab");

	if (!fp) {
		fprintf(stderr, "Cannot open file: %s\n", file);
		fclose(fp);
		return 1;
	}

	fwrite(str, meta, strlen(str), fp);

	fclose(fp);

	return 0;
}
