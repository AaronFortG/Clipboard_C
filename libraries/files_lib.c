// Libraries to include
#include "global_lib.h"

#include "files_lib.h"

/*********************************************** *
* @brief Function to open a txt file.
* @param fileName  the name of the file to open.
* @return Return the valor of the variable fd.
* ************************************************/
int FILES_openTextFile(const char* fileName, const char* mode) {
    int fileDescriptor = INVALID_FILE_DESCRIPTOR;

    if (strcmp(mode, FILE_READ) == 0) {
        // Read = Only if the file exists.
        fileDescriptor = open(fileName, O_RDONLY);
    }
    else if (strcmp(mode, FILE_WRITE) == 0) {
        // Write = Create the file and write on it.
        fileDescriptor = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, 0744);
    }
    else {
        // Read write = Append the information, and create file if it does not exist.
        fileDescriptor = open(fileName, O_RDWR | O_APPEND | O_CREAT, 0744);
    }

    if (fileDescriptor < 0) {
        char error[] = "Error reading the file";
        perror(error);
    }

    return fileDescriptor;
}

/*********************************************** *
* @brief Function to read a text file until a certain character.
* @param fd the file descriptor.
* @param delimiter the delimiter to stop reading.
* @return Return the string read from the file.
* ************************************************/
char* FILES_readFileDelimiter(int fd, char delimiter) {
    ssize_t bytesRead = 0;
    char* content = NULL;
    char letter = 0;

    // Continue reading until delimiter is found.
    do {
        // Read byte per byte until delimiter is found.
        bytesRead = read(fd, &letter, sizeof(char));

        // Check if reading has failed.
        if (bytesRead < 0) {
            perror("read");
            return NULL;
        }

        if (bytesRead == 0) {
            return NULL;
        }

        // If delimiter is found, return the string.
        if (letter == delimiter) {
            return content;
        }

        if (STRINGS_concatCharacter(&content, letter) != EXIT_SUCCESS) {
            GLOBAL_freePointer((void **) &content);
            return NULL;
        }
    } while (bytesRead > 0);

    // Finished reading the file
    return content;
}