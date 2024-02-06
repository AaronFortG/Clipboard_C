/**
 * @file clipboard_move_cursor.h
 * @author Aaron Fort Garcia
 * @date 4th February 2024.
 * @brief Clipboard's MOVE_CURSOR operation module.
 */

#ifndef _CLIPBOARD_MOVE_CURSOR_LIB_H_
#define _CLIPBOARD_MOVE_CURSOR_LIB_H_

#include "../clipboard_manager.h"

/*************************************************
* @brief Function to move the current position of the clipboard's cursor.
* @param  clipboard clipboard's variable that will have its cursor moved.
* @return ----.
**************************************************/
void CLIPBOARD_MOVE_CURSOR_moveCursor(Clipboard* clipboard, int offset);

#endif