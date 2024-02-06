#include "clipboard_move_cursor.h"
#include "../../libraries/global_lib.h"

#define CLIPBOARD_MOVE_CURSOR_POSITION_TEXT "Cursor is now placed in" BHWHT " position %d " COLOR_RESET "-> "

void CLIPBOARD_MOVE_CURSOR_moveCursor(Clipboard* clipboard, int offset) {
    // Erase the selected area in case there was one.
    clipboard->selectionArea.selectedArea = false;

    // Move the cursor based on the offset.
    clipboard->cursorPosition += offset;    // If positive offset, sum; if negative, subtract.

    // Check if the cursor is out of the boundaries (lower than zero or greater than the maximum = 50).
    if (clipboard->cursorPosition < 0) {
        clipboard->cursorPosition = 0;
    } else if (clipboard->cursorPosition > (int)strlen(clipboard->text)) {
        clipboard->cursorPosition = strlen(clipboard->text);
    }
    GLOBAL_printMessage(CLIPBOARD_MOVE_CURSOR_POSITION_TEXT, clipboard->cursorPosition);
    CLIPBOARD_MANAGER_printTextWithCursor(*clipboard);
}