SHELL:=/bin/bash

# Variables
CC=gcc -I. -fopenmp
FLAGS=-Wall -Wextra -pedantic -fsanitize=thread -g
TFLAGS=-Ofast -march=native# -fsanitize=undefined -fsanitize=thread -fsanitize=address
LIB=-lm -lgmp -lmpfr
LINKER=$(CC) $(FLAGS)
OPTIMIZER=$(CC) $(TFLAGS)

### TODO: MODIFY ON PRODUCTION
# LINKER / OPTIMIZER
COMPILER=$(OPTIMIZER)

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

SERV_SRC=$(SERV_DIR)/main.c \
		 $(SERV_DIR)/communications.c \
		 database/database.c
SERV_OBJ=$(SERV_SRC:.c=.o)
SERV_DEP=$(SERV_SRC:.c=.d)

SERV_BIN=server
server: clean $(SERV_OUT)
	./$(SERV_OUT)

$(SERV_OUT): $(SERV_OBJ)
	@$(COMPILER) -o $@ $+ $(LIB)

### CLIENT

CLIENT_DIR=client
CLIENT_OUT=build/client.out

CLIENT_SRC=$(CLIENT_DIR)/main.c \
		   $(SERV_DIR)/communications.c \
		   $(CALC_DIR)/interface.c \
		   $(CALC_DIR)/algorithm.c \
		   mathematics/mathematics.c \
		   converter/converter.c
CLIENT_OBJ=$(CLIENT_SRC:.c=.o)
CLIENT_DEP=$(CLIENT_SRC:.c=.d)

CLIENT_BIN=client
client: clean $(CLIENT_OUT)
	./$(CLIENT_OUT)

$(CLIENT_OUT): $(CLIENT_OBJ)
	@$(COMPILER) -o $@ $+ $(LIB)

### TEST

TEST_DIR=test
TEST_OUT=build/test.out

TEST_SRC=$(TEST_DIR)/main.c \
		 calculator/interface.c \
		 calculator/algorithm.c \
		 mathematics/mathematics.c \
		 converter/converter.c
TEST_OBJ=$(TEST_SRC:.c=.o)
TEST_DEP=$(TEST_SRC:.c=.d)

TEST_BIN=test
test: clean $(TEST_OUT)
	time ./$(TEST_OUT)

$(TEST_OUT): $(TEST_OBJ)
	$(COMPILER) -o $@ $+ $(LIB)

# Clean
.PHONY: clean
clean:
	@rm -f $(CALC_OUT) $(CALC_OBJ) $(CALC_DEP)
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
	@make -C ./docs/latex

# Includes dependencies
-include $(DEP)
