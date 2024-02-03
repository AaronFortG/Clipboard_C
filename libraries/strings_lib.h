#ifndef _STRINGS_LIB_H_
#define _STRINGS_LIB_H_

#include "global_lib.h"

typedef struct {
    char** tokens;
    int count;
} TokenArray;

/*************************************************
* @brief Function to concatenate a char with an array of char.
* @param  in/out: buffer -> the array char to concatenate.
* @param  in: letter -> the char to concatenate.
* @return Return -1 if an error occurs, 0 otherwise.
**************************************************/
int STRINGS_concatCharacter(char **buffer, char letter);
int STRINGS_prefixCharacter(char **temp, char buffer);

/*************************************************
* @brief Concatenate the source string to the destination dynamically.
* @param  in/out: dest -> address of the final string that will have source concatenated.
* @param	in: src -> string to concatenate.
* @return Return NULL if an error occurs, char pointer (strings concatenated) otherwise.
**************************************************/
char* STRINGS_concatString(char** dest, const char* src);
char* STRINGS_prefixString(char** dest, const char* src);

/*************************************************
* @purpose: Concatenate the source string to the destination dynamically.
* @params:  in/out: dest -> address of the final string that will have source concatenated.
			in: src -> string to concatenate.
* @return: Return NULL if an error occurs, char pointer (strings concatenated) otherwise.
* ************************************************/
char* STRINGS_concatAllStrings(char** dest, int numStrings, ...);

/*************************************************
* @brief Replace a certain character from string (if newChar == 0, delete it from the string).
* @param in/out: string -> address of string that will have the replace string concatenated starting from index.
* @param in: oldChar -> current character in string to be replaced.
* @param in: newChar -> new character that will replace oldChar from string.
* @return Return -1 if an error occurs, integer (number of replaced characters) otehrwise.
* @warning An error may occur when dealing with dynamic memory (malloc and realloc).
**************************************************/
int STRINGS_replaceCharacter(char** string, char oldChar, char newChar);

/*************************************************
* @brief Replace the initial string for the appended string dynamically starting from the index and clearing all the extra dest's string characters.
* @param  in/out: dest -> address of string that will have the replace string concatenated starting from index.
* @param	in/out: replace -> string to append on the dest[index] characters.
* @param    in: index -> starting point where the appended string will be concatenated, replacing the initialStrings
* @return Return NULL if an error occurs, char pointer (dest + appended string) otherwise.
**************************************************/
char* STRINGS_replaceString(char** dest, char* replace, size_t index);

/*************************************************
* @purpose: Create a substring (copy) allocated dynamically with content of the source string.
* @params:  in/out: src -> string that will be used for the substring.
			in: start -> index where the substring should start.
            in: length -> how many extra characters to copy starting from the start index.
* @return: Return NULL if an error occurs, char pointer (substring) otherwise.
* ************************************************/
char* STRINGS_copySubstring(const char* src, size_t start, size_t length);

/*************************************************
* @purpose: Concatenate source string to the end of dest string.
* @param dest destination static string that will have the source string concatenated.
* @param source dynamic or static string that will be concatenated to dest string.
* @param index dest's index where the source strings will be appended.
* @warning This functions only works if dest string has enough capacity to append source string.
* ************************************************/
void STRINGS_concatStringIndex(char dest[], char* source, int index);

TokenArray* STRINGS_parse(char* input, char* delim);
void STRINGS_freeParse(TokenArray** array);

char* STRINGS_unsignedShortToAscii(unsigned short value);
char* STRINGS_longLongToAscii(long long value);

#endif