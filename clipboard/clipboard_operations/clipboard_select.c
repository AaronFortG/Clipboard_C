/**
 * @file clipboard_select.c
 * @author Aaron Fort Garcia
 * @date 4th February 2024.
 * @brief Clipboard's SELECT operation module.
 */

#include "clipboard_select.h"
#include "../../libraries/global_lib.h"

// Texts constants regarding clipboard's SELECT operation
#define CLIPBOARD_SELECT_SELECTION_TEXT "Text selected from clipboard: "
#define CLIPBOARD_SELECT_INVALID_INDEX_TEXT "Please input valid indexes (values between 0 and %d).\n\n"

/*************************************************
* @brief Function to select a text from the clipboard.
* @param  clipboard     clipboard's variable that will have the text selected.
* @param  startIndex    index that indicates where the selected text starts (0-based).
* @param  endIndex      index that indicates where the selected text ends (0-based).
* @return ----.
**************************************************/
void CLIPBOARD_SELECT_selectText(Clipboard* clipboard, int startIndex, int endIndex) {
    if (startIndex >= 0 && (size_t) endIndex < strlen(clipboard->text)) {
        clipboard->selectionArea.startIndex = startIndex;
        clipboard->selectionArea.endIndex = endIndex;
        clipboard->cursorPosition = endIndex + 1;
        clipboard->selectionArea.selectedArea = true;   // Mark area as selected.

        GLOBAL_printMessage(CLIPBOARD_SELECT_SELECTION_TEXT);
        CLIPBOARD_MANAGER_printTextWithCursor(*clipboard);
    }
    else {
        GLOBAL_errorMessage(CLIPBOARD_SELECT_INVALID_INDEX_TEXT, strlen(clipboard->text) - 1);
    }
}