#ifndef BOCL_ARRAY_H
#define BOCL_ARRAY_H

// FIXME: Right now it's just simple-arrays.

typedef struct lisp_array {
  
  lispobj** vector;
} lisp_array;

#endif /* guard */
