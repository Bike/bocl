#ifndef BOCL_LISPOBJ_H
#define BOCL_LISPOBJ_H

/* Objects are represented as their class and arbitrary data.
 * The arbitrary data is an in-place char[]. This is allowed in C99
 *  but not before.
 * To do useful things with it, you put some object in the char[],
 *  as C lets you do with any object.
 * The LO_GET macro is used to hide a bit of this.
 * "LO" of course is short for "lisp obj(ect)".
 * LO_GET(structname, lispobj) returns a pointer to the char[],
 *  cast to be a pointer to a structname.
 * As an example of use, lisp "car" might be implemented like this:
 * lispobj* car(lispobj* cons) {
 *   return LO_GET(lisp_cons, *cons)->car;
 * }
 */

typedef struct lispobj {
  struct lispobj* class;
  char data[];
} lispobj;

#define LO_GET(TYPE, LO) ((TYPE*)((LO).data))

#endif /* guard */
