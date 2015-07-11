#ifndef _FKVM_MEMORY_H
#define _FKVM_MEMORY_H

#include <stdbool.h>

typedef struct {
  unsigned char *array;
  unsigned long size;
  unsigned long ptr;
} memory_fkvm_t;

int memory_init(memory_fkvm_t *const memory);

void memory_dump(const memory_fkvm_t *const memory, char *const buffer, const unsigned long long buff_size);

int memory_plus(memory_fkvm_t *const memory);
int memory_minus(memory_fkvm_t *const memory);

int memory_left(memory_fkvm_t *const memory);
int memory_right(memory_fkvm_t *const memory);

bool memory_get_bool(memory_fkvm_t *const memory);
unsigned char memory_get_val(memory_fkvm_t *const memory);
void memory_set_val(memory_fkvm_t *const memory, const unsigned char c);
unsigned long long memory_get_dump_size(memory_fkvm_t *const memory);

void memory_destroy(memory_fkvm_t *const memory);

#endif
