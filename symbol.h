#ifndef BOCL_SYMBOL_H
#define BOCL_SYMBOL_H

#include "lispobj.h"
#include <stdbool.h>

extern lispobj* the_class_symbol;

typedef struct lisp_symbol {
  lispobj* name;
  lispobj* package;
} lisp_symbol;

lispobj* make_symbol(lispobj*, lispobj*);
bool symbolp(lispobj*);

#endif /* guard */
