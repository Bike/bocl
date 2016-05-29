#ifndef BOCL_CONS_H
#define BOCL_CONS_H

#include <stdbool.h>
#include "lispobj.h"

extern lispobj* the_class_cons;

typedef struct lisp_cons {
  lispobj* car;
  lispobj* cdr;
} lisp_cons;

lispobj* cons(lispobj*, lispobj*);
bool consp(lispobj*);

#define CAR(x) (LO_GET(lisp_cons, (x))->car)
#define CDR(x) (LO_GET(lisp_cons, (x))->cdr)

#endif /* guard */
