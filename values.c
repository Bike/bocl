#include "alloc.h" // for init
#include "error.h"
#include "list.h" // nil
#include "values.h"

// 20 is the minimum maximum (also yes, this is exclusive)
size_t multiple_values_limit = 20;

size_t nvalues;
lispobj** values;

// fill the values vector, then return the primary value.
lispobj* fill_values(size_t n, ...) {
  size_t i;
  va_list args;

  if (n > multiple_values_limit)
    error("too many values");
  
  nvalues = n;

  if (n == 0)
    return nil; // default for zero values
  va_start(args, n);
  for (i = 0; i < n; ++i)
    values[i] = va_arg(args, lispobj*);
  // TODO: make things nicer for gc by nulling everything else?
  va_end(args);
  return values[0];
}

void init_values(void) {
  values = alloc_lop_vector(multiple_values_limit);
}
