// Guard.
#ifndef LIB_FILE_IO_H_
#define LIN_FILE_IO_H_


// Headers.
#include "stdio.h"


// Aliases.
typedef enum { false, true } bool


// Function Prototypes.
char* read_file(char*, bool*);


// Implementation.
#include "file_io.c"


// End guard.
#endif