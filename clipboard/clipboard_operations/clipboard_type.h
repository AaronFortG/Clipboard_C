/**
 * @file clipboard_type.h
 * @author Aaron Fort Garcia
 * @date 4th February 2024.
 * @brief Clipboard's TYPE operation module.
 */

#ifndef _CLIPBOARD_TYPE_LIB_H_
#define _CLIPBOARD_TYPE_LIB_H_

#include "../clipboard_manager.h"

/*************************************************
* @brief Function to type a text inside the clipboard.
* @param  clipboard clipboard's variable that will have the text written.
* @param  newText   string that has the new text to be written.
* @return ----.
**************************************************/
void CLIPBOARD_TYPE_addText(Clipboard* clipboard, const char* newText);

#endif