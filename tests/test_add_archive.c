#include <stdio.h>

#include "archive.h"
#include "payload.h"

int main(int argc, char* argv[]) {
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
