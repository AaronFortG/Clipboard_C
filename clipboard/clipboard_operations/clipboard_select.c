#include "clipboard_select.h"

void CLIPBOARD_SELECT_selectText(Clipboard* clipboard, char startIndex, char endIndex) {
    clipboard->startIndex = startIndex;
    clipboard->endIndex = endIndex;
    clipboard->cursorPosition = endIndex + 1;
    clipboard->selectedArea = true; // Mark area as selected.
}