#include "../libraries/global_lib.h"
#include "clipboard.h"
#include "clipboard_manager.h"
#include "clipboard_operations/clipboard_type.h"
#include "clipboard_operations/clipboard_select.h"
#include "clipboard_operations/clipboard_move_cursor.h"
#include "clipboard_operations/clipboard_copy.h"
#include "clipboard_operations/clipboard_paste.h"

#define CLIPBOARD_PROCESSING_OPERATIONS_TEXT "Processing %d operations...\n"
#define CLIPBOARD_NO_OPERATIONS_TEXT "There are no operations to process.\n"
#define CLIPBOARD_NEXT_OPERATION_TEXT "Type in the next operation: "
#define CLIPBOARD_EXIT_OPERATION_TEXT "Thanks for using this program!\n"
#define CLIPBOARD_ERROR_OPERATION_TEXT "This operation is not valid!\n"

void CLIPBOARD_doOperation(Clipboard* clipboard, ClipboardOperation clipboardOperation) {
    switch (clipboardOperation.operation) {
        case CLIPBOARD_TYPE:
            CLIPBOARD_TYPE_addText(clipboard, clipboardOperation.operationText);
            break;
        case CLIPBOARD_SELECT: {
            int startIndex = atoi(strtok(clipboardOperation.operationText, CLIPBOARD_OPERATION_SEPARATOR));
            int endIndex = atoi(strtok(NULL, CLIPBOARD_OPERATION_SEPARATOR));
            CLIPBOARD_SELECT_selectText(clipboard, startIndex, endIndex);
            break;
        }
        case CLIPBOARD_MOVE_CURSOR: {
            int offset = atoi(clipboardOperation.operationText);
            CLIPBOARD_MOVE_CURSOR_moveCursor(clipboard, offset);
            break;
        }
        case CLIPBOARD_COPY:
            CLIPBOARD_COPY_copySelectedArea(clipboard);
            break;
        case CLIPBOARD_PASTE: {
            int stepsBack;
            if (clipboardOperation.operationText == NULL) {
                stepsBack = 1;
            }
            else {
                stepsBack = atoi(clipboardOperation.operationText);
            }
            CLIPBOARD_PASTE_pasteCopiedText(clipboard, stepsBack);
            break;
        }
        case CLIPBOARD_EXIT:
            break;
        case CLIPBOARD_INVALID_OPERATION:
            GLOBAL_errorMessage(CLIPBOARD_ERROR_OPERATION_TEXT);
            break;
    }
}

void CLIPBOARD_showClipboard(Clipboard clipboard) {
    GLOBAL_printMessage("Clipboard text: ");
    for (size_t i = 0; i <= strlen(clipboard.text); i++) {
        if (clipboard.cursorPosition == (char) i) {
            GLOBAL_printMessage("|");
        }
        // Just in case the loop is needed for the '|' char.
        if (i < strlen(clipboard.text)) {
            GLOBAL_printMessage("%c", clipboard.text[i]);
        }
    }

    GLOBAL_printMessage("\nSelected area: ");
    clipboard.selectionArea.selectedArea == true ? GLOBAL_printMessage("true") : GLOBAL_printMessage("false");
    GLOBAL_printMessage(" -> Start index: %d - End index: %d.\n", clipboard.selectionArea.startIndex, clipboard.selectionArea.endIndex);
    GLOBAL_printMessage("Current cursor index: %d.\n", clipboard.cursorPosition);
    GLOBAL_printMessage("Copied areas: %d.\n", clipboard.copiedText.numCopiedText);
    for (int i = 0; i < clipboard.copiedText.numCopiedText; i++) {
        GLOBAL_printMessage("\t- %s.\n", clipboard.copiedText.copiedTextArray[i]);
    }

    if (clipboard.copiedText.numCopiedText > 0) {
        GLOBAL_printMessage("\n");
    }
    else {
        GLOBAL_printMessage("\n\n");
    }
}

void CLIPBOARD_startClipboard(int numOperations, char* operations[]) {
    Clipboard clipboard = CLIPBOARD_MANAGER_newClipboard();

    if (numOperations > 0) {
        GLOBAL_printMessage(CLIPBOARD_PROCESSING_OPERATIONS_TEXT, numOperations);
    }
    else {
        GLOBAL_printMessage(CLIPBOARD_NO_OPERATIONS_TEXT);
    }

    // Do all the instructions passed as parameters to the program.
    for (int i = 0; i < numOperations; i++) {
        ClipboardOperation currentOperation = CLIPBOARD_MANAGER_parseOperation(operations[i]);
        CLIPBOARD_doOperation(&clipboard, currentOperation);
        CLIPBOARD_showClipboard(clipboard);
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
        CLIPBOARD_showClipboard(clipboard);    // TODO: Erase
    } while (userOperation.operation != CLIPBOARD_EXIT);

    CLIPBOARD_MANAGER_freeClipboard(&clipboard);
    GLOBAL_printMessage(CLIPBOARD_EXIT_OPERATION_TEXT);
}
