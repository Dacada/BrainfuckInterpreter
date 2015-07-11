#include "memory.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#ifndef MEM_INCREASE_UNIT
#define MEM_INCREASE_UNIT 128
#endif

int memory_init(memory_fkvm_t *const memory){
  unsigned char *temparray;
  
  temparray = malloc(MEM_INCREASE_UNIT*sizeof(unsigned char));
  if (temparray == NULL){
    free(temparray);
    return -1;
  }
  memory->array = temparray;
  
  for(int i=0; i<MEM_INCREASE_UNIT; i++){
    (memory->array)[i] = 0;
  }

  memory->size = MEM_INCREASE_UNIT;

  memory->ptr = 0;

  return 0;
}

static void add_to_line(char *const buffer, const char *const what){
  int i,j;
  for (i=0;;i++){
    if (buffer[i] == '\0'){
      break;
    }
  }
  
  for (j=0;;i++,j++){
    if (what[j] == '\0'){
      break;
    }
    buffer[i] = what[j];
  }

  buffer[++i] = '\0';
}

void memory_dump(const memory_fkvm_t *const memory, char *const buffer, const unsigned long long buff_size){
  char num[100];
  unsigned long i;

  for (i=0; i<buff_size; i++){
    buffer[i] = '\0';
  }
  for (i=0; i<(memory->size); i++){
    if (i % 8 == 0){
      if (i != 0){
	add_to_line(buffer,"\n");
      }
      sprintf(num,"%05lu:\t",i);
      add_to_line(buffer,num);
    }
    if (i == memory->ptr){
      sprintf(num,"|%03d| ",(memory->array)[i]);
    } else {
      sprintf(num,"%03d ",(memory->array)[i]);
    }
    add_to_line(buffer,num);
  }
}

int memory_plus(memory_fkvm_t *const memory){
  if (memory->size == 0){
    errno = ENOMEM;
    return -1;
  }
  ((memory->array)[memory->ptr])++;
  return 0;
}
int memory_minus(memory_fkvm_t *const memory){
  if (memory->size == 0){
    errno = ENOMEM;
    return -1;
  }
  ((memory->array)[memory->ptr])--;
  return 0;
}


int memory_left(memory_fkvm_t *const memory){
  unsigned char *temparray;
  unsigned long newsize;
  
  if (memory->size == 0){
    errno = ENOMEM;
    return -1;
  }

  if (memory->ptr == 0){
    newsize = (memory->size) + MEM_INCREASE_UNIT;
    temparray = realloc(memory->array,newsize);
    if (temparray == NULL){
      free(temparray);
      return -1;
    }
    if (temparray != memory->array){
      free(memory->array);
      memory->array = temparray;
    }

    for (unsigned long i=(memory->size)-1;; i--){
      (memory->array)[i+MEM_INCREASE_UNIT] = (memory->array)[i];
      (memory->array)[i] = 0;
      if (i == 0){
	break;
      }
    }
    memory->ptr = MEM_INCREASE_UNIT;
    memory->size = newsize;
  }
  (memory->ptr)--;
  return 0;
}
int memory_right(memory_fkvm_t *const memory){
  unsigned char *temparray;
  unsigned long newsize;

  if (memory->size == 0){
    errno = ENOMEM;
    return -1;
  }
  
  if (memory->ptr == (memory->size)-1){
    newsize = (memory->size) + MEM_INCREASE_UNIT;
    temparray = realloc(memory->array,newsize);
    if (temparray == NULL){
      free(temparray);
      return -1;
    }
    if (temparray != memory->array){
      free(memory->array);
      memory->array = temparray;
    }
      
    for(unsigned long i=0; i<newsize; i++){
      (memory->array)[i] = 0;
    }
    memory->size = newsize;
  }
  (memory->ptr)++;
  return 0;
}

bool memory_get_bool(memory_fkvm_t *const memory){
  return memory_get_val(memory) != 0;
}

unsigned char memory_get_val(memory_fkvm_t *const memory){
  return (memory->array)[memory->ptr];
}

void memory_set_val(memory_fkvm_t *const memory, const unsigned char c){
  (memory->array)[memory->ptr] = c;
}

unsigned long long memory_get_dump_size(memory_fkvm_t *const memory){
  return (memory->size)*5 + ((memory->size)/8+8)*10; //More, just in case
}


void memory_destroy(memory_fkvm_t *const memory){
  free(memory->array);
  memory->size=0;
}
