#include "clipboard_select.h"
#include "../../libraries/global_lib.h"

#define CLIPBOARD_SELECT_SELECTION_TEXT "Text selected from clipboard:" BOLD_TEXT " '%.*s' " RESET_COLOR ".\n\n"

void CLIPBOARD_SELECT_selectText(Clipboard* clipboard, int startIndex, int endIndex) {
    clipboard->selectionArea.startIndex = startIndex;
    clipboard->selectionArea.endIndex = endIndex;
    clipboard->cursorPosition = endIndex + 1;
    clipboard->selectionArea.selectedArea = true; // Mark area as selected.

    GLOBAL_printMessage(CLIPBOARD_SELECT_SELECTION_TEXT, (endIndex - startIndex + 1), clipboard->text + startIndex);
}