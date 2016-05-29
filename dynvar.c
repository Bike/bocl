#include "dynvar.h"
#include "list.h"
#include "error.h"

/* This would be thread-local, but without threads it doesn't
 * really matter. */
lispobj* dynamic_bindings; // alist

lispobj* symbol_value(lispobj* name) {
  DOLIST(pair, dynamic_bindings)
    if (CAR(*pair) == name)
      return CDR(*pair);
  error("Unbound dynamic variable");
}

void init_dynamic_bindings(void) {
  dynamic_bindings = nil;
}
