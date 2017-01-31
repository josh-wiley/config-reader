// header guard.
#ifndef LIB_FILE_IO_H_
#define LIB_FILE_IO_H_


// Headers.
#include "stdio.h"
#include "../bool/bool.h"


// Function Prototypes.
bool open_file(char*, FILE*);
bool read_line(FILE*, char*, size_t, char);
bool close_file(FILE*);


// End header guard.
#endif