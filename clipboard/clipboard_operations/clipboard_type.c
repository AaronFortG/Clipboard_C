#include "clipboard_type.h"
#include "../../libraries/global_lib.h"

#define CLIPBOARD_PASTE_NEW_TEXT "New text typed: "

void CLIPBOARD_TYPE_addText(Clipboard* clipboard, const char* newText) {
    // Check if any area is selected to delete the selected text and insert the new one in the same position.
    if (clipboard->selectionArea.selectedArea == true) {
        CLIPBOARD_MANAGER_eraseSelectedText(clipboard);
    }
    STRINGS_insertSubstring(&(clipboard->text), newText, clipboard->cursorPosition);

    // Update current cursor's position.
    clipboard->cursorPosition += strlen(newText);
    GLOBAL_printMessage(CLIPBOARD_PASTE_NEW_TEXT);
    CLIPBOARD_MANAGER_printTextWithCursor(*clipboard);
}