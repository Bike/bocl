#ifndef BOCL_GLOBAL_H
#define BOCL_GLOBAL_H

#include "lispobj.h"
#include <stdbool.h>

lispobj* global_funmacro_lookup(lispobj*);
lispobj* global_symbol_macro_lookup(lispobj*);
bool globally_special_p(lispobj*);

void defun(lispobj*, lispobj*);

void init_globals(void);

#endif /* guard */
