#include "macro.h"
#include "alloc.h"

lispobj* the_class_macro;

lispobj* make_macro(lispobj* function) {
  lispobj* result;
  result = alloc_lo(sizeof(lisp_macro));
  result->class = the_class_macro;
  LO_GET(lisp_macro, *result)->function = function;
  return result;
}

bool macro_p(lispobj* object) {
  return object->class == the_class_macro;
}
