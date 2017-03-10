// header guard.
#ifndef LIB_FILE_IO_H_
#define LIB_FILE_IO_H_


// Headers.
#include <stdio.h>


// Function Prototypes.
FILE* open_file(char*, char*);
int read_until(FILE*, char*, size_t, char);
void close_file(FILE*);


// End header guard.
#endif