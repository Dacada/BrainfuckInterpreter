#include "stack.h"

#include <stdio.h>

int main(void){
  stack_fkvm_t stack;

  if (stack_init(&stack) == -1){
    return 1;
  }

  for (int i=0; i<200; i++){
    if (stack_push(&stack,i) == -1){
      return 1;
    }
  }

  while (!is_empty(&stack)){
    printf("%lu ",stack_pop(&stack));
  }
  printf("\n");

  stack_destroy(&stack);
  
  return 0;
}
