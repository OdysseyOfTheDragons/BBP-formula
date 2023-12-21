SHELL:=/bin/bash

# Variables
CC=gcc -I. -Icalculator
FLAGS=-Wall -Wextra -Werror -pedantic -fsanitize=address -g
TFLAGS=-flto -Ofast -march=native
LIB=-lm
LINKER=$(CC) $(FLAGS)
OPTIMIZER=$(CC) $(TFLAGS)

### TODO: MODIFY ON PRODUCTION
COMPILER=$(OPTIMIZER) # LINKER / OPTIMIZER

# Build objects and dependencies
%.o: %.c
	@$(COMPILER) -o $@ -c $<

%.d: %.c
	@$(COMPILER) -MM -MD -o $@ $<

### CALCULATOR

CALC_DIR=calculator
CALC_OUT=$(CALC_DIR)/build/calculator.out

CALC_SRC=$(CALC_DIR)/main.c \
		 $(CALC_DIR)/mathematics/mathematics.c \
		 $(CALC_DIR)/algorithm/algorithm.c
CALC_OBJ=$(CALC_SRC:.c=.o)
CALC_DEP=$(CALC_SRC:.c=.d)

CALC_BIN=calculator
calculator: clean $(CALC_OUT)
	time ./$(CALC_OUT)

$(CALC_OUT): $(CALC_OBJ)
	$(COMPILER) -o $@ $+ $(LIB)

# Clean
.PHONY: clean
clean:
	# CALCULATOR
	@rm -f $(CALC_OUT) $(CALC_OBJ) $(CALC_DEP) *.i *.s

# Archive
.PHONY: tarball
tarball:
	@tar -zcf pi.tar.gz Makefile **/*.md **/*.[ch]

# Includes dependencies
-include $(DEP)
