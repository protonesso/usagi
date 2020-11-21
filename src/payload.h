#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <stdint.h>

struct payloadHeader {
  char ext[8];
  char magic[6];
  char comp[2];
  char rel[3];
  char null[1];	 // must be always empty
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
  obsoletes = 12,
  backup = 13
} metaHeader;

int usagi_write_payloadHeader(const char *file);
int usagi_write_metaHeader(const char *file, metaHeader meta, const char *str);

#endif
