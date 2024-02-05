# Compiler and flags' variables
CC = gcc
CFLAGS = -g -Wall -Wextra

# Directory structure
LIBRARIES_DIR = ./libraries
CLIPBOARD_DIR = ./clipboard

# Source files and object files
LIBRARIES_SOURCES = $(wildcard $(LIBRARIES_DIR)/*.c)
CLIPBOARD_SOURCES = $(shell find $(CLIPBOARD_DIR) -name '*.c')
MAIN_SOURCES = main.c

# Object files for each target
LIBRARIES_OBJECTS = $(LIBRARIES_SOURCES:.c=.o)
CLIPBOARD_OBJECTS = $(CLIPBOARD_SOURCES:.c=.o)
MAIN_OBJECTS = $(MAIN_SOURCES:.c=.o)

# Pattern rule to compile .c files into .o files
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Targets
all: Clipboard

Clipboard: $(LIBRARIES_OBJECTS) $(CLIPBOARD_OBJECTS) $(MAIN_OBJECTS)
	$(CC) $^ -o $@ $(CFLAGS)

# Clean
.PHONY: clean
clean:
	rm -rf $(LIBRARIES_OBJECTS) $(CLIPBOARD_OBJECTS) $(MAIN_OBJECTS) Clipboard

# Variables for execution
VALGRIND_ARGS = valgrind --leak-check=full --dsymutil=yes --show-leak-kinds=all --track-fds=yes -s --track-origins=yes --show-reachable=yes
PROGRAM_ARGS_1 = ["TYPE We hate pointers", "MOVE_CURSOR -3", "SELECT 3 6", "TYPE love"]
PROGRAM_ARGS_2 = ["TYPE Barcelona is located in Cactus", "SELECT 0 8", "COPY", "SELECT 24 29", "COPY", "PASTE 2", "SELECT 0 8", "PASTE", "MOVE_CURSOR 24", "TYPE !"]

# 'run' and 'check' targets variables fo r executables
.PHONY: run-clipboard, check-clipboard, run-clipboard-args, check-clipboard-args
run-clipboard: Clipboard
	./$<
check-clipboard: Clipboard
	$(VALGRIND_ARGS) ./$<
run-clipboard-args: Clipboard
	./$<  $(PROGRAM_ARGS_2)
check-clipboard-args: Clipboard
	$(VALGRIND_ARGS) ./$< $(PROGRAM_ARGS_2)