#ifndef BOCL_PACKAGE_H
#define BOCL_PACKAGE_H

#include "lispobj.h"
#include <stdbool.h>

extern lispobj* the_class_package;
extern lispobj* the_package_cl;
extern lispobj* the_package_impl;

typedef struct lisp_package {
  lispobj* name; // string
  lispobj* nicknames; // list of strings
  lispobj* use_list; // list of packages
  lispobj* used_by_list; // list of packages
  lispobj* internals; // list of symbols
  lispobj* externals; // list of symbols
} lisp_package;

lispobj* make_package(lispobj*, lispobj*,
		      lispobj*, lispobj*, lispobj*, lispobj*);
bool packagep(lispobj*);
lispobj* get_symbol(const char*, lispobj*);
lispobj* find_external_symbol(const char*, lispobj*);
lispobj* find_internal_symbol(const char*, lispobj*);
lispobj* cl_symbol(const char*);
lispobj* impl_symbol(const char*);
lispobj* intern(const char*, lispobj*, bool);
void import(lispobj*, lispobj*, bool);

#endif /* guard */
