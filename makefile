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

# 'run' and 'check' targets variables fo r executables
.PHONY: run-clipboard, check-clipboard
run-clipboard: Clipboard
	./$< ["TYPE We hate pointers", "MOVE_CURSOR -3", "SELECT 3 6", "TYPE love"]

check-clipboard: Clipboard
	valgrind --leak-check=full --dsymutil=yes --show-leak-kinds=all --track-fds=yes -s --track-origins=yes --show-reachable=yes ./$< ["TYPE We hate pointers", "MOVE_CURSOR -3", "SELECT 3 6", "TYPE love"]
