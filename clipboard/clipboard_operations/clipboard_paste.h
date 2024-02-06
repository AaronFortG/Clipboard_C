/**
 * @file clipboard_paste.h
 * @author Aaron Fort Garcia
 * @date 4th February 2024.
 * @brief Clipboard's PASTE operation module.
 */

#ifndef _CLIPBOARD_PASTE_LIB_H_
#define _CLIPBOARD_PASTE_LIB_H_

#include "../clipboard_manager.h"

/*************************************************
* @brief Function to paste a copied text from the clipboard.
* @param  clipboard clipboard's variable that has the copied text.
* @param  stepsBack index of the text to be copied (1 equals the last element copied).
* @return ----.
**************************************************/
void CLIPBOARD_PASTE_pasteCopiedText(Clipboard* clipboard, int stepsBack);

#endif