#include "clipboard_manager.h"
#include "../libraries/global_lib.h"

#define CLIPBOARD_TYPE_OPERATION "CLIPBOARD_TYPE"
#define CLIPBOARD_SELECT_OPERATION "CLIPBOARD_SELECT"
#define CLIPBOARD_MOVE_CURSOR_OPERATION "MOVE_CURSOR"
#define CLIPBOARD_COPY_OPERATION "CLIPBOARD_COPY"
#define CLIPBOARD_PASTE_OPERATION "CLIPBOARD_PASTE"
#define CLIPBOARD_EXIT_OPERATION "CLIPBOARD_EXIT"

Clipboard CLIPBOARD_MANAGER_newClipboard() {

    // Initialize all the values from the data type.
    Clipboard clipboard = {
            .text = "",
            .startIndex = 0,
            .endIndex = 0,
            .selectedArea = false,
            .cursorPosition = 0,
            .copiedText.numCopiedText = 0,
            .copiedText.copiedTextArray = NULL
    };
    return clipboard;
}

void CLIPBOARD_MANAGER_freeClipboard(Clipboard* clipboard) {

    // Free all the memory used in the clipboard.
    for (int i = 0; i < clipboard->copiedText.numCopiedText; i++) {
        CopiedText* copiedText = &(clipboard->copiedText.copiedTextArray[i]);
        GLOBAL_freePointer((void **) &copiedText->text);
    }
    GLOBAL_freePointer((void **) &clipboard->copiedText.copiedTextArray);
}

// Function to parse a string and convert it to the corresponding enum Operation.
ClipboardOperation CLIPBOARD_MANAGER_parseOperation(char* operationArgument) {
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