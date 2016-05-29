#include "alloc.h"

/* lispobj's flexible array member is not counted in sizeof. */

lispobj* alloc_lo(size_t size) {
  return (lispobj*)GC_MALLOC(sizeof(lispobj) + size);
}

lispobj** alloc_lop_vector(size_t size) {
  return (lispobj**)GC_MALLOC(sizeof(lispobj*) * size);
}
