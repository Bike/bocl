#ifndef BOCL_STRING_H
#define BOCL_STRING_H

#include "lispobj.h"
#include <stddef.h> // size_t

// FIXME: actually this is a simple string.
// FIXME: also could probably stand to think about unicode etc.

extern lispobj* the_class_string;

/* it is convenient for the string to be null-terminated,
 *  so that it can work with C functions, but a length is nice too
 * so we do both, at least for now.
 */

typedef struct lisp_string {
  size_t length;
  char vector[];
} lisp_string;

lispobj* make_string(const char*);
int lstrcmp(const char* , lispobj*);

#endif /* guard */
