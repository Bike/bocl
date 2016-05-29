#ifndef BOCL_ENVIRONMENT_H
#define BOCL_ENVIRONMENT_H

#include "lispobj.h"
#include <stdbool.h>

extern lispobj* the_class_environment;

typedef struct lisp_environment {
  lispobj* parent;
  lispobj** value_names;
  lispobj** value_values;

  // i.e., functions and macros
  lispobj** funmacro_names;
  lispobj** funmacro_values;

  lispobj** symbol_macro_names;
  lispobj** symbol_macro_values;
  
  lispobj** specials;
} lisp_environment;

lispobj* make_environment(lispobj*, lispobj**, lispobj**,
			  lispobj**, lispobj**,
			  lispobj**, lispobj**,
			  lispobj**);
bool environmentp(lispobj*);

lispobj* local_value_lookup(lispobj*, lispobj*);
lispobj* value_lookup(lispobj*, lispobj*);
lispobj* local_funmacro_lookup(lispobj*, lispobj*);
lispobj* funmacro_lookup(lispobj*, lispobj*);
lispobj* local_symbol_macro_lookup(lispobj*, lispobj*);
lispobj* symbol_macro_lookup(lispobj*, lispobj*);

bool special_in_p(lispobj*, lispobj*);

#endif /* guard */
