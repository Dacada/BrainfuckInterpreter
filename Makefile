CC=gcc
CFLAGS=-std=c99 -Wall -g
LDFLAGS=
LDLIBS=

.PHONY: clean veryclean all tests

all: fkvm
tests: test_memory test_program test_stack
	$(MAKE) -C tests
clean:
	$(MAKE) -C tests clean
	$(RM) *.o *~
veryclean: clean
	$(RM) test_memory test_program test_stack fkvm

memory.o: memory.c
test_memory.o: test_memory.c
test_memory: memory.o test_memory.o

program.o: program.c
test_program.o: test_program.c
test_program: program.o test_program.o

stack.o: stack.c
test_stack.o: test_stack.c
test_stack: stack.o test_stack.o

fkvm.o: fkvm.c
fkvm: program.o memory.o stack.o fkvm.o
