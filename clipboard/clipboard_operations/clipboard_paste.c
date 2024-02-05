#include "clipboard_paste.h"
#include "../../libraries/global_lib.h"

void CLIPBOARD_PASTE_pasteCopiedText(Clipboard* clipboard, int stepsBack) {
    GLOBAL_printMessage("Pasting %d stepsback!\n");

    // Check if the number of steps back is inside the boundary (positive number and lower than the number of copied texts).
    if (stepsBack > 0 && stepsBack <= clipboard->copiedText.numCopiedText) {
        if (clipboard->selectionArea.selectedArea == true) {
            int numPastedText = clipboard->copiedText.numCopiedText - stepsBack;
            char* copiedText = clipboard->copiedText.copiedTextArray[numPastedText].text;

            GLOBAL_printMessage("Copying text (%d) %s.\n", numPastedText, copiedText);
            CLIPBOARD_MANAGER_eraseSelectedText(clipboard);
            STRINGS_insertSubstring(&clipboard->text, copiedText, clipboard->selectionArea.startIndex);
        }
    }
}