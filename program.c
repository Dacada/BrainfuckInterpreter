#include "program.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long load_program(const char *const filename, program_fkvm_t *const program){
  FILE *fp;
  char *file_contents;
  unsigned long size;
  unsigned long prog_size=0;

  fp = fopen(filename,"r");
  if (fp == NULL){
    return 0;
  }
  
  if (fseek(fp,0,SEEK_END) == -1){
    return 0;
  }
  
  size = ftell(fp)+1;
  if (size == 0){
    return 0;
  }

  if (fseek(fp,0,SEEK_SET) == -1){
    return 0;
  }

  file_contents = malloc(size*sizeof(char));
  if (file_contents == NULL){
    free(file_contents);
    return 0;
  }

  if (fread(file_contents, sizeof(char), size-1, fp) != size-1){
    free(file_contents);
    return 0;
  }

  for (int i=0; i<size; i++){
    switch (file_contents[i]){
    case '+':
    case '-':
    case '<':
    case '>':
    case '[':
    case ']':
    case '.':
    case ',':
    case '#':
      prog_size++;
    }
  }

  program->array = malloc((prog_size+1)*sizeof(char));
  if (program->array == NULL){
    free(program->array);
    return 0;
  }
  prog_size=0;

  for (int i=0; i<size; i++){
    switch (file_contents[i]){
    case '+':
    case '-':
    case '<':
    case '>':
    case '[':
    case ']':
    case '.':
    case ',':
    case '#':
      (program->array)[prog_size++] = file_contents[i];
    }
  }
  
  free(file_contents);
  
  if (fclose(fp) == EOF){
    return 0;
  }

  return prog_size;
}

char get_index(const program_fkvm_t *const program, const unsigned long index){
  return (program->array)[index];
}

bool valid_program(const program_fkvm_t *const program, const unsigned long size){
  unsigned long balance_brackets=0;
  
  for (unsigned long i=0; i<size; i++){
    if ((program->array)[i] == '['){
      balance_brackets++;
    }
    else if ((program->array)[i] == ']'){
      if (balance_brackets == 0){
	return false;
      }
      balance_brackets--;
    }
  }

  return balance_brackets == 0;
}

void destroy_program(const program_fkvm_t *const program){
  free(program->array);
}
