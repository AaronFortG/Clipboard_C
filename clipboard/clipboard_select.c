#include "clipboard_select.h"

void CLIPBOARD_SELECT_selectText(Clipboard* clipboard, char startIndex, char endIndex) {
    clipboard->startIndex = startIndex;
    clipboard->endIndex = endIndex;
    clipboard->currentIndex = endIndex - startIndex  + 1;
}