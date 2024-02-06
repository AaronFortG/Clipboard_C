#include "global_lib.h"

#define TIME_FORMAT     "%Y-%m-%d %H:%M:%S"

#define ARGUMENTS_ERROR "ERROR: Incorrect number of arguments (%d)! Expected at least %d arguments.\n"

/*************************************************
* @Purpose: Function to read the input from the user.
* @Params:  ---.
* @Return: Return the input from the user.
* ************************************************/
char* GLOBAL_readInput(const char* message) {
    // Show the prompt before reading the input (if set).
    if (message != NULL) {
        GLOBAL_printMessage("%s", message);
    }

    return FILES_readFileDelimiter(STDIN_FILENO, '\n');
}


/*************************************************
* @brief Variadic function made to print any message using a variable number of parameters (inside ...) using dynamic memory (with vasprintf and a buffer).
* @param message the message to print.
* @param  ... the variable number of parameters.
**************************************************/
void GLOBAL_printMessage(const char* message, ...) {
    // Initialize the list of arguments and set the list to start before the first string parameter.
    va_list args;
    va_start(args, message);

    // vasprintf allocates a string large enough to hold the output including the terminating null byte ('\0').
    char* buffer = NULL;
    int length = vasprintf(&buffer, message, args);

    // Check if vasprintf worked fine (returns -1 if some error occurs).
    if (length >= 0) {
        printGA(buffer);
    }

    // Even if vasprintf fails or succeeds, the content of strp is undefined when freed or when an error ocurred.
    if (buffer != NULL) {
        GLOBAL_freePointer((void **) &buffer);
    }

    va_end(args);   // Clean the list of arguments and deinitialize it.
}

/*************************************************
* @brief Function to check if the number of parameters is correct.
* @param  numArgs the number of arguments.
* @param  numExpected the number of arguments expected.
* @return Return -1 if an error occurs, 0 otherwise.
**************************************************/
int GLOBAL_validParams(int numArgs, int numExpected) {
    if (numArgs < numExpected) {
        GLOBAL_errorMessage(ARGUMENTS_ERROR, numArgs - 1, numExpected - 1);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/**
*   @purpose: Frees a pointer and sets it to NULL
*   @param pointer pointer's address used to be freed
*/
void GLOBAL_freePointer(void** pointer) {
    if (*pointer != NULL) {
        free(*pointer);
        *pointer = NULL;
    }
}

/**
* @brief Print an error message in red color.
* @param event string with the error message
* @param ... arguments to print with the message
*/
void GLOBAL_errorMessage(const char *event, ...) {
    // Initialize the list of arguments and set the list to start before the first string parameter.
    va_list args;
    va_start(args, event);

    // vasprintf allocates a string large enough to hold the output including the terminating null byte ('\0').
    char* buffer = NULL;
    int length = vasprintf(&buffer, event, args);

    // Check if vasprintf worked fine (returns -1 if some error occurs).
    if (length < 0) {
        GLOBAL_freePointer((void **) &buffer);
        va_end(args);
        return;
    }

    GLOBAL_printMessage("%s%s%s", RED, buffer, COLOR_RESET);

    // Even if vasprintf fails or succeeds, the content of strp is undefined when freed or when an error ocurred.
    GLOBAL_freePointer((void **) &buffer);
    va_end(args);   // Clean the list of arguments and deinitialize it.
}

