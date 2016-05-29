#include <stdlib.h>
#include <stdio.h>

void error(const char* reason) {
  fputs(reason, stderr);
  fputc('\n', stderr);
  exit(1);
}
