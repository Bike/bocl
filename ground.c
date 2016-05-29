#include "lispobj.h"
#include "list.h"
#include "eval.h"
#include "values.h"
#include "function.h"

lispobj* cons_l(lispobj* combinand) {
  return fill_values(1,
		     cons(CAR(*combinand), CAR(*CDR(*combinand))));
}

/* some special forms use fill_values and some do not.
 * The ones that do return a fixed number of values.
 * The ones that don't keep the values from some computation,
 *  generally an evaluation. */

lispobj* function_l(lispobj* combinand, lispobj* env) {
  return fill_values(1, feval(CAR(*combinand), env));
}

lispobj* if_l(lispobj* combinand, lispobj* env) {
  lispobj *condition = CAR(*combinand);
  lispobj *consequence = CAR(*CDR(*combinand));
  lispobj *alternative = CAR(*CDR(*CDR(*combinand)));
  if (nullp(eval(condition, env))) return eval(alternative, env);
  else return eval(consequence, env);
}

/* LTV only needs to be specially handled by compilers.
 * "If a load-time-value expression is processed by eval,
 *  form is evaluated in a null lexical environment,
 *  and one value is returned."
 */
lispobj* load_time_value_l(lispobj* combinand, lispobj* env) {
  return fill_values(1, eval(CAR(*combinand), NULL));
}

lispobj* multiple_value_call_l(lispobj* combinand, lispobj* env) {
  lispobj* function = eval(CAR(*combinand), env);
  lispobj* argforms = CDR(*combinand);
  lispobj* args = nil;

  DOLIST(argform, argforms) {
    eval(argform, env);
    args = nconc2(args, values_to_list());
  }
  return apply(function, args);
}

lispobj* multiple_value_prog1_l(lispobj* combinand, lispobj* env) {
  /* (defmacro multiple-value-prog1 (&body forms)
   *   `(let ((save (multiple-value-list (first forms))))
   *     (progn ,@(rest forms))
   *     (values-list save)))
   * (but with gensym) but macro parsing is still hard. */
  lispobj* save;
  eval(CAR(*combinand), env);
  save = values_to_list();
  DOLIST(form, CDR(*combinand))
    eval(form, env); // discard results
  return list_to_values(save);
}

lispobj* progn_l(lispobj* combinand, lispobj* env) {
  lispobj* result;
  DOLIST(form, combinand)
    result = eval(form, env);
  return result;
}

lispobj* quote_l(lispobj* combinand, lispobj* env) {
  (void)env; // ignore
  return fill_values(1, CAR(*combinand));
}

// Types are for nerds.
lispobj* the_l(lispobj* combinand, lispobj* env) {
  return eval(CAR(*CDR(*combinand)), env);
}
