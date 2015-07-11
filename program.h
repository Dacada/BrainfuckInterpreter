#ifndef _KKVM_PROGRAM_H
#define _KKVM_PROGRAM_H

#include <stdbool.h>

typedef struct{
  char *array;
} program_fkvm_t;

unsigned long load_program(const char *const filename, program_fkvm_t *const program);
char get_index(const program_fkvm_t *const program, const unsigned long index);
bool valid_program(const program_fkvm_t *const program, const unsigned long size);
void destroy_program(const program_fkvm_t *const program);

#endif
