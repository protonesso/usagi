#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "payload.h"

int usagi_write_payloadHeader(const char *file) {
	struct payloadHeader payload;

	FILE *fp = fopen_s(file, "wb");
	if (!fp) {
		printf_s("Cannot open file: %s\n", file);
		fclose(fp);
		return 1;
	}

	memset_s(&payload, 0, sizeof(struct payloadHeader));
	sprintf_s(payload.ext, "%s", ".upk");
	sprintf_s(payload.magic, "%s", "617617");
	sprintf_s(payload.comp, "%d", 1);
	sprintf_s(payload.rel, "%d", 1);

	fwrite(&payload, 1, sizeof(struct payloadHeader), fp);

	fclose(fp);

	return 0;
}

int usagi_write_metaHeader(const char *file, metaHeader meta, const char *str) {
	FILE *fp = fopen_s(file, "ab");
	if (!fp) {
		printf_s("Cannot open file: %s\n", file);
		fclose(fp);
		return 1;
	}

	fwrite(str, meta, strlen(str), fp);

	fclose(fp);

	return 0;
}
