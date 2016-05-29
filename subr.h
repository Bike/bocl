#ifndef BOCL_SUBR_H
#define BOCL_SUBR_H

#include "lispobj.h"
#include <stdbool.h>

extern lispobj* the_class_subr;

// function, not function pointer
typedef lispobj*(subr_fun)(lispobj*);

typedef struct lisp_subr {
  subr_fun* function;
} lisp_subr;

lispobj* make_subr(subr_fun*);
bool subrp(lispobj*);
lispobj* apply_subr(lispobj*, lispobj*);

#endif /* guard */
