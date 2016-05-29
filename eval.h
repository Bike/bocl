#include "lispobj.h"
#include <stdbool.h>

lispobj* macroexpand_1(lispobj*, lispobj*, lispobj*);
lispobj* eval_symbol(lispobj*, lispobj*);
lispobj* eval_cons(lispobj*, lispobj*);
lispobj* eval(lispobj*, lispobj*);
lispobj* evlis(lispobj*, lispobj*);
lispobj* feval_symbol(lispobj*, lispobj*);
bool lambda_form_p(lispobj*);
lispobj* feval_lambda(lispobj*, lispobj*);
lispobj* feval(lispobj*, lispobj*);
