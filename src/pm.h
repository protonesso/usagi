#ifndef PM_H
#define PM_H

#include <stdbool.h>

struct options {
  bool force;
  bool needed;
  bool nodeps;
  bool noscripts;
  bool notriggers;
};

#endif
