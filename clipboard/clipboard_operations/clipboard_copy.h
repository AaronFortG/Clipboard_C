/**
 * @file clipboard_copy.h
 * @author Aaron Fort Garcia
 * @date 4th February 2024.
 * @brief Clipboard's COPY operation module.
 */

#ifndef _CLIPBOARD_COPY_LIB_H_
#define _CLIPBOARD_COPY_LIB_H_

#include "../clipboard_manager.h"

/*************************************************
* @brief Function to copy the selected area to the clipboard.
* @param  clipboard clipboard's variable that will save the copied text.
* @return ----.
**************************************************/
void CLIPBOARD_COPY_copySelectedArea(Clipboard* clipboard);

#endif
