#ifndef _FKVM_STACK_H
#define _FKVM_STACK_H

#include <stdbool.h>

typedef struct {
  unsigned long *array;
  int alloc_size;
  int elements;
} stack_fkvm_t;

int stack_init(stack_fkvm_t *const stack);

unsigned long stack_pop(stack_fkvm_t *const stack);
int stack_push(stack_fkvm_t *const stack, const unsigned long value);

bool is_empty(stack_fkvm_t *const stack);

void stack_destroy(stack_fkvm_t *const stack);
  
#endif
