#include "alloc.h" // for init
#include "error.h"
#include "list.h"
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

// I'm somehow glad list.h was already a dependency.

lispobj* values_to_list(void) {
  size_t i;
  lispobj* result = nil;
  /* Written in this weird way because I don't want to think about
   *  size_t underflow. */
  for (i = nvalues - 1; i > 0; --i)
    result = cons(values[i], result);
  if (nvalues > 0)
    return cons(values[0], result);
  else
    return nil;
}

lispobj* list_to_values(lispobj* ls) {
  size_t i;
  for (i = 0; !nullp(ls); ++i, ls = CDR(*ls))
    if (i >= multiple_values_limit)
      error("Too many values (in list_to_values)");
    else values[i] = CAR(*ls);
  nvalues = i;
  return values[0];
}
