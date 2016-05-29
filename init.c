#include "alloc.h"
#include "dynvar.h"
#include "global.h"
#include "list.h"
#include "values.h"

#include "built-in-class.h"
#include "cons.h"
#include "macro.h"
#include "package.h"
#include "special_operator.h"
#include "string.h"
#include "subr.h"
#include "symbol.h"

#include "ground.h"

void init() {
  // We have to do this one specially to get the recursion right.
  the_class_built_in_class = alloc_lo(sizeof(lisp_built_in_class));
  the_class_built_in_class->class = the_class_built_in_class;

  // No symbols yet, so all the class names are just NULL.
  the_class_cons = make_built_in_class(NULL);
  the_class_symbol = make_built_in_class(NULL);
  the_class_package = make_built_in_class(NULL);
  the_class_string = make_built_in_class(NULL);

  nil = make_symbol(make_string("NIL"), NULL);
  
  the_package_cl =
    make_package(make_string("COMMON-LISP"), list(1, "CL"),
		 nil, nil, nil, nil);
  the_package_impl =
    make_package(make_string("IMPL"), nil, nil, nil, nil, nil);
  import(nil, the_package_cl, true);
  
  LO_GET(lisp_built_in_class, *the_class_built_in_class)->name =
    cl_symbol("BUILT-IN-CLASS");
  LO_GET(lisp_built_in_class, *the_class_cons)->name =
    cl_symbol("CONS");
  LO_GET(lisp_built_in_class, *the_class_package)->name =
    cl_symbol("PACKAGE");
  LO_GET(lisp_built_in_class, *the_class_symbol)->name =
    cl_symbol("SYMBOL");
  LO_GET(lisp_built_in_class, *the_class_string)->name =
    cl_symbol("STRING");

  the_class_subr = make_built_in_class(impl_symbol("SUBR"));
  the_class_macro = make_built_in_class(impl_symbol("MACRO"));
  the_class_special_operator =
    make_built_in_class(impl_symbol("SPECIAL-OPERATOR"));

  init_globals();
  init_values();
  init_dynamic_bindings();
  GC_INIT();

  defun(cl_symbol("CONS"), make_subr(cons_l));
  defun(cl_symbol("FUNCTION"), make_special_operator(function_l));
}
