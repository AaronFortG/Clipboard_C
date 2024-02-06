/**
 * @file clipboard_manager.c
 * @author Aaron Fort Garcia
 * @date 3rd February 2024.
 * @brief Clipboard's manager module.
 */

#include "clipboard_manager.h"
#include "../libraries/global_lib.h"

// Texts constants regarding clipboard's operations
#define CLIPBOARD_TYPE_OPERATION "TYPE"
#define CLIPBOARD_SELECT_OPERATION "SELECT"
#define CLIPBOARD_MOVE_CURSOR_OPERATION "MOVE_CURSOR"
#define CLIPBOARD_COPY_OPERATION "COPY"
#define CLIPBOARD_PASTE_OPERATION "PASTE"
#define CLIPBOARD_EXIT_OPERATION "EXIT"

/*************************************************
* @brief Function to initialize a new Clipboard variable.
* @return ----.
**************************************************/
Clipboard CLIPBOARD_MANAGER_newClipboard() {

    // Initialize all the values from the data type.
    Clipboard clipboard = {
            .text = NULL,
            .selectionArea.startIndex = 0,
            .selectionArea.endIndex = 0,
            .selectionArea.selectedArea = false,
            .cursorPosition = 0,
            .copiedText.numCopiedText = 0,
            .copiedText.copiedTextArray = NULL
    };
    return clipboard;
}

/*************************************************
* @brief Function to free all the memory from a Clipboard.
* @param  clipboard clipboard's variable that will be freed.
* @return ----.
**************************************************/
void CLIPBOARD_MANAGER_freeClipboard(Clipboard* clipboard) {

    // Free all the memory used in the clipboard.
    for (int i = 0; i < clipboard->copiedText.numCopiedText; i++) {
        CopiedText* copiedText = &(clipboard->copiedText.copiedTextArray[i]);
        GLOBAL_freePointer((void **) &copiedText->text);
    }
    GLOBAL_freePointer((void **) &clipboard->copiedText.copiedTextArray);
    GLOBAL_freePointer((void **) &clipboard->text);
}

/*************************************************
* @brief Function to get the clipboard's selected area offset from.
* @param  clipboard clipboard's variable that has the selected area stored.
* @return ----.
**************************************************/
int CLIPBOARD_MANAGER_getSelectedOffset(Clipboard clipboard) {
    return clipboard.selectionArea.endIndex - clipboard.selectionArea.startIndex + 1;
}

/*************************************************
* @brief Function to show the current clipboard's text with the cursor's position in it.
* @param  clipboard clipboard's variable that has the text and cursor stored.
* @return ----.
**************************************************/
void CLIPBOARD_MANAGER_printTextWithCursor(Clipboard clipboard) {
    GLOBAL_printMessage("'%s", BHWHT);

    // Loop until i <= strlen(text) in case it is needed because of the cursor's position.
    for (size_t i = 0; i <= strlen(clipboard.text); i++) {

        // Check if the index corresponds to the cursor's position.
        if (clipboard.cursorPosition == (int) i) {

            // Check if the cursor is at the end to add a white space.
            if (i == strlen(clipboard.text)) {
                GLOBAL_printMessage("%s %s", COLOR_RESET BHRED UNDERLINE_TEXT, COLOR_RESET);
            }
            else {
                GLOBAL_printMessage("%s%c%s", COLOR_RESET BHRED UNDERLINE_TEXT, clipboard.text[i], COLOR_RESET);
            }
            continue;   // Skip to the next character so that it's not written twice.
        }

        // Write the corresponding text's character.
        if (i < strlen(clipboard.text)) {

            // Highlight the selected area.
            if (i >= (size_t) clipboard.selectionArea.startIndex && i <= (size_t) clipboard.selectionArea.endIndex && clipboard.selectionArea.selectedArea) {
                GLOBAL_printMessage("%s%c", COLOR_RESET CYNB BHWHT, clipboard.text[i]);
            }
            else {
                GLOBAL_printMessage("%s%c", COLOR_RESET BHWHT, clipboard.text[i]);
            }
        }
    }

    GLOBAL_printMessage("%s'\n\n", COLOR_RESET);
}

/*************************************************
* @brief Function to erase the text inside the selected area from the clipboard.
* @param  clipboard clipboard's variable that has the whole text stored.
* @return ----.
**************************************************/
void CLIPBOARD_MANAGER_eraseSelectedText(Clipboard* clipboard) {
    size_t originalLength = strlen(clipboard->text);
    size_t shiftOffset = originalLength - clipboard->selectionArea.endIndex;

    // Remove the string between the start and end index (substring).
    size_t startIndex = strlen(clipboard->text) > (size_t)clipboard->selectionArea.startIndex ? (size_t)clipboard->selectionArea.startIndex : strlen(clipboard->text);
    size_t endIndex = strlen(clipboard->text) > (size_t)clipboard->selectionArea.endIndex ? (size_t)clipboard->selectionArea.endIndex + 1 : strlen(clipboard->text);
    char* startString = clipboard->text + startIndex;
    char* endString = clipboard->text + endIndex;
    memmove(startString, endString, shiftOffset);

    // Erase the duplicated text (set it to '\0' chars).
    int selectionOffset = CLIPBOARD_MANAGER_getSelectedOffset(*clipboard);
    size_t newLength = originalLength - selectionOffset;
    size_t duplicatedOffset = originalLength - newLength;
    memset(startString + shiftOffset, 0, duplicatedOffset);
    clipboard->cursorPosition = clipboard->selectionArea.startIndex;    // Update the cursor to be at the beginning of the selected text.
}

/*************************************************
* @brief Function to parse a string and convert it to the corresponding enum OperationType.
* @param  clipboard clipboard's variable that will have the text written.
* @param  newText   string that has the new text to be written.
* @return ----.
**************************************************/
ClipboardOperation CLIPBOARD_MANAGER_parseOperation(char* operationArgument) {
    ClipboardOperation clipboardOperation = { .operationType = CLIPBOARD_INVALID_OPERATION };
    char* operationBuffer;
    STRINGS_separateWords(operationArgument, &operationBuffer, &clipboardOperation.operationText, CLIPBOARD_OPERATION_SEPARATOR);

    // Check what operationBuffer was typed in.
    if (strcmp(operationBuffer, CLIPBOARD_TYPE_OPERATION) == 0) {
        clipboardOperation.operationType = CLIPBOARD_TYPE;
    } else if (strcmp(operationBuffer, CLIPBOARD_SELECT_OPERATION) == 0) {
        clipboardOperation.operationType = CLIPBOARD_SELECT;
    } else if (strcmp(operationBuffer, CLIPBOARD_MOVE_CURSOR_OPERATION) == 0) {
        clipboardOperation.operationType = CLIPBOARD_MOVE_CURSOR;
    } else if (strcmp(operationBuffer, CLIPBOARD_COPY_OPERATION) == 0) {
        clipboardOperation.operationType = CLIPBOARD_COPY;
    } else if (strcmp(operationBuffer, CLIPBOARD_PASTE_OPERATION) == 0) {
        clipboardOperation.operationType = CLIPBOARD_PASTE;
    } else if (strcmp(operationBuffer, CLIPBOARD_EXIT_OPERATION) == 0) {
        clipboardOperation.operationType = CLIPBOARD_EXIT;
    } else {
        clipboardOperation.operationType = CLIPBOARD_INVALID_OPERATION;
    }

    // Free the temp's operationBuffer malloc.
    GLOBAL_freePointer((void **) &operationBuffer);

    return clipboardOperation;
}