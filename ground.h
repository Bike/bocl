#ifndef BOCL_GROUND_H
#define BOCL_GROUND_H

#include "lispobj.h"

lispobj* cons_l(lispobj*);

lispobj* function_l(lispobj*, lispobj*);
lispobj* if_l(lispobj*, lispobj*);
lispobj* load_time_value_l(lispobj*, lispobj*);
lispobj* multiple_value_call_l(lispobj*, lispobj*);
lispobj* multiple_value_prog1_l(lispobj*, lispobj*);
lispobj* progn_l(lispobj*, lispobj*);
lispobj* quote_l(lispobj*, lispobj*);
lispobj* the_l(lispobj*, lispobj*);

#endif /* guard */
