// header guard.
#ifndef LIB_FILE_IO_H_
#define LIN_FILE_IO_H_


// Headers.
#include "stdio.h"


// Aliases.
#ifndef BOOL_ALIAS_
#define BOOL_ALIAS_
typedef enum { false, true } bool;
#endif


// Function Prototypes.
char* read_file(char*, bool*);


// Implementation.
#include "file_io.c"


// End guard.
#endif