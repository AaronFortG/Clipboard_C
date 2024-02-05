#include "clipboard_type.h"
#include "../../libraries/global_lib.h"

void CLIPBOARD_TYPE_addText(Clipboard* clipboard, const char* newText) {
    GLOBAL_printMessage("Before type: %s.\n", clipboard->text);
    GLOBAL_printMessage("Typing in %s.\n", (clipboard->text) + clipboard->cursorPosition);

    STRINGS_insertSubstring(&(clipboard->text), newText, clipboard->cursorPosition);

    GLOBAL_printMessage("Typed newText: %s.\n", clipboard->text);
    clipboard->cursorPosition = strlen(newText) + clipboard->cursorPosition;
}