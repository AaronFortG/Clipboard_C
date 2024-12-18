/**
 * @file clipboard.c
 * @author Aaron Fort Garcia
 * @date 3rd February 2024.
 * @brief Clipboard global module.
 */

#include "../libraries/global_lib.h"
#include "clipboard.h"
#include "clipboard_manager.h"
#include "clipboard_operations/clipboard_type.h"
#include "clipboard_operations/clipboard_select.h"
#include "clipboard_operations/clipboard_move_cursor.h"
#include "clipboard_operations/clipboard_copy.h"
#include "clipboard_operations/clipboard_paste.h"

// Texts constants regarding clipboard's operations
#define CLIPBOARD_PROCESSING_OPERATIONS_TEXT "Processing %d operations as input...\n\n"
#define CLIPBOARD_NO_OPERATIONS_TEXT "There are no operations to process.\n"
#define CLIPBOARD_NEXT_OPERATION_TEXT "Type in the next operation: " HWHT
#define CLIPBOARD_EXIT_OPERATION_TEXT "\nThanks for using Clipboard's program!\n"
#define CLIPBOARD_ERROR_OPERATION_TEXT "Please enter a valid operation: TYPE, SELECT, MOVE_CURSOR, COPY, PASTE or EXIT.\n\n"
#define CLIPBOARD_ARGUMENT_OPERATION_TEXT ITALIC_TEXT "Operation typed as argument (input): " COLOR_RESET HWHT "%s" COLOR_RESET "\n"

// Global clipboard variable in case it's needed to free its memory on an interrupt (SIGINT).
Clipboard clipboard;

/*************************************************
* @brief Function to execute a clipboard operation.
* @param  clipboard pointer to clipboard's variable that does the operation.
* @param  clipboardOperation type of operation and its parameters.
* @return ----.
**************************************************/
void CLIPBOARD_doOperation(Clipboard* clipboard, ClipboardOperation clipboardOperation) {
    switch (clipboardOperation.operationType) {
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

            // Get the number of stepsback depending if there was a parameter (PASTE number) or there wasn't (just PASTE).
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

/*************************************************
* @brief Function to show all the parameters from the clipboard.
* @param  clipboard clipboard's variable that will be checked.
* @return ----.
**************************************************/
void CLIPBOARD_showClipboard(Clipboard clipboard) {
    GLOBAL_printMessage("Clipboard text: ");
    for (size_t i = 0; i <= strlen(clipboard.text); i++) {
        if (clipboard.cursorPosition == (int) i) {
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

/*************************************************
* @brief Function to finish the clipboard's execution freeing all it's memory.
* @param  clipboard clipboard's variable that will be finished.
* @return ----.
**************************************************/
void CLIPBOARD_finishClipboard() {
    CLIPBOARD_MANAGER_freeClipboard(&clipboard);
    GLOBAL_printMessage(CLIPBOARD_EXIT_OPERATION_TEXT);
}

/*************************************************
* @brief Function to start the execution of the clipboard.
* @param  numOperations number of operations inputted as arguments to the program.
* @param  operations    array of strings with the actual arguments' value of the program.
* @return ----.
**************************************************/
void CLIPBOARD_startClipboard(int numOperations, char* operations[]) {
    clipboard = CLIPBOARD_MANAGER_newClipboard();

    if (numOperations > 0) {
        GLOBAL_printMessage(CLIPBOARD_PROCESSING_OPERATIONS_TEXT, numOperations);
    }
    else {
        GLOBAL_printMessage(CLIPBOARD_NO_OPERATIONS_TEXT);
    }

    // Do all the instructions passed as parameters to the program.
    for (int i = 0; i < numOperations; i++) {
        GLOBAL_printMessage(CLIPBOARD_ARGUMENT_OPERATION_TEXT, operations[i]);
        ClipboardOperation currentOperation = CLIPBOARD_MANAGER_parseOperation(operations[i]);
        CLIPBOARD_doOperation(&clipboard, currentOperation);
        /* CLIPBOARD_showClipboard(clipboard);  // Show clipboard's information. */
    }

    ClipboardOperation userOperation;
    do {
        // Get the next operation from the user.
        char* bufferOperation = GLOBAL_readInput(CLIPBOARD_NEXT_OPERATION_TEXT);
        GLOBAL_printMessage(COLOR_RESET);

        // Do the selected operation.
        userOperation = CLIPBOARD_MANAGER_parseOperation(bufferOperation);
        CLIPBOARD_doOperation(&clipboard, userOperation);

        // Free the temporary buffer.
        GLOBAL_freePointer((void **) &bufferOperation);
        /* CLIPBOARD_showClipboard(clipboard);  // Show clipboard's information. */
    } while (userOperation.operationType != CLIPBOARD_EXIT);

    CLIPBOARD_finishClipboard();
}
