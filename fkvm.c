#include "memory.h"
#include "program.h"
#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  memory_fkvm_t memory;
  program_fkvm_t program;
  stack_fkvm_t stack;
  unsigned long program_size,number_brackets=0;
  unsigned long long dump_size;
  unsigned char c;
  char *dump=NULL;

  if (argc != 2){
    fprintf(stderr,"Usage %s filename\n",argv[0]);
    exit(EXIT_FAILURE);
  }

  if (memory_init(&memory) == -1){
    perror("Failed to load memory");
    exit(EXIT_FAILURE);
  }
  
  program_size = load_program(argv[1],&program);
  if (program_size == 0){
    perror("Failed to read file");
    exit(EXIT_FAILURE);
  }
  if (!valid_program(&program,program_size)){
    fprintf(stderr,"Invalid program.");
    exit(EXIT_FAILURE);
  }
    
  stack_init(&stack);

  for (unsigned long i=0; i<program_size; i++){
    c = get_index(&program,i);
    switch (c){
    case '+':
      memory_plus(&memory);
      break;
    case'-':
      memory_minus(&memory);
      break;
    case '<':
      memory_left(&memory);
      break;
    case '>':
      memory_right(&memory);
      break;
    case '[':
      if (!memory_get_bool(&memory)){
	for (i++;i<program_size;i++){
	  if (get_index(&program,i) == '['){
	    number_brackets++;
	  }
	  else if (get_index(&program,i) == ']'){
	    if (number_brackets == 0){
	      break;
	    } else {
	      number_brackets--;
	    }
	  }
	}
      } else {
	stack_push(&stack,i);
      }
      break;
    case ']':
      if (memory_get_bool(&memory)){
	i = stack_pop(&stack);
	stack_push(&stack,i);
      } else {
	stack_pop(&stack);
      }
      break;
    case '.':
      fputc(memory_get_val(&memory),stdout);
      break;
    case ',':
      c = fgetc(stdin);
      if (c != (unsigned char) EOF){
	memory_set_val(&memory,c);
      }
      break;
    case '#':
      free(dump);
      dump_size = memory_get_dump_size(&memory);
      dump = malloc(dump_size);
      if (dump == NULL) {
	perror("Memory error");
	exit(EXIT_FAILURE);
      }
      memory_dump(&memory,dump,dump_size);
      printf("-------------------------------------------\n");
      printf("Memory dumped:\n");
      printf("%s\n",dump);
      printf("-------------------------------------------\n\n");
      break;
    }
  }

  destroy_program(&program);
  memory_destroy(&memory);
  stack_destroy(&stack);
  
  exit(EXIT_SUCCESS);
}
