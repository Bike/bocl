#include "lispobj.h"
#include <stdarg.h>

extern size_t multiple_values_limit;

extern size_t nvalues;
/* This would be thread-local, but without threads it doesn't
 * really matter. */
extern lispobj** values;

lispobj* fill_values(size_t n, ...);
void init_values(void);

lispobj* values_to_list(void);
lispobj* list_to_values(lispobj*);
