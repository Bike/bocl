#include "symbol.h"
#include "alloc.h"

lispobj* the_class_symbol;

lispobj* make_symbol(lispobj* name, lispobj* package) {
  lispobj* result;
  result = alloc_lo(sizeof(lisp_symbol));
  result->class = the_class_symbol;
  LO_GET(lisp_symbol, *result)->name = name;
  LO_GET(lisp_symbol, *result)->package = package;
  return result;
}

bool symbolp(lispobj* object) {
  return object->class == the_class_symbol;
}
