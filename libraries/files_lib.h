#ifndef _FILES_LIB_
#define _FILES_LIB_

/*********************************************** *
* @brief Function to read a text file until a certain character.
* @param fd the file descriptor.
* @param delimiter the delimiter to stop reading.
* @return Return the string read from the file.
* ************************************************/
char* FILES_readFileDelimiter(int fd, char delimiter);

#endif