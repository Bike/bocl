#include "special_operator.h"
#include "alloc.h"

lispobj* the_class_special_operator;

lispobj* make_special_operator(fsubr_fun* function) {
  lispobj* result;
  result = alloc_lo(sizeof(lisp_special_operator));
  result->class = the_class_special_operator;
  LO_GET(lisp_special_operator, *result)->function = function;
  return result;
}

bool special_operator_p(lispobj* object) {
  return object->class == the_class_special_operator;
}

lispobj* special_operate(lispobj* so,
			 lispobj* combinand, lispobj* env) {
  fsubr_fun* function;
  function = LO_GET(lisp_special_operator, *so)->function;
  return function(combinand, env);
}
