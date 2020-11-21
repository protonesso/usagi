#include <stdio.h>
#include <string.h>

#include "payload.h"

int main() {
  usagi_write_payloadHeader("file");
  usagi_write_metaHeader("file", name, "rpm");
  usagi_write_metaHeader("file", version, "4.16.0");
  usagi_write_metaHeader("file", release, "1");
  usagi_write_metaHeader("file", summary, "RPM Package Manager");
  usagi_write_metaHeader("file", section, "admin");
  usagi_write_metaHeader("file", priority, "required");
  usagi_write_metaHeader("file", url, "http://rpm.org/");
  usagi_write_metaHeader("file", backup, "/etc/resolv.conf /etc/passwd");

  return 0;
}
