#include "list.h"

lispobj* nil;

bool nullp(lispobj* object) {
  return object == nil;
}

lispobj* list(size_t count, ...) {
  size_t i;
  lispobj* result;
  lispobj* tail;
  va_list args;
  
  if (count == 0)
    return nil;

  va_start(args, count);
  result = tail = cons(va_arg(args, lispobj*), nil);

  for (i = 1; i < count; ++i) {
    CDR(*tail) = cons(va_arg(args, lispobj*), nil);
    tail = CDR(*tail);
  }

  va_end(args);
  return result;
}

lispobj* map1(lispobj*(*fun)(lispobj*,void*),
	      lispobj* list, void* data) {
  lispobj* result;
  lispobj* cur;

  if (nullp(list))
    return nil;
  else {
    result = cur = cons(fun(CAR(*list), data), nil);
    // could be non-vacuous but don't fix what ain't broke
    for(;;) {
      list = CDR(*list);
      if (nullp(list)) break;
      CDR(*cur) = cons(fun(CAR(*list), data), nil);
      cur = CDR(*cur);
    }
  }

  return result;
}

/* Unlike cl:last, this is invalid on anything but a cons. */
lispobj* last(lispobj* ls) {
  for(; !nullp(CDR(*ls)); ls = CDR(*ls));
  return ls;
}

lispobj* nconc2(lispobj* l1, lispobj* l2) {
  if (nullp(l1)) return l2;
  else {
    lispobj* las = last(l1);
    CDR(*las) = l2;
    return l1;
  }
}
