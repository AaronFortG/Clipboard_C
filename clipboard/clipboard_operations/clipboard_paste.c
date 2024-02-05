#include "clipboard_paste.h"
#include "../../libraries/global_lib.h"

#define CLIPBOARD_PASTE_WRONG_PASTE_TEXT "Wrong number of stepsback when trying to paste!\n"

void CLIPBOARD_PASTE_pasteCopiedText(Clipboard* clipboard, int stepsBack) {
    
    // Check if the number of steps back is inside the boundary (positive number and lower than the number of copied texts).
    if (stepsBack > 0 && stepsBack <= clipboard->copiedText.numCopiedText) {
        int numPastedText = clipboard->copiedText.numCopiedText - stepsBack;
        char* copiedText = clipboard->copiedText.copiedTextArray[numPastedText].text;

        GLOBAL_printMessage("Copying text (%d) %s.\n", numPastedText, copiedText);
        // If there is a selected area, paste the text in that area; if not, just paste in the cursor's position.
        if (clipboard->selectionArea.selectedArea == true) {
            CLIPBOARD_MANAGER_eraseSelectedText(clipboard);
        }
        STRINGS_insertSubstring(&clipboard->text, copiedText, clipboard->cursorPosition);

        // Update current cursor's position.
        clipboard->cursorPosition += strlen(copiedText);
    }
    else {
        GLOBAL_errorMessage(CLIPBOARD_PASTE_WRONG_PASTE_TEXT);
    }
}