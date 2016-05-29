#ifndef BOCL_SPECIAL_OPERATOR_H
#define BOCL_SPECIAL_OPERATOR_H

#include "lispobj.h"
#include <stdbool.h>

extern lispobj* the_class_special_operator;

// function, not function pointer
typedef lispobj*(fsubr_fun)(lispobj*, lispobj*);

typedef struct lisp_special_operator {
  fsubr_fun* function;
} lisp_special_operator;

lispobj* make_special_operator(fsubr_fun*);
bool special_operator_p(lispobj*);
lispobj* special_operate(lispobj*, lispobj*, lispobj*);

#endif /* guard */
