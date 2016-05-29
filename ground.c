#include "lispobj.h"
#include "list.h"
#include "eval.h"

lispobj* cons_l(lispobj* combinand) {
  return cons(CAR(*combinand), CAR(*CDR(*combinand)));
}

lispobj* function_l(lispobj* combinand, lispobj* env) {
  return feval(CAR(*combinand), env);
}
