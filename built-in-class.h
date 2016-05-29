#ifndef BOCL_BUILT_IN_CLASS_H
#define BOCL_BUILT_IN_CLASS_H

#include "lispobj.h"

extern lispobj* the_class_built_in_class;

typedef struct lisp_built_in_class {
  lispobj *name; // a symbol
} lisp_built_in_class;

lispobj* make_built_in_class(lispobj*);

#endif /* guard */
