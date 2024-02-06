/**
 * @file clipboard_manager.h
 * @author Aaron Fort Garcia
 * @date 3rd February 2024.
 * @brief Clipboard's manager module.
 */

#ifndef _CLIPBOARD_OPERATIONS_LIB_H_
#define _CLIPBOARD_OPERATIONS_LIB_H_

#include <stdbool.h>

#define CLIPBOARD_MAX_LENGTH 50
#define CLIPBOARD_OPERATION_SEPARATOR " "
#define CLIPBOARD_ERROR_TEXT "There was an error during the operationType! Closing program...\n"

typedef struct {
    char* text;
} CopiedText;

// Data type to store the different copied texts on the Clipboard.
typedef struct {
    int numCopiedText;              // Number of copied texts into the clipboard.
    CopiedText* copiedTextArray;    // Dynamic array of strings (texts copied).
} CopiedTextArray;

// Data type of the Clipboard's selected area.
typedef struct {
    bool selectedArea;      // Boolean (flag) that checks if the clipboard has an area selected.
    int startIndex;         // Index that indicates where the selected area starts.
    int endIndex;           // Index that indicates where the selected area finishes.
} ClipboardSelectionArea;

// Data type of the actual Clipboard.
typedef struct {
    char* text;                             // Text typed into the clipboard.
    int cursorPosition;                     // Current cursor's position inside the text.
    ClipboardSelectionArea selectionArea;   // Indexes from the clipboard's selected area.
    CopiedTextArray copiedText;             // Array of copied texts.
} Clipboard;

// Operations that can handle the Clipboard.
typedef enum {
    CLIPBOARD_TYPE,
    CLIPBOARD_SELECT,
    CLIPBOARD_MOVE_CURSOR,
    CLIPBOARD_COPY,
    CLIPBOARD_PASTE,
    CLIPBOARD_EXIT,
    CLIPBOARD_INVALID_OPERATION
} OperationType;

// Data type that holds the operation to execute and its arguments.
typedef struct {
    OperationType operationType;    // Type of operation to be executed in the clipboard.
    char* operationText;            // Text that follows the operation inputted (its parameters).
} ClipboardOperation;

/*************************************************
* @brief Function to initialize a new Clipboard variable.
* @return ----.
**************************************************/
Clipboard CLIPBOARD_MANAGER_newClipboard();

/*************************************************
* @brief Function to free all the memory from a Clipboard.
* @param  clipboard clipboard's variable that will be freed.
* @return ----.
**************************************************/
void CLIPBOARD_MANAGER_freeClipboard(Clipboard* clipboard);

/*************************************************
* @brief Function to get the clipboard's selected area offset from.
* @param  clipboard clipboard's variable that has the selected area stored.
* @return ----.
**************************************************/
int CLIPBOARD_MANAGER_getSelectedOffset(Clipboard clipboard);

/*************************************************
* @brief Function to parse a string and convert it to the corresponding enum OperationType.
* @param  clipboard clipboard's variable that will have the text written.
* @param  newText   string that has the new text to be written.
* @return ----.
**************************************************/
ClipboardOperation CLIPBOARD_MANAGER_parseOperation(char* operationArgument);

/*************************************************
* @brief Function to erase the text inside the selected area from the clipboard.
* @param  clipboard clipboard's variable that has the whole text stored.
* @return ----.
**************************************************/
void CLIPBOARD_MANAGER_eraseSelectedText(Clipboard* clipboard);

/*************************************************
* @brief Function to show the current clipboard's text with the cursor's position in it.
* @param  clipboard clipboard's variable that has the text and cursor stored.
* @return ----.
**************************************************/
void CLIPBOARD_MANAGER_printTextWithCursor(Clipboard clipboard);

#endif