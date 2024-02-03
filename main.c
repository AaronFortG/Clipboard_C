#include "libraries/global_lib.h"
#include "clipboard/clipboard.h"

#define MINIMUM_ARGUMENTS 1
#define PROGRAM_USAGE_TEXT "Usage of Clipboard program: ./Clipboard [\"Operation 1\", \"Operation 2\"...]\n"

// Transform arguments from the program into valid instructions for the Clipboard.
void parseArguments(int argc, char* argv[], char* arguments[]) {
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
        arguments[i - 1] = STRINGS_copySubstring(argv[i], startIndex, endIndex);
        GLOBAL_printMessage("-%s-\n", arguments[i - 1]);
    }
}

// Free all the memory allocated for the arguments.
void freeArguments(char* arguments[], int numArguments) {
    for (int i = 0; i < numArguments; i++) {
        GLOBAL_freePointer((void **) &arguments[i]);
    }
}

int main(int argc, char* argv[]) {
    /*for (int i = 0; i <= strlen(argv[1]); i++) {
        printf("%c(%d)", argv[1][i], argv[1][i]);
    }
    printf("\n");

    for (int i = 0; i <= strlen(argv[2]); i++) {
        printf("%c(%d)", argv[2][i], argv[2][i]);
    }
    printf("\n");*/

    // Parse all the arguments.
    int numArguments = argc - 1;
    char* arguments[numArguments];

    if (GLOBAL_validParams(argc, MINIMUM_ARGUMENTS)) {
        GLOBAL_printMessage(PROGRAM_USAGE_TEXT);
        exit(EXIT_FAILURE);
    }

    parseArguments(argc, argv, arguments);
    CLIPBOARD_startClipboard(numArguments, arguments);
    freeArguments(arguments, numArguments);

    return EXIT_SUCCESS;
}