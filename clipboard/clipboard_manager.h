#ifndef _CLIPBOARD_OPERATIONS_LIB_H_
#define _CLIPBOARD_OPERATIONS_LIB_H_

#include <stdbool.h>

#define CLIPBOARD_MAX_LENGTH 50
#define CLIPBOARD_OPERATION_SEPARATOR " "
#define CLIPBOARD_ERROR_TEXT "There was an error during the operation! Closing program...\n"

typedef struct {
    char* text;
} CopiedText;

typedef struct {
    int numCopiedText;
    CopiedText* copiedTextArray;
} CopiedTextArray;

typedef struct {
    bool selectedArea;
    char startIndex;
    char endIndex;
} ClipboardSelectionArea;

typedef struct {
    char* text;
    char cursorPosition;
    ClipboardSelectionArea selectionArea;
    CopiedTextArray copiedText;
} Clipboard;

typedef enum {
    CLIPBOARD_TYPE,
    CLIPBOARD_SELECT,
    CLIPBOARD_MOVE_CURSOR,
    CLIPBOARD_COPY,
    CLIPBOARD_PASTE,
    CLIPBOARD_EXIT,
    CLIPBOARD_INVALID_OPERATION
} Operation;

typedef struct {
    Operation operation;
    char* operationText;
} ClipboardOperation;

Clipboard CLIPBOARD_MANAGER_newClipboard();
void CLIPBOARD_MANAGER_freeClipboard(Clipboard* clipboard);
int CLIPBOARD_MANAGER_getSelectedOffset(Clipboard* clipboard);
ClipboardOperation CLIPBOARD_MANAGER_parseOperation(char* operationArgument);

#endif