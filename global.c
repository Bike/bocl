#include "global.h"
#include "list.h"

/* unlike the lexical environments' fixed lengths,
 * we have to allow definitions, so these are lisp lists. */

lispobj* global_funmacros;
lispobj* global_specials;

lispobj* global_funmacro_lookup(lispobj* name) {
  DOLIST(pair, global_funmacros)
    if (CAR(*pair) == name)
      return CDR(*pair);
  return NULL;
}

// FIXME: stub
lispobj* global_symbol_macro_lookup(lispobj* name) {
  return NULL;
}

bool globally_special_p(lispobj* name) {
  DOLIST(sym, global_specials)
    if (sym == name)
      return true;
  return false;
}

void defun(lispobj* name, lispobj* value) {
  global_funmacros = cons(cons(name, value), global_funmacros);
}

void init_globals(void) {
  global_funmacros = nil;
  global_specials = nil;
}
