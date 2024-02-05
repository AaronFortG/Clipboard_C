#include "clipboard_select.h"

void CLIPBOARD_SELECT_selectText(Clipboard* clipboard, char startIndex, char endIndex) {
    clipboard->selectionArea.startIndex = startIndex;
    clipboard->selectionArea.endIndex = endIndex;
    clipboard->cursorPosition = endIndex + 1;
    clipboard->selectionArea.selectedArea = true; // Mark area as selected.
}