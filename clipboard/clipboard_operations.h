#ifndef _CLIPBOARD_OPERATIONS_LIB_H_
#define _CLIPBOARD_OPERATIONS_LIB_H_

#define CLIPBOARD_MAX_LENGTH 50

typedef struct {
    char text[CLIPBOARD_MAX_LENGTH + 1];    // Extra byte for the '\0' (NULL) terminator.
    char startIndex;
    char endIndex;
    char currentIndex;
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

ClipboardOperation CLIPBOARD_parseOperation(char* operationArgument);

#endif