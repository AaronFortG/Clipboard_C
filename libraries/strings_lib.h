/**
 * @file strings_lib.h
 * @author Aaron Fort Garcia
 * @date 3rd February 2024.
 * @brief Strings' management module.
 */

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
* @brief Function to create a substring (copy) allocated dynamically with content of the source string.
* @param src String that will be used for the substring.
* @param start Index where the substring should start.
* @param length How many extra characters to copy starting from the start index.
* @return Return NULL if an error occurs, char pointer (substring) otherwise.
**************************************************/
char* STRINGS_copySubstring(const char* src, size_t start, size_t length);

/*************************************************
* @brief Function to insert a substring dynamically before the index of the source string.
* @param dest Address of the final string that will have source prefixed.
* @param src String to set as prefix.
* @param index Position where the insertion should occur.
* @return Return NULL if an error occurs, char pointer (strings prefixed) otherwise.
**************************************************/
char* STRINGS_insertSubstring(char** dest, const char* src, size_t index);

/*************************************************
* @brief Function to separate the first word from the rest of a string based on a delimiter.
* @param inputString The input string to separate.
* @param firstSeparation Pointer to store the first word.
* @param restOfString Pointer to store the rest of the string.
* @param delimiter The delimiter used to separate the words (e.g., " " for space).
* @note If no delimiter is found, the entire string is considered the first word, and the restOfString pointer is set to NULL.
**************************************************/
void STRINGS_separateWords(const char* inputString, char** firstSeparation, char** restOfString, const char* delimiter);

#endif