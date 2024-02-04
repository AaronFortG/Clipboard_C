#include "clipboard_paste.h"
#include "../../libraries/global_lib.h"

void CLIPBOARD_PASTE_eraseSelectedText(Clipboard* clipboard) {
    size_t originalLength = strlen(clipboard->text);
    char shiftOffset = originalLength - clipboard->endIndex;

    // Remove the string by the start and end index (substring).
    char* startString = clipboard->text + clipboard->startIndex;
    char* endString = clipboard->text + clipboard->endIndex;
    memmove(startString, endString, shiftOffset);

    // Erase the duplicated text.
    char selectionOffset = CLIPBOARD_MANAGER_getSelectedOffset(clipboard);
    char newLength = originalLength - selectionOffset;
    char duplicatedOffset = originalLength - newLength;
    memset(startString + shiftOffset, 0, duplicatedOffset);
}

void CLIPBOARD_PASTE_pasteCopiedText(Clipboard* clipboard, int stepsBack) {
    // Check if the number of steps back is inside the boundary (positive number and lower than the number of copied texts).
    if (stepsBack > 0 && stepsBack < clipboard->copiedText.numCopiedText) {
        //int numPastedText = clipboard->copiedText.numCopiedText - 1 - stepsBack;

        if (clipboard->selectedArea == true) {
            CLIPBOARD_PASTE_eraseSelectedText(clipboard);
        }
    }
}