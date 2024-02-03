#include "clipboard_type.h"
#include "../libraries/global_lib.h"

void CLIPBOARD_TYPE_addText(Clipboard* clipboard, const char* text) {
    strncpy(clipboard->text, text, CLIPBOARD_MAX_LENGTH);
    clipboard->currentIndex = strlen(clipboard->text);
}