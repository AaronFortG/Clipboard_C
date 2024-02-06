#ifndef _GLOBAL_LIB_H_
#define _GLOBAL_LIB_H_

// Llibreries a incloure
#define _GNU_SOURCE

// Color constants for the CLI text.
#include "ANSI-color-codes.h"

// Variadic functions (such as printMessage() simulating printf() function)
#include <stdarg.h>

// File descriptors
#include <fcntl.h>
#include <unistd.h>

// Standard input and output + dynamic memory and strings
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Signals
#include <sys/types.h>
#include <signal.h>

#include <ctype.h>	// isspace()
#include <time.h>   // time

// Directories and files
#include <errno.h>

// Own libraries
#include "files_lib.h"
#include "strings_lib.h"

// Constants i macros
#define printGA(x) write(STDOUT_FILENO, x, strlen(x))

/*************************************************
* @brief Function to read the input from the user.
* @param  message string to show when asking for input to console.
* @return Return the input from the user.
**************************************************/
char* GLOBAL_readInput(const char* message);

/*************************************************
* @brief Variadic function made to print any message using a variable number of parameters (inside ...) using dynamic memory (with vasprintf and a buffer).
* @param message the message to print.
* @param  ... the variable number of parameters.
**************************************************/
void GLOBAL_printMessage(const char* message, ...);

/*************************************************
* @brief Function to check if the number of parameters is correct.
* @param  numArgs the number of arguments.
* @param  numExpected the number of arguments expected.
* @return Return -1 if an error occurs, 0 otherwise.
**************************************************/
int GLOBAL_validParams(int numArgs, int numExpected);

/**
*   @brief Frees a pointer and sets it to NULL
*   @param pointer address of pointer to free (it is also set to NULL).
*/
void GLOBAL_freePointer(void** pointer);

/**
* @brief Print an error message in red color.
* @param event string with the error message
* @param ... arguments to print with the message
*/
void GLOBAL_errorMessage(const char *event, ...);

#endif