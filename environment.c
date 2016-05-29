#include "environment.h"
#include "alloc.h"
#include "global.h"

lispobj* the_class_environment;

lispobj* make_environment (lispobj* parent,
			   lispobj** value_names,
			   lispobj** value_values,
			   lispobj** funmacro_names,
			   lispobj** funmacro_values,
			   lispobj** symbol_macro_names,
			   lispobj** symbol_macro_values,
			   lispobj** specials) {
  lispobj* result;
  result = alloc_lo(sizeof(lisp_environment));
  result->class = the_class_environment;
  LO_GET(lisp_environment, *result)->value_names = value_names;
  LO_GET(lisp_environment, *result)->value_values = value_values;
  LO_GET(lisp_environment, *result)->funmacro_names =
    funmacro_names;
  LO_GET(lisp_environment, *result)->funmacro_values =
    funmacro_values;
  LO_GET(lisp_environment, *result)->symbol_macro_names =
    symbol_macro_names;
  LO_GET(lisp_environment, *result)->symbol_macro_values =
    symbol_macro_values;
  LO_GET(lisp_environment, *result)->specials = specials;
  return result;
}

bool environmentp(lispobj* object) {
  return object->class == the_class_environment;
}

#define DEFLOOKUP(ID, GLOBAL)						\
  lispobj* local_##ID##_lookup(lispobj* name, lispobj* env) {		\
    lispobj** namesptr, **valuesptr;					\
    lisp_environment* env_o = LO_GET(lisp_environment, *env);		\
    for (namesptr = env_o->ID##_names, valuesptr = env_o->ID##_values;	\
	 namesptr; ++namesptr, ++valuesptr)				\
      if (*namesptr == name) return *valuesptr;				\
    return NULL;							\
  }									\
  lispobj* ID##_lookup(lispobj* name, lispobj* env) {			\
    lispobj* result;							\
    lisp_environment* env_o = LO_GET(lisp_environment, *env);		\
    if (!env)								\
      return GLOBAL;							\
    else {								\
      result = local_##ID##_lookup(name, env);				\
      if (result) return result;					\
      else return ID##_lookup(name, env_o->parent);			\
    }									\
  }

DEFLOOKUP(value, NULL)
DEFLOOKUP(funmacro, global_funmacro_lookup(name))
DEFLOOKUP(symbol_macro, global_symbol_macro_lookup(name))

bool special_in_p(lispobj* symbol, lispobj* env) {
  lisp_environment* env_o = LO_GET(lisp_environment, *env);
  if (env) {
    for(lispobj** vars = env_o->specials; vars; ++vars) {
      if (*vars == symbol) return true;
    }
    return special_in_p(symbol, env_o->parent);
  } else return globally_special_p(symbol);
}
