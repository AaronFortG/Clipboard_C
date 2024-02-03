#include "clipboard_move_cursor.h"

void CLIPBOARD_MOVE_CURSOR_moveCursor(Clipboard* clipboard, char offset) {
    // Erase the selected area in case there was one.
    clipboard->selectedArea = false;

    // Move the cursor based on the offset.
    clipboard->cursorPosition += offset;    // If positive offset, sum; if negative, subtract.

    // Check if the cursor is out of the boundaries (lower than zero or greater than the maximum = 50).
    if (clipboard->cursorPosition < 0) {
        clipboard->cursorPosition = 0;
    } else if (clipboard->cursorPosition > CLIPBOARD_MAX_LENGTH) {
        clipboard->cursorPosition = CLIPBOARD_MAX_LENGTH;
    }
}