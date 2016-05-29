#include "eval.h"

#include "lispobj.h"
#include "list.h"
#include "environment.h"
#include "function.h"
#include "macro.h"
#include "package.h" // cl_symbol
#include "special_operator.h"
#include "global.h"
#include "dynvar.h"
#include "error.h"

lispobj* macroexpand_1(lispobj* macro,
		       lispobj* form, lispobj* env) {
  return funcall3(symbol_value(cl_symbol("*MACROEXPAND_HOOK*")),
		  LO_GET(lisp_macro, *macro)->function, form, env);
}

lispobj* eval_symbol(lispobj* form, lispobj* env) {
  lispobj *result, *smacro;
  smacro = symbol_macro_lookup(form, env);
  if (smacro)
    return eval(macroexpand_1(smacro, form, env), env);
  else if (special_in_p(form, env)) {
    result = symbol_value(form);
  } else
    result = value_lookup(form, env);

  if (result) return result;
  else error("Unbound variable");
}

lispobj* eval_cons(lispobj* form, lispobj* env) {
  lispobj *combiner, *combinand;
  combiner = feval(CAR(*form), env);
  combinand = CDR(*form);
  if (special_operator_p(combiner))
    return special_operate(combiner, form, env);
  if (macro_p(combiner))
    return macroexpand_1(combiner, form, env);
  else return apply(combiner, evlis(combinand, env));
}

lispobj* eval(lispobj* form, lispobj* env) {
  if (symbolp(form))
    return eval_symbol(form, env);
  else if (consp(form))
    return eval_cons(form, env);
  else
    return form;
}

/* This is necessary because map1(eval, forms, env) triggers
 * -Wincompatible-pointer-types because
 * lispobj*(*)(lispobj*,void*)
 * is, for some reason, "incompatible" with
 * lispobj*(*)(lispobj*,lispobj*). Some standards paranoia about
 * a computer with different calling conventions, I guess? */
lispobj* evlis_hack(lispobj* form, void* env) {
  return eval(form, env);
}

lispobj* evlis(lispobj* forms, lispobj* env) {
  return map1(evlis_hack, forms, env);
}

lispobj* feval_symbol(lispobj* symbol, lispobj* env) {
  lispobj* result;
  result = funmacro_lookup(symbol, env);
  if (result) return result;
  else error("Unbound function");
}

// FIXME: stubs
bool lambda_form_p(lispobj* form) { return false; }
lispobj* feval_lambda(lispobj* form, lispobj* env) {
  error("No lambdas yet");
}

lispobj* feval(lispobj* form, lispobj* env) {
  if (symbolp(form))
    return feval_symbol(form, env);
  else if (consp(form)) {
    if (lambda_form_p(form))
      return feval_lambda(form, env);
    else error("Cons in head position");
  } else
    error("Cannot feval thing");
}
