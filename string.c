#include "string.h"
#include "alloc.h"
#include <string.h>

lispobj* the_class_string;

lispobj* make_string(const char* vector) {
  lispobj* result;
  size_t length;
  length = strlen(vector);
  /* note that sizeof excludes the flexible array member
   * and strlen excludes the null terminator */
  result = alloc_lo(sizeof(lisp_string) + length + 1);
  LO_GET(lisp_string, *result)->length = length;
  strcpy(LO_GET(lisp_string, *result)->vector, vector);
  return result;
}

int lstrcmp(const char* cstring, lispobj* string) {
  return strcmp(cstring, LO_GET(lisp_string, *string)->vector);
}
