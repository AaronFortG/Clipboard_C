/**
 * @file clipboard.h
 * @author Aaron Fort Garcia
 * @date 3rd February 2024.
 * @brief Clipboard global module.
 */

#ifndef _CLIPBOARD_LIB_H_
#define _CLIPBOARD_LIB_H_

/*************************************************
* @brief Function to start the execution of the clipboard.
* @param  numOperations number of operations inputted as arguments to the program.
* @param  operations    array of strings with the actual arguments' value of the program.
* @return ----.
**************************************************/
void CLIPBOARD_startClipboard(int numOperations, char* operations[]);

/*************************************************
* @brief Function to finish the clipboard's execution freeing all it's memory.
* @param  clipboard clipboard's variable that will be finished.
* @return ----.
**************************************************/
void CLIPBOARD_finishClipboard();

#endif