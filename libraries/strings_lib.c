#include "strings_lib.h"

/*********************************************** *
* @Purpose: Function to concatenate a char with an array of char.
* @Params:  in/out: temp -> the array char to concatenate.
			in: buffer -> the char to concatenate.
* @Return: Return -1 if an error occurs, 0 otherwise.
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

/*********************************************** *
* @Purpose: Function to prefix (set in front) a char with an array of char.
* @Params:  in/out: temp -> the array char to set as prefix.
			in: buffer -> the char to set as prefix.
* @Return: Return -1 if an error occurs, 0 otherwise.
* ************************************************/
int STRINGS_prefixCharacter(char **temp, char buffer) {
    // Check if the string is empty
    if (*temp == NULL) {
        GLOBAL_printMessage("String empty!\n");
        *temp = (char*) malloc(sizeof(char));

        if (*temp == NULL) {
            return -EXIT_FAILURE;
        }

        (*temp)[0] = '\0'; // Assignar 1 byte per posar el '\0' al final.
    }

    ssize_t length = strlen(*temp);

    // Ampliar la cadena 2 bytes per posar ['buffer' + '\0']
    *temp = (char*) realloc(*temp, (length + 2) * sizeof(char));

    if (*temp == NULL) {
        return -EXIT_FAILURE;
    }

    // Shift all the characters to the right.
    //for (ssize_t i = length; i >= 0; i--) {
    //    (*temp)[i + 1] = (*temp)[i];
    //}
    memmove(*temp + 1, *temp, length);

    // Place the prefix and the last '\0' character.
    (*temp)[0] = buffer;
    (*temp)[length + 1] = '\0';

    return EXIT_SUCCESS;
}

/*************************************************
* @purpose: Concatenate the source string to the destination dynamically.
* @params:  in/out: dest -> address of the final string that will have source concatenated.
			in: src -> string to concatenate.
* @return: Return NULL if an error occurs, char pointer (strings concatenated) otherwise.
* ************************************************/
char* STRINGS_concatString(char** dest, const char* src) {
    if (src == NULL) {
        return *dest;
    }

    // Concat string character per character.
    for (size_t i = 0; i < strlen(src); i++) {
        if (STRINGS_concatCharacter(dest, src[i]) != EXIT_SUCCESS) {
            return NULL;
        }
    }

    return *dest;
}

/*************************************************
* @purpose: Prefix (set in front) the source string to the destination dynamically.
* @params:  in/out: dest -> address of the final string that will have source prefixed.
			in: src -> string to set as prefix.
* @return: Return NULL if an error occurs, char pointer (strings prefixed) otherwise.
* ************************************************/
char* STRINGS_prefixString(char** dest, const char* src) {
    if (src == NULL) {
        return *dest;
    }

    // Prefix string character per character.
    for (size_t i = strlen(src); i > 0; i--) {
        if (STRINGS_prefixCharacter(dest, src[i - 1]) != EXIT_SUCCESS) {
            return NULL;
        }
    }

    GLOBAL_printMessage("Hey: %s.\n", *dest);

    return *dest;
}

/*************************************************
* @purpose: Concatenate the source string to the destination dynamically.
* @params:  in/out: dest -> address of the final string that will have source concatenated.
			in: src -> string to concatenate.
* @return: Return NULL if an error occurs, char pointer (strings concatenated) otherwise.
* ************************************************/
char* STRINGS_concatAllStrings(char** dest, int numStrings, ...) {
    va_list args;
    va_start(args, numStrings);

    // Concatenate all the strings
    for (int i = 0; i < numStrings; i++) {
        char* string = va_arg(args, char *);
        if (STRINGS_concatString(dest, string) == NULL) {
            va_end(args);
            return NULL;
        }
    }

    va_end(args);   // Clean the list of arguments and deinitialize it.
    return *dest;
}

/*************************************************
* @purpose: Create a substring (copy) allocated dynamically with content of the source string.
* @params:  in/out: src -> string that will be used for the substring.
			in: start -> index where the substring should start.
            in: length -> how many extra characters to copy starting from the start index.
* @return: Return NULL if an error occurs, char pointer (substring) otherwise.
* ************************************************/
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
* @purpose: Create a substring (copy) allocated dynamically with content of the source string.
* @params:  in/out: src -> string that will be used for the substring.
			in: start -> index where the substring should start.
            in: length -> how many extra characters to copy starting from the start index.
