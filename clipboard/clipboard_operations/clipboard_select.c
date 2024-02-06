#include "clipboard_select.h"
#include "../../libraries/global_lib.h"

#define CLIPBOARD_SELECT_SELECTION_TEXT "Text selected from clipboard: "
#define CLIPBOARD_SELECT_INVALID_INDEX_TEXT "Please input valid indexes (values between 0 and %d).\n\n"

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