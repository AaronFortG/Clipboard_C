/**
 * @file clipboard_paste.c
 * @author Aaron Fort Garcia
 * @date 4th February 2024.
 * @brief Clipboard's PASTE operation module.
 */

#include "clipboard_paste.h"
#include "../../libraries/global_lib.h"

// Texts constants regarding clipboard's PASTE operation
#define CLIPBOARD_PASTE_WRONG_PASTE_TEXT "Wrong number of stepsback when trying to paste!\n"
#define CLIPBOARD_PASTE_COPIED_TEXT "Pasting text '" BHWHT "%s" COLOR_RESET "' from clipboard.\n"
#define CLIPBOARD_PASTE_NEW_TEXT "New text pasted: "
#define CLIPBOARD_PASTE_PREVIOUS_TEXT "Previous text: '" BHWHT "%.*s" REDB "%.*s" COLOR_RESET BHWHT "%.*s" COLOR_RESET "'\n"

/*************************************************
* @brief Function to paste a copied text from the clipboard.
* @param  clipboard clipboard's variable that has the copied text.
* @param  stepsBack index of the text to be copied (1 equals the last element copied).
* @return ----.
**************************************************/
void CLIPBOARD_PASTE_pasteCopiedText(Clipboard* clipboard, int stepsBack) {
    // Check if the number of steps back is inside the boundary (positive number and lower than the number of copied texts).
    if (stepsBack > 0 && stepsBack <= clipboard->copiedText.numCopiedText) {
        int numPastedText = clipboard->copiedText.numCopiedText - stepsBack;
        char* copiedText = clipboard->copiedText.copiedTextArray[numPastedText].text;

        // Show whole pasted text.
        GLOBAL_printMessage(CLIPBOARD_PASTE_PREVIOUS_TEXT, clipboard->selectionArea.startIndex, clipboard->text,
                            CLIPBOARD_MANAGER_getSelectedOffset(*clipboard), clipboard->text + clipboard->selectionArea.startIndex,
                            strlen(clipboard->text) - clipboard->selectionArea.endIndex, clipboard->text + clipboard->cursorPosition);
        GLOBAL_printMessage(CLIPBOARD_PASTE_COPIED_TEXT, copiedText);

        // If there is a selected area, paste the text in that area; if not, just paste in the cursor's position.
        if (clipboard->selectionArea.selectedArea == true) {
            CLIPBOARD_MANAGER_eraseSelectedText(clipboard);
        }
        STRINGS_insertSubstring(&clipboard->text, copiedText, clipboard->cursorPosition);

        // Update current cursor's position and show new pasted text.
        clipboard->cursorPosition += strlen(copiedText);
        clipboard->selectionArea.selectedArea = false;
        GLOBAL_printMessage(CLIPBOARD_PASTE_NEW_TEXT);
        CLIPBOARD_MANAGER_printTextWithCursor(*clipboard);
    }
    else {
        GLOBAL_errorMessage(CLIPBOARD_PASTE_WRONG_PASTE_TEXT);
    }
}