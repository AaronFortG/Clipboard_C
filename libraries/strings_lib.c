/**
 * @file strings_lib.c
 * @author Aaron Fort Garcia
 * @date 3rd February 2024.
 * @brief Strings' management module.
 */

#include "strings_lib.h"

/************************************************
* @brief Function to concatenate a char with an array of char.
* @param temp the array char to concatenate.
* @param buffer the char to concatenate.
* @return return -EXIT_FAILURE if an error occurs, EXIT_SUCCESS otherwise.
* ************************************************/
int STRINGS_concatCharacter(char **temp, char buffer) {
    // Check if the string is empty
    if (*temp == NULL) {
        *temp = (char*) malloc(sizeof(char));

        if (*temp == NULL) {
            return -EXIT_FAILURE;
        }

        (*temp)[0] = '\0'; // Assignar 1 byte per posar el '\0' al final.
    }

    size_t length = strlen(*temp);

    // Ampliar la cadena 2 bytes per posar ['buffer' + '\0']
    *temp = (char*) realloc(*temp, (length + 2) * sizeof(char));

    if (*temp == NULL) {
        return -EXIT_FAILURE;
    }

    (*temp)[length] = buffer;
    (*temp)[length + 1] = '\0';

    return EXIT_SUCCESS;
}

/*************************************************
* @brief Function to create a substring (copy) allocated dynamically with content of the source string.
* @param src String that will be used for the substring.
* @param start Index where the substring should start.
* @param length How many extra characters to copy starting from the start index.
* @return Return NULL if an error occurs, char pointer (substring) otherwise.
**************************************************/
char* STRINGS_copySubstring(const char* src, size_t start, size_t length) {
    if (length <= 0 || start >= strlen(src)) {
        return NULL;
    }

    char *temp = NULL;
    for (size_t i = 0; i < length; i++) {
        if (STRINGS_concatCharacter(&temp, src[start + i]) != EXIT_SUCCESS) {
            return NULL;
        }
    }

    return temp;
}

/*************************************************
* @brief Function to insert a substring dynamically before the index of the source string.
* @param dest Address of the final string that will have source prefixed.
* @param src String to set as prefix.
* @param index Position where the insertion should occur.
* @return Return NULL if an error occurs, char pointer (strings prefixed) otherwise.
**************************************************/
char* STRINGS_insertSubstring(char** dest, const char* src, size_t index) {
    if (src == NULL) {
        return *dest;
    }

    // Calculate the length of the original string
    size_t destLength = (*dest != NULL) ? strlen(*dest) : 0;

    // Validate the insertion index
    if (index > destLength) {
        return NULL;
    }

    // Allocate memory for the new string (including subString)
    size_t newStringLength = strlen(src) + destLength + 1;
    char* newString = (char*)malloc(newStringLength * sizeof(char));   // Include '\0' terminator.
    if (newString == NULL) {
        return NULL; // Handle memory allocation failure
    }
    memset(newString, '\0', newStringLength);

    // Copy the prefix (before the insertion point) from the original string
    strncpy(newString, *dest, index);

    // Concatenate the substring
    strcat(newString, src);

    // Concatenate the remaining part of the original string
    if (*dest != NULL && strlen(*dest) > index) {
        strcat(newString, *dest + index);
    }

    // Update the original string
    GLOBAL_freePointer((void **) dest);
    *dest = newString;

    return *dest;
}

/*************************************************
* @brief Function to separate the first word from the rest of a string based on a delimiter.
* @param inputString The input string to separate.
* @param firstSeparation Pointer to store the first word.
* @param restOfString Pointer to store the rest of the string.
* @param delimiter The delimiter used to separate the words (e.g., " " for space).
* @note If no delimiter is found, the entire string is considered the first word, and the restOfString pointer is set to NULL.
**************************************************/
void STRINGS_separateWords(const char* inputString, char** firstSeparation, char** restOfString, const char* delimiter) {
    // Find the position of the first space character
    char* spacePosition = strstr(inputString, delimiter);

    if (spacePosition != NULL) {
        // Allocate memory for the first word and copy it
        size_t firstWordLength = spacePosition - inputString;
        *firstSeparation = malloc(firstWordLength + 1);
        strncpy(*firstSeparation, inputString, firstWordLength);
        (*firstSeparation)[firstWordLength] = '\0';

        // Set the pointer to the rest of the string
        *restOfString = spacePosition + 1;
    } else {
        // Case where no space was found.
        *firstSeparation = strdup(inputString);
        *restOfString = NULL;
    }
}