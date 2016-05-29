#ifndef BOCL_ALLOC_H
#define BOCL_ALLOC_H

#include "lispobj.h"
#include <stddef.h> // size_t
#include <gc/gc.h>

/* Size is the size of the internal object, i.e. not including
 * the class pointer, which alloc_lo transparently adds on. */
lispobj* alloc_lo(size_t);
/* Size is how many pointers we want space for. */
lispobj** alloc_lop_vector(size_t);

#endif /* guard */
