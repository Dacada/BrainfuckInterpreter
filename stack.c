#include "stack.h"

#include <stdbool.h>
#include <stdlib.h>

#ifndef STACK_INCRESE_UNIT
#define STACK_INCREASE_UNIT 128
#endif

int stack_init(stack_fkvm_t *const stack){
  stack->array = malloc(STACK_INCREASE_UNIT*sizeof(unsigned long));
  if (stack->array == NULL){
    return -1;
  }
  stack->alloc_size = STACK_INCREASE_UNIT;
  stack->elements = 0;
  return 0;
}


unsigned long stack_pop(stack_fkvm_t *const stack){
  return (stack->array)[--(stack->elements)];
}

int stack_push(stack_fkvm_t *const stack, const unsigned long value){
  unsigned long *newarray;
  int newsize;
  
  if (stack->elements == stack->alloc_size){
    newsize = stack->alloc_size + STACK_INCREASE_UNIT;
    newarray = realloc(stack->array, newsize*sizeof(unsigned long));
    if (newarray == NULL){
      free(newarray);
      return -1;
    }
    if (newarray != stack->array){
      free(stack->array);
      stack->array = newarray;
    }
  }
  (stack->array)[(stack->elements)++] = value;
  return 0;
}


bool is_empty(stack_fkvm_t *const stack){
  return stack->elements == 0;
}


void stack_destroy(stack_fkvm_t *const stack){
  free(stack->array);
  stack->alloc_size = 0;
  stack->elements = 0;
}