* @return: Return NULL if an error occurs, char pointer (substring) otherwise.
* ************************************************/
char* STRINGS_removeSubstring(const char* src, size_t start, size_t length) {
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
* @purpose: Insert a substring dynamically before the index of the source string.
* @params:  in/out: dest -> address of the final string that will have source prefixed.
            in: src -> string to set as prefix.
            in: index -> position where the insertion should occur.
* @return: Return NULL if an error occurs, char pointer (strings prefixed) otherwise.
* ************************************************/
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
    GLOBAL_printMessage("-%ld.%ld-\n", strlen(src), destLength);
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
* @purpose: Replace the initial string for the appended string dynamically starting from the index and clearing all the extra dest's string characters.
* @params:  in/out: dest -> address of string that will have the replace string concatenated starting from index.
			in/out: replace -> string to append on the dest[index] characters.
            in: index -> starting point where the appended string will be concatenated, replacing the initialStrings
* @return: Return NULL if an error occurs, char pointer (dest + appended string) otherwise.
* ************************************************/
char* STRINGS_replaceString(char** dest, char* replace, size_t index) {
    char* temp = NULL;

    // Copy the first "index" (0 .. index - 1) characters from dest string to split it from index.
    for (size_t i = 0; i < index; i++) {
        if (STRINGS_concatCharacter(&temp, (*dest)[i]) != EXIT_SUCCESS) {
            return NULL;
        }
    }

    // Clear dest's memory since it will no longer be used (replace string has the other half).
    GLOBAL_freePointer((void **) dest);

    // Append replace string (last bytes - n + 1 .. length) to temp's string (first bytes of dest string).
    STRINGS_concatString(&temp, replace);
    *dest = temp;   // When freeing dest, temp will be freed as well (it's actually a temporary stack memory only).

    return (*dest);
}

/*************************************************
* Replace a certain character from string (if newChar == 0, delete it from the string).
* @params:  in/out: string -> address of string that will have the replace string concatenated starting from index.
			in: oldChar -> current character in string to be replaced.
            in: newChar -> new character that will replace oldChar from string.
* @return: Return -1 if an error occurs, integer (number of replaced characters) otehrwise.
* ************************************************/
int STRINGS_replaceCharacter(char** string, char oldChar, char newChar) {
    int timesReplaced = 0;
    size_t length = strlen(*string);

    for (size_t i = 0; i < length; i++) {
        if ((*string)[i] == oldChar) {
            timesReplaced++;

            // Case where we have to shift all the characters one position to the left.
            if (newChar == 0) {
                int start = i + 1;

                // Split the original string in 2 strings starting from "index" position, skip the oldChar and append both strings.
                char* temp = STRINGS_copySubstring(*string, start, length - start); // Substring with the last N characters that started with oldChar.
                if (temp == NULL) {
                    return -EXIT_FAILURE;
                }

                STRINGS_replaceString(string, temp, i); // Appending the substring starting in the oldChar position to skip it.
                if (string == NULL) {
                    return -EXIT_FAILURE;
                }

                length = strlen(*string);   // Update strings length integer.
                GLOBAL_freePointer((void **) &temp);
            }
            else {
                // Change the old character for the new one.
                (*string)[i] = newChar;
            }
        }
    }

    return timesReplaced;
}

TokenArray* STRINGS_parse(char* input, char* delim) {
    TokenArray* result = (TokenArray*) malloc(sizeof(TokenArray));
    if (result == NULL) {
        return NULL;
    }

    result->tokens = NULL;
    result->count = 0;

    char* token = strtok(input, delim);
    int i = 0;

    // Mentre hi hagi tokens, els anem afegint a l'array
    while (token != NULL) {
        // Fem realloc per a l'array de tokens
        result->tokens = (char**)realloc(result->tokens, (i + 1) * sizeof(char*));
        if (result->tokens == NULL) {
            perror("Error en l'assignació de memòria");
            exit(EXIT_FAILURE);
        }

        // Reservem memòria per al token
        result->tokens[i] = (char*)malloc((strlen(token) + 1) * sizeof(char));
        if (result->tokens[i] == NULL) {
            perror("Error en l'assignació de memòria");
            exit(EXIT_FAILURE);
        }

        // Copiem el token a l'array
        strcpy(result->tokens[i], token);
        i++;

        // Següent token
        token = strtok(NULL, delim);
    }

    result->count = i;
    return result;
}

/*************************************************
* @purpose: Concatenate source string to the end of dest string.
* @param dest destination static string that will have the source string concatenated.
* @param source dynamic or static string that will be concatenated to dest string.
* @param index dest's index where the source strings will be appended.
* @warning This functions only works if dest string has enough capacity to append source string.
* ************************************************/
void STRINGS_concatStringIndex(char dest[], char* source, int index) {
    size_t i = 0;

    if (source != NULL) {
        while (i < strlen(source)) {
            dest[index] = source[i];
            index++;
            i++;
        }
    }
}

void STRINGS_freeParse(TokenArray** array) {
    for (int i = 0; i < (*array)->count; i++) {
        GLOBAL_freePointer((void **) &(*array)->tokens[i]);    // Alliberem la memòria de cada string
    }

    GLOBAL_freePointer((void **) &(*array)->tokens);
    GLOBAL_freePointer((void **) &*array);
}

char* STRINGS_reverseString(char* string) {
    int start = 0;
    int end = strlen(string) - 1;

    while (start < end) {
        char temp = string[start];
        string[start] = string[end];
        string[end] = temp;
        start++;
        end--;
    }

    return string;
}

// Custom itoa but using an unsigned short.
char* STRINGS_unsignedShortToAscii(unsigned short value) {
    char* numberStr = NULL;

    // Append each digit individually starting from the left.
    unsigned short tmpValue = value;
    do {
        char digit = (tmpValue % 10) + '0';
        STRINGS_concatCharacter(&numberStr, digit);
        tmpValue /= 10; // Skip to the next digit.
    } while (tmpValue != 0);

    // Reverse the string.
    return STRINGS_reverseString(numberStr);
}

// Custom itoa but using a long long.
char* STRINGS_longLongToAscii(long long value) {
    char* numberStr = NULL;

    // Append each digit individually starting from the left.
    unsigned long long tmpValue = value;
    do {
        char digit = (tmpValue % 10) + '0';
        STRINGS_concatCharacter(&numberStr, digit);
        tmpValue /= 10; // Skip to the next digit.
    } while (tmpValue != 0);

    // Reverse the string.
    return STRINGS_reverseString(numberStr);
}

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