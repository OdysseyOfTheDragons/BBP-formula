# Variables
CC=gcc
FLAGS=-Wall -Wextra -Werror -pedantic -fsanitize=address -g -I. -pg
TFLAGS=-I. -flto -s -Ofast -march=native
LINKER=$(CC) $(FLAGS)
OPTIMIZER=$(CC) $(TFLAGS)

OUT=_pi_
TOUT=_test_

## Sources
SRC=main.c \
	mathematics/mathematics.c \
	algorithm/algorithm.c
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.d)

## Snippets
BIN=pi test
LIB=-lm

.PHONY: all
all: $(BIN)

# GCC build the program to test
pi: clean $(OUT)

test: clean $(TOUT)

$(OUT): $(OBJ)
	$(LINKER) -o $@ $+ $(LIB)

$(TOUT): $(OBJ)
	$(OPTIMIZER) -o $@ $+ $(LIB)

# Build objects and dependencies
%.o: %.c
	@$(OPTIMIZER) -pg -o $@ -c $<

%.d: %.c
	@$(OPTIMIZER) -MM -MD -o $@ $<

# Additional
valgrind: $(OUT)
	valgrind ./$(OUT)

gprof: $(OUT)
	./$(OUT)
	gprof -b $(OUT)

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
