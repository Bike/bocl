#include "built-in-class.h"
#include "alloc.h"

lispobj* the_class_built_in_class;

// Note that, for bootstrapping (see init.c), name might be NULL.
lispobj* make_built_in_class(lispobj* name) {
  lispobj* result;
  result = alloc_lo(sizeof(lisp_built_in_class));
  result->class = the_class_built_in_class;
  LO_GET(lisp_built_in_class, *result)->name = name;
  return result;
}
