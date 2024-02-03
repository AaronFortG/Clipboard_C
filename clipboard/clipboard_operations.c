#include "clipboard_operations.h"
#include "../libraries/global_lib.h"

#define CLIPBOARD_TYPE_OPERATION "CLIPBOARD_TYPE"
#define CLIPBOARD_SELECT_OPERATION "CLIPBOARD_SELECT"
#define CLIPBOARD_MOVE_CURSOR_OPERATION "MOVE_CURSOR"
#define CLIPBOARD_COPY_OPERATION "CLIPBOARD_COPY"
#define CLIPBOARD_PASTE_OPERATION "CLIPBOARD_PASTE"
#define CLIPBOARD_EXIT_OPERATION "CLIPBOARD_EXIT"

// Function to parse a string and convert it to the corresponding enum Operation.
ClipboardOperation CLIPBOARD_parseOperation(char* operationArgument) {
    const char* operation = strtok(operationArgument, CLIPBOARD_OPERATION_SEPARATOR);
    ClipboardOperation clipboardOperation = { .operation = CLIPBOARD_INVALID_OPERATION, .operationText = strdup(strtok(NULL, CLIPBOARD_OPERATION_SEPARATOR)) };

    if (strcmp(operation, CLIPBOARD_TYPE_OPERATION) == 0) {
        clipboardOperation.operation = CLIPBOARD_TYPE;
    } else if (strcmp(operation, CLIPBOARD_SELECT_OPERATION) == 0) {
        clipboardOperation.operation = CLIPBOARD_SELECT;
    } else if (strcmp(operation, CLIPBOARD_MOVE_CURSOR_OPERATION) == 0) {
        clipboardOperation.operation = CLIPBOARD_MOVE_CURSOR;
    } else if (strcmp(operation, CLIPBOARD_COPY_OPERATION) == 0) {
        clipboardOperation.operation = CLIPBOARD_COPY;
    } else if (strcmp(operation, CLIPBOARD_PASTE_OPERATION) == 0) {
        clipboardOperation.operation = CLIPBOARD_PASTE;
    } else if (strcmp(operation, CLIPBOARD_EXIT_OPERATION) == 0) {
        clipboardOperation.operation = CLIPBOARD_EXIT;
    } else {
        clipboardOperation.operation = CLIPBOARD_INVALID_OPERATION;
    }

    return clipboardOperation;
}