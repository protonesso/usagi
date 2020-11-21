#include <stdio.h>

#include "archive.h"
#include "payload.h"

int main(int argc, char* argv[]) {
  usagi_write_payloadHeader(argv[1]);
  usagi_write_metaHeader(argv[1], name, "rpm");
  usagi_write_metaHeader(argv[1], version, "4.16.0");
  usagi_write_metaHeader(argv[1], release, "1");
  usagi_write_metaHeader(argv[1], summary, "RPM Package Manager");
  usagi_write_metaHeader(argv[1], section, "admin");
  usagi_write_metaHeader(argv[1], priority, "required");
  usagi_write_metaHeader(argv[1], url, "http://rpm.org/");
  usagi_write_metaHeader(argv[1], backup, "/etc/resolv.conf /etc/passwd");

  FILE* archive = fopen(argv[1], "ab");
  if (!archive) {
    printf("Cannot open file: %s\n", argv[1]);
    return 1;
  }

  for (int i = 2; i < argc; i++) {
    usagi_write_cpio(archive, argv[i]);
  }

  fclose(archive);

  return 0;
}
