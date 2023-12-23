SHELL:=/bin/bash

# Variables
CC=gcc -I. -Icalculator
FLAGS=-Wall -Wextra -pedantic -fsanitize=address -g
TFLAGS=-Ofast -march=native
LIB=-lm -lgmp -lmpfr
LINKER=$(CC) $(FLAGS)
OPTIMIZER=$(CC) $(TFLAGS)

### TODO: MODIFY ON PRODUCTION
# LINKER / OPTIMIZER
COMPILER=$(LINKER)

# Build objects and dependencies
%.o: %.c
	@$(COMPILER) -o $@ -c $<

%.d: %.c
	@$(COMPILER) -MM -MD -o $@ $<

### CALCULATOR

CALC_DIR=calculator
CALC_OUT=build/calculator.out

CALC_SRC=$(CALC_DIR)/main.c \
		 $(CALC_DIR)/algorithm.c \
		 mathematics/mathematics.c \
		 converter/converter.c
CALC_OBJ=$(CALC_SRC:.c=.o)
CALC_DEP=$(CALC_SRC:.c=.d)

CALC_BIN=calculator
calculator: clean $(CALC_OUT)
	time ./$(CALC_OUT)

$(CALC_OUT): $(CALC_OBJ)
	@$(COMPILER) -o $@ $+ $(LIB)

### SERVER

SERV_DIR=server
SERV_OUT=build/server.out

SERV_SRC=$(SERV_DIR)/main.c
SERV_OBJ=$(SERV_SRC:.c=.o)
SERV_DEP=$(SERV_SRC:.c=.d)

SERV_BIN=server
server: clean $(SERV_OUT)
	./$(SERV_OUT)

$(SERV_OUT): $(SERV_OBJ)
	@$(COMPILER) -o $@ $+ $(LIB)

# Clean
.PHONY: clean
clean:
	# CALCULATOR
	@rm -f $(CALC_OUT) $(CALC_OBJ) $(CALC_DEP)
	# SERVER
	@rm -f $(SERV_OUT) $(SERV_OBJ) $(SERV_DEP)

# Archive
.PHONY: tarball
tarball: clean format
	@tar -zcf pi.tar.gz Makefile **/*.[ch] README.md LICENSE Contributors.md

# Format to Linux format
format:
	@indent -linux **/*.[ch]

# Generate documentation
.PHONY: docs
docs:
	@doxygen
	# @make -C ./docs/latex

# Includes dependencies
-include $(DEP)
