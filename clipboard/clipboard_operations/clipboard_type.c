/**
 * @file clipboard_type.c
 * @author Aaron Fort Garcia
 * @date 4th February 2024.
 * @brief Clipboard's TYPE operation module.
 */

#include "clipboard_type.h"
#include "../../libraries/global_lib.h"

// Texts constants regarding clipboard's TYPE operation
#define CLIPBOARD_MAX_LENGTH 50
#define CLIPBOARD_PASTE_NEW_TEXT "New text typed: "
#define CLIPBOARD_PASTE_INVALID_INPUT_TEXT "Please insert a valid input text (50 characters maximum).\n\n"

/*************************************************
* @brief Function to type a text inside the clipboard.
* @param  clipboard clipboard's variable that will have the text written.
* @param  newText   string that has the new text to be written.
* @return ----.
**************************************************/
void CLIPBOARD_TYPE_addText(Clipboard* clipboard, const char* newText) {
    // Check if the typed text is valid (less or equal to 50 characters).
    if (strlen(newText) <= CLIPBOARD_MAX_LENGTH) {

        // Check if any area is selected to delete the selected text and insert the new one in the same position.
        if (clipboard->selectionArea.selectedArea == true) {
            CLIPBOARD_MANAGER_eraseSelectedText(clipboard);
        }
        STRINGS_insertSubstring(&(clipboard->text), newText, clipboard->cursorPosition);

        // Update current cursor's position.
        clipboard->cursorPosition += strlen(newText);
        GLOBAL_printMessage(CLIPBOARD_PASTE_NEW_TEXT);
        CLIPBOARD_MANAGER_printTextWithCursor(*clipboard);
    } else {
        GLOBAL_errorMessage(CLIPBOARD_PASTE_INVALID_INPUT_TEXT);
    }
}