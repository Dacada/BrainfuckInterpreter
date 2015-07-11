#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
  memory_fkvm_t memory;
  char mem_dump[5000];

  memory_init(&memory);
  
  memory_dump(&memory,mem_dump,5000);printf("Just made\n%s\n\n",mem_dump);
  memory_plus(&memory);
  memory_dump(&memory,mem_dump,5000);printf("After +\n%s\n\n",mem_dump);
  
  printf("Number: %d\n",memory_get_val(&memory));
  if (memory_get_bool(&memory)){
    printf("True bool ok\n");
  } else {
    printf("True bool NOT OK\n");
  }
  
  memory_minus(&memory);
  memory_dump(&memory,mem_dump,5000);printf("After -\n%s\n\n",mem_dump);

  printf("Number: %d\n",memory_get_val(&memory));
  if (memory_get_bool(&memory)){
    printf("False bool NOT OK\n");
  } else {
    printf("False bool ok\n");
  }
  
  memory_plus(&memory);
  memory_left(&memory);
  memory_dump(&memory,mem_dump,5000);printf("After +<\n%s\n\n",mem_dump);

  memory_right(&memory);
  memory_dump(&memory,mem_dump,5000);printf("After >\n%s\n\n",mem_dump);
  
  for(int i=0;i<150;i++){ memory_right(&memory); }
  memory_dump(&memory,mem_dump,5000);printf("After >*150\n%s\n\n",mem_dump);

  memory_set_val(&memory, 'a');
  memory_dump(&memory,mem_dump,5000);printf("After setting 'a'\n%s\n\n",mem_dump);
  
  memory_destroy(&memory);
  
  return 0;
}
