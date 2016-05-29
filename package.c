#include "package.h"
#include "alloc.h"
#include "symbol.h"
#include "string.h"
#include "list.h"

lispobj* the_class_package;
lispobj* the_package_cl;
lispobj* the_package_impl;

lispobj* make_package(lispobj* name, lispobj* nicknames,
		      lispobj* use_list, lispobj* used_by_list,
		      lispobj* internals, lispobj* externals) {
  lispobj* result;
  result = alloc_lo(sizeof(lisp_package));
  result->class = the_class_package;
  LO_GET(lisp_package, *result)->name = name;
  LO_GET(lisp_package, *result)->nicknames = nicknames;
  LO_GET(lisp_package, *result)->use_list = use_list;
  LO_GET(lisp_package, *result)->used_by_list = used_by_list;
  LO_GET(lisp_package, *result)->internals = internals;
  LO_GET(lisp_package, *result)->externals = externals;
  return result;
}

bool packagep(lispobj* object) {
  return object->class == the_class_package;
}

lispobj* get_symbol(const char* name, lispobj* symbols) {
  DOLIST(symbol, symbols) {
    lispobj* string = LO_GET(lisp_symbol, *symbol)->name;
    if (!lstrcmp(name, string))
      return symbol;
  }
  return NULL;
}

lispobj* find_external_symbol(const char* name, lispobj* package) {
  return get_symbol(name,
		    LO_GET(lisp_package, *package)->externals);
}

lispobj* find_internal_symbol(const char* name, lispobj* package) {
  return get_symbol(name,
		    LO_GET(lisp_package, *package)->internals);
}

// find or intern something in CL
lispobj* cl_symbol(const char* name) {
  lispobj* result;
  result = find_external_symbol(name, the_package_cl);
  if (result) return result;
  else return intern(name, the_package_cl, true);
}

// find or intern something in IMPL
lispobj* impl_symbol(const char* name) {
  lispobj* result;
  result = find_internal_symbol(name, the_package_impl);
  if (result) return result;
  else return intern(name, the_package_impl, false);
}

/* this is not CL intern. it definitely actually interns.
 * a new symbol will be made! be careful to avoid duplicates! */
lispobj* intern(const char* name, lispobj* package, bool external)
{
  lisp_package* package_o = LO_GET(lisp_package, *package);
  lispobj* symbol;
  symbol = make_symbol(make_string(name), package);
  if (external)
    package_o->externals = cons(symbol, package_o->externals);
  else
    package_o->internals = cons(symbol, package_o->internals);
  return symbol;
}

void import(lispobj* symbol, lispobj* package, bool external) {
  lisp_symbol* symbol_o = LO_GET(lisp_symbol, *symbol);
  lisp_package* package_o = LO_GET(lisp_package, *package);
  // rehome if the symbol has no home package
  if (symbol_o->package == NULL) symbol_o->package = package;
  if (external)
    package_o->externals = cons(symbol, package_o->externals);
  else
    package_o->internals = cons(symbol, package_o->internals);
}
