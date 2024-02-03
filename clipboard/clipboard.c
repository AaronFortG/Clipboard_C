#include "../libraries/global_lib.h"
#include "clipboard.h"
#include "clipboard_manager.h"
#include "clipboard_operations/clipboard_type.h"
#include "clipboard_operations/clipboard_select.h"
#include "clipboard_operations/clipboard_move_cursor.h"
#include "clipboard_operations/clipboard_copy.h"

#define CLIPBOARD_PROCESSING_OPERATIONS_TEXT "Processing %d operations...\n"
#define CLIPBOARD_NO_OPERATIONS_TEXT "There are no operations to process.\n"
#define CLIPBOARD_NEXT_OPERATION_TEXT "Type in the next operation: "
#define CLIPBOARD_EXIT_OPERATION_TEXT "Thanks for using this program!"

void CLIPBOARD_doOperation(Clipboard* clipboard, ClipboardOperation clipboardOperation) {
    clipboard->startIndex = 0;

    switch (clipboardOperation.operation) {
        case CLIPBOARD_TYPE:
            CLIPBOARD_TYPE_addText(clipboard, clipboardOperation.operationText);
            break;
        case CLIPBOARD_SELECT: {
            char startIndex = atoi(strtok(clipboardOperation.operationText, CLIPBOARD_OPERATION_SEPARATOR));
            char endIndex = atoi(strtok(NULL, CLIPBOARD_OPERATION_SEPARATOR));
            CLIPBOARD_SELECT_selectText(clipboard, startIndex, endIndex);
            break;
        }
        case CLIPBOARD_MOVE_CURSOR: {
            char offset = atoi(clipboardOperation.operationText);
            CLIPBOARD_MOVE_CURSOR_moveCursor(clipboard, offset);
            break;
        }
        case CLIPBOARD_COPY:
            CLIPBOARD_COPY_copySelectedArea(clipboard);
            break;
        case CLIPBOARD_PASTE:
            break;
        case CLIPBOARD_EXIT:
            break;
        case CLIPBOARD_INVALID_OPERATION:
            break;
    }
}

void CLIPBOARD_startClipboard(int numOperations, char* operations[]) {
    Clipboard clipboard = CLIPBOARD_MANAGER_newClipboard();

    if (numOperations > 0) {
        GLOBAL_printMessage(CLIPBOARD_PROCESSING_OPERATIONS_TEXT);
    }
    else {
        GLOBAL_printMessage(CLIPBOARD_NO_OPERATIONS_TEXT);
    }

    // Do all the instructions passed as parameters to the program.
    for (int i = 0; i < numOperations; i++) {
        ClipboardOperation currentOperation = CLIPBOARD_MANAGER_parseOperation(operations[i]);
        CLIPBOARD_doOperation(&clipboard, currentOperation);
    }

    ClipboardOperation userOperation;
    do {
        // Get the next operation from the user.
        char* bufferOperation = GLOBAL_readInput(CLIPBOARD_NEXT_OPERATION_TEXT);

        // Do the selected operation.
        userOperation = CLIPBOARD_MANAGER_parseOperation(bufferOperation);
        CLIPBOARD_doOperation(&clipboard, userOperation);

        // Free the temporary buffer.
        GLOBAL_freePointer((void **) &bufferOperation);
    } while (userOperation.operation != CLIPBOARD_EXIT);

    CLIPBOARD_MANAGER_freeClipboard(&clipboard);
    GLOBAL_printMessage(CLIPBOARD_EXIT_OPERATION_TEXT);
}