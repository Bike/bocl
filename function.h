#ifndef BOCL_FUNCTION_H
#define BOCL_FUNCTION_H

#include "subr.h"
#include "list.h"

bool functionp(lispobj*);

lispobj* apply(lispobj*, lispobj*);

lispobj* funcall1(lispobj*, lispobj*);
lispobj* funcall2(lispobj*, lispobj*, lispobj*);
lispobj* funcall3(lispobj*, lispobj*, lispobj*, lispobj*);

#endif /* guard */
