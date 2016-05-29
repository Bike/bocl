#include "cons.h"
#include "alloc.h"

lispobj* the_class_cons;

lispobj* cons(lispobj* car, lispobj* cdr) {
  lispobj* result;
  result = alloc_lo(sizeof(lisp_cons));
  result->class = the_class_cons;
  LO_GET(lisp_cons, *result)->car = car;
  LO_GET(lisp_cons, *result)->cdr = cdr;
  return result;
}

bool consp(lispobj* object) {
  // boy, i hope == has to return a bool.
  return object->class == the_class_cons;
}
