# Variables
CC=gcc
FLAGS=-Wall -Wextra -Werror -pedantic -fsanitize=address -g -I. -pg
TFLAGS=-I. -flto -Ofast -march=native
LINKER=$(CC) $(FLAGS)
OPTIMIZER=$(CC) $(TFLAGS)

OUT=_server_

## Sources
SRC=main.c
OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.d)

## Snippets
BIN=server
LIB=-lm

.PHONY: all
all: $(BIN)

# GCC build the program to test
server: clean $(OUT)

$(OUT): $(OBJ)
	$(LINKER) -o $@ $+ $(LIB)

# Build objects and dependencies
%.o: %.c
	@$(OPTIMIZER) -o $@ -c $<

%.d: %.c
	@$(OPTIMIZER) -MM -MD -o $@ $<

# Additional
valgrind: $(OUT)
	valgrind ./$(OUT)

# Clean
.PHONY: clean
clean:
	rm -f $(BIN) $(OUT) $(OBJ) $(DEP) *.i *.s

# Archive
.PHONY: tarball
tarball:
	-tar -zcf server.tar.gz Makefile **/*.[ch]

# Includes dependencies
-include $(DEP)
