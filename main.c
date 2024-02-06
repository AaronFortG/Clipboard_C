/**
 * @file main.c
 * @author Aaron Fort Garcia
 * @date 3rd February 2024.
 * @brief Main program's file.
 */

#include "libraries/global_lib.h"
#include "clipboard/clipboard.h"

#define MINIMUM_ARGUMENTS 1
#define PROGRAM_USAGE_TEXT "Usage of Clipboard program: ./Clipboard [\"OperationType 1\", \"OperationType 2\"...]\n"

int numArguments = 0;
char** argumentValue;

/*************************************************
* @brief Transform arguments from the program into valid instructions for the Clipboard.
* @param argc Number of command-line arguments.
* @param argv Array of command-line arguments.
* @param arguments Pointer to store the parsed arguments.
* @note The memory for the parsed arguments is dynamically allocated and needs to be freed by the caller.
**************************************************/
void parseArguments(int argc, char* argv[], char*** arguments) {
    // Allocate all the necessary memory.
    *arguments = (char **) malloc (sizeof(char *) * argc);

    // Skip the first argument (./programName) with i = 1.
    for (int i = 1; i < argc; i++) {
        size_t startIndex = 0, endIndex = 0;

        // Skip the '[' character from the first argument.
        if (i == 1) {
            startIndex = 1;
        }

        // No need to skip the ']' character from the last argument since it's the only that does not have a comma at the end (already skipped).
        endIndex = strlen(argv[i]) - 1;
        if (i == 1) {
            endIndex--; // Take into account the '[' on the first parameter.
        }

        // Copy only the interesting content from the parameters.
        (*arguments)[i - 1] = STRINGS_copySubstring(argv[i], startIndex, endIndex);
    }
}

/*************************************************
* @brief Free all the memory allocated for the arguments.
* @param arguments Pointer to the array of arguments.
* @param numArgs Number of arguments in the array.
**************************************************/
void freeArguments(char** arguments, int numArgs) {
    for (int i = 0; i < numArgs; i++) {
        GLOBAL_freePointer((void **) &arguments[i]);
    }
    GLOBAL_freePointer((void **) &arguments);
}

/*************************************************
* @brief Signal handler function to handle SIGINT.
* @param signum Signal number (unused).
* @note This function cleans up resources and exits the program gracefully.
**************************************************/
void signalHandler(int signum __attribute__((unused))) {
    signal(SIGINT, SIG_DFL);
    CLIPBOARD_finishClipboard();
    freeArguments(argumentValue, numArguments);
    exit(EXIT_SUCCESS);
}

/*************************************************
* @brief Main function to start the program.
* @param argc Number of command-line arguments.
* @param argv Array of command-line arguments.
* @return Returns EXIT_SUCCESS if the program exits successfully, EXIT_FAILURE otherwise.
**************************************************/
int main(int argc, char* argv[]) {
    signal(SIGINT, signalHandler);

    // Parse all the arguments.
    numArguments = argc - 1;

    if (GLOBAL_validParams(argc, MINIMUM_ARGUMENTS)) {
        GLOBAL_printMessage(PROGRAM_USAGE_TEXT);
        exit(EXIT_FAILURE);
    }

    parseArguments(argc, argv, &argumentValue);
    CLIPBOARD_startClipboard(numArguments, argumentValue);
    freeArguments(argumentValue, numArguments);

    return EXIT_SUCCESS;
}