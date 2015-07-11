#include "program.h"
#include <stdio.h>

int main(void){
  program_fkvm_t program;
  unsigned long size;

  size = load_program("program_input",&program);
  if (size == 0){
    perror("Couldn't load program");
    return 1;
  }
  
  for (int i=0; i<size; i++){
    printf("%d -> %c\n",i,get_index(&program,i));
  }

  destroy_program(&program);
  
  return 0;
}
