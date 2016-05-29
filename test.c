#include "init.h"
#include "eval.h"
#include "list.h"
#include "package.h"
#include "error.h"

int main(void) {
  init();
  lispobj* cons_s = cl_symbol("CONS");
  lispobj* function_s = cl_symbol("FUNCTION");
  lispobj* function_form = list(2, function_s, cons_s);
  lispobj* cons = eval(function_form, NULL);
  if (!cons) error("cons null");
  lispobj* form =
    list(3, cons_s, function_form, function_form);
  lispobj* result = eval(form, NULL);
  if (!result) error("result null");
  if (result->class != the_class_cons) error("result not a cons");
  if (!CAR(*result)) error("car null");
  if (!CDR(*result)) error("cdr null");
  if (CAR(*result) != cons) error("car wrong");
  if (CDR(*result) != cons) error("cdr wrong");
  return 0;
}
