#include "subr.h"
#include "alloc.h"

lispobj* the_class_subr;

lispobj* make_subr(subr_fun* function) {
  lispobj* result;
  result = alloc_lo(sizeof(lisp_subr));
  result->class = the_class_subr;
  LO_GET(lisp_subr, *result)->function = function;
  return result;
}

bool subrp(lispobj* object) {
  return object->class == the_class_subr;
}

lispobj* apply_subr(lispobj* subr, lispobj* combinand) {
  subr_fun* function = LO_GET(lisp_subr, *subr)->function;
  return function(combinand);
}
