#include "clipboard_type.h"
#include "../../libraries/global_lib.h"

void CLIPBOARD_TYPE_addText(Clipboard* clipboard, const char* newText) {
    GLOBAL_printMessage("Before type: %s.\n", clipboard->text);
    GLOBAL_printMessage("Typing in %s.\n", (clipboard->text) + clipboard->cursorPosition);

    // Check if any area is selected to delete the selected text and insert the new one in the same position.
    if (clipboard->selectionArea.selectedArea == true) {
        CLIPBOARD_MANAGER_eraseSelectedText(clipboard);
        clipboard->cursorPosition = clipboard->selectionArea.startIndex;    // Update the cursor to be at the beginning of the selected text.
    }
    STRINGS_insertSubstring(&(clipboard->text), newText, clipboard->cursorPosition);

    GLOBAL_printMessage("Typed newText: %s.\n", clipboard->text);
    clipboard->cursorPosition = strlen(newText) + clipboard->cursorPosition;
}