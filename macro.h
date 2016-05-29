#ifndef BOCL_MACRO_H
#define BOCL_MACRO_H

#include "lispobj.h"
#include <stdbool.h>

extern lispobj* the_class_macro;

typedef struct lisp_macro {
  lispobj* function;
} lisp_macro;

lispobj* make_macro(lispobj*);
bool macro_p(lispobj*);

#endif /* guard */
