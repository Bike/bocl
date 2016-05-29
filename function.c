#include "function.h"
#include "error.h"

bool functionp(lispobj* object) {
  return subrp(object);
  //  return subrp(object) || closurep(object);
}

lispobj* apply(lispobj* function, lispobj* combinand) {
  if (subrp(function))
    return apply_subr(function, combinand);
  //  else if (closurep(function))
  //    return apply_closure(function, combinand);
  else error("Don't know how to apply");
}

lispobj* funcall1(lispobj* function, lispobj* arg1) {
  return apply(function, list(1, arg1));
}

lispobj* funcall2(lispobj* function, lispobj* arg1, lispobj* arg2)
{
  return apply(function, list(2, arg1, arg2));
}

lispobj* funcall3(lispobj* function,
		  lispobj* arg1, lispobj* arg2, lispobj* arg3) {
  return apply(function, list(3, arg1, arg2, arg3));
}
