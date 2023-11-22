# Variables
CC=gcc
FLAGS=-Wall -Wextra -Werror -pedantic -fsanitize=address -g -I.
TFLAGS=-I. -O3 -Os -s
LINKER=$(CC) $(FLAGS)
OPTIMIZER=$(CC) $(TFLAGS)

## Sources
SRC=main.c \
	mathematics/mathematics.c \
	cli/cli.c \
	algorithm/algorithm.c
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.d)

## Snippets
BIN=pi test
LIB=-lm

.PHONY: all
all: $(BIN)

# GCC build the program to test
pi: clean _pi_

test: clean _test_

_pi_: $(OBJ)
	$(LINKER) -o $@ $+ $(LIB)

_test_: $(OBJ)
	$(OPTIMIZER) -o $@ $+ $(LIB)

# Build objects and dependencies
%.o: %.c
	$(OPTIMIZER) -o $@ -c $<

%.d: %.c
	$(OPTIMIZER) -MM -MD -o $@ $<

# Clean
.PHONY: clean
clean:
	rm -f $(BIN) _pi_ _test_ $(OBJ) $(DEP) *.i *.s

# Archive
.PHONY: tarball
tarball:
	-tar -zcf pi.tar.gz Makefile **/*.[ch]

# Includes dependencies
-include $(DEP)
