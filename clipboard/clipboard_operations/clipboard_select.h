/**
 * @file clipboard_select.c
 * @author Aaron Fort Garcia
 * @date 4th February 2024.
 * @brief Clipboard's SELECT operation module.
 */

#ifndef _CLIPBOARD_SELECT_LIB_H_
#define _CLIPBOARD_SELECT_LIB_H_

#include "../clipboard_manager.h"

/*************************************************
* @brief Function to select a text from the clipboard.
* @param  clipboard     clipboard's variable that will have the text selected.
* @param  startIndex    index that indicates where the selected text starts (0-based).
* @param  endIndex      index that indicates where the selected text ends (0-based).
* @return ----.
**************************************************/
void CLIPBOARD_SELECT_selectText(Clipboard* clipboard, int startIndex, int endIndex);

#endif