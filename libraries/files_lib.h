#ifndef _FILES_LIB_
#define _FILES_LIB_

// Text files
#define FILE_READ "read"
#define FILE_WRITE "write"
#define FILE_READ_WRITE "read_write"
#define INVALID_FILE_DESCRIPTOR (-1)

/*********************************************** *
* @brief Function to open a txt file.
* @param fileName  the name of the file to open.
* @return Return the valor of the variable fd.
* ************************************************/
int FILES_openTextFile(const char* fileName, const char* mode);

/*********************************************** *
* @brief Function to read a text file until a certain character.
* @param fd the file descriptor.
* @param delimiter the delimiter to stop reading.
* @return Return the string read from the file.
* ************************************************/
char* FILES_readFileDelimiter(int fd, char delimiter);

#endif