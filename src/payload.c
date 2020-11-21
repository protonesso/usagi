#include "payload.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int usagi_write_payloadHeader(const char *file) {
  struct payloadHeader payload;

  FILE *fp = fopen(file, "wb");
  if (!fp) {
    printf("Cannot open file: %s\n", file);
    fclose(fp);
    return 1;
  }

  memset(&payload, 0, sizeof(struct payloadHeader));
  sprintf(payload.ext, "%s", ".upk");
  sprintf(payload.magic, "%s", "617617");
  sprintf(payload.comp, "%d", 1);
  sprintf(payload.rel, "%d", 1);

  fwrite(&payload, 1, sizeof(struct payloadHeader), fp);

  fclose(fp);

  return 0;
}

int usagi_write_metaHeader(const char *file, metaHeader meta, const char *str) {
  FILE *fp = fopen(file, "ab");
  if (!fp) {
    printf("Cannot open file: %s\n", file);
    fclose(fp);
    return 1;
  }

  fwrite(str, meta, strlen(str), fp);

  fclose(fp);

  return 0;
}
