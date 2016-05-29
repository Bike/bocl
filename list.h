#ifndef BOCL_LIST_H
#define BOCL_LIST_H

/* This file includes both cons.h and symbol.h (for nil).
 * It contains the definition of nil.
 * It further contains various utilities for working with lists. */

#include "cons.h"
#include "symbol.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

extern lispobj* nil;

bool nullp(lispobj*);
lispobj* list(size_t, ...);

/* Calls FUN on each element of LIST and returns a new LIST with
 * the result. FUN receives the DATA as a second argument. */
lispobj* map1(lispobj*(*)(lispobj*, void*), lispobj*, void*);

lispobj* last(lispobj*);
lispobj* nconc2(lispobj*, lispobj*);

/* declaration in the initialization is ok in C99
 * C macros suck so bad. dolist_list is a reserved identifier now.
 * My kingdom for gensym.
 * (You need a new variable so that LIST isn't mutated.) */
#define DOLIST(VAR, LIST)					\
  for(lispobj* VAR = CAR(*LIST), *dolist_list = LIST;		\
      !nullp(dolist_list);					\
      dolist_list = CDR(*dolist_list), VAR = CAR(*dolist_list))

#endif /* guard */
