#ifndef _STRINGS_LIB_H_
#define _STRINGS_LIB_H_

#include "global_lib.h"

/*************************************************
* @brief Function to concatenate a char with an array of char.
* @param  in/out: buffer -> the array char to concatenate.
* @param  in: letter -> the char to concatenate.
* @return Return -1 if an error occurs, 0 otherwise.
**************************************************/
int STRINGS_concatCharacter(char **buffer, char letter);

/*************************************************
* @purpose: Create a substring (copy) allocated dynamically with content of the source string.
* @params:  in/out: src -> string that will be used for the substring.
			in: start -> index where the substring should start.
            in: length -> how many extra characters to copy starting from the start index.
* @return: Return NULL if an error occurs, char pointer (substring) otherwise.
* ************************************************/
char* STRINGS_copySubstring(const char* src, size_t start, size_t length);

/*************************************************
* @purpose: Insert a substring dynamically before the index of the source string.
* @params:  in/out: dest -> address of the final string that will have source prefixed.
            in: src -> string to set as prefix.
            in: index -> position where the insertion should occur.
* @return: Return NULL if an error occurs, char pointer (strings prefixed) otherwise.
* ************************************************/
char* STRINGS_insertSubstring(char** dest, const char* src, size_t index);

void STRINGS_separateWords(const char* inputString, char** firstSeparation, char** restOfString, const char* delimiter);

#endif