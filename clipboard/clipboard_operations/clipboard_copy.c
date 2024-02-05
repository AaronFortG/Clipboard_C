#include "clipboard_copy.h"
#include "../../libraries/global_lib.h"

#define CLIPBOARD_COPY_NO_SELECT_TEXT "There is no area selected when trying to copy!\n"

void CLIPBOARD_COPY_copySelectedArea(Clipboard* clipboard) {

    // Copy the selected area from the clipboard (if there is any).
    if (clipboard->selectionArea.selectedArea == true) {
        clipboard->copiedText.numCopiedText++;
        clipboard->copiedText.copiedTextArray = realloc(clipboard->copiedText.copiedTextArray, sizeof(CopiedText) * clipboard->copiedText.numCopiedText);

        // Check if realloc was successful.
        if (clipboard->copiedText.copiedTextArray == NULL) {
            GLOBAL_printMessage(CLIPBOARD_ERROR_TEXT);
            exit(EXIT_FAILURE);
        }

        // Save the copied text from the clipboard.
        int copiedTextIndex = clipboard->copiedText.numCopiedText - 1;
        char* copiedText = STRINGS_copySubstring(clipboard->text, clipboard->selectionArea.startIndex, CLIPBOARD_MANAGER_getSelectedOffset(clipboard));
        clipboard->copiedText.copiedTextArray[copiedTextIndex].text = copiedText;
    }
    else {
        GLOBAL_errorMessage(CLIPBOARD_COPY_NO_SELECT_TEXT);
    }
}