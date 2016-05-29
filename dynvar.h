#ifndef BOCL_DYNVAR_H
#define BOCL_DYNVAR_H

#include "lispobj.h"

lispobj* symbol_value(lispobj*);
void init_dynamic_bindings(void);

#endif /* guard */
