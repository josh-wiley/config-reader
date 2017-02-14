// Header guard.
#ifndef LIB_OS_PROG_METADATA_H_
#define LIB_OS_PROG_METADATA_H_


// Headers.
#include <stdlib.h>
#include <stdio.h>
#include "./tokens.h"


// Definitions.
#define MAX_OPERATIONS (size_t) 128


// Metadata code.
typedef enum { OS, APPLICATION, PROCESS, INPUT, OUTPUT, MEMORY } metadata_code;


// Metadata descriptor.
typedef enum { START, END, RUN, HDD, KEYBOARD, MOUSE, MONITOR, SPEAKER, PRINTER, BLOCK, ALLOCATE } metadata_descriptor;


// Metadata.
typedef struct
{
	metadata_code code;
	metadata_descriptor descriptor;
	unsigned int cycles;
} prog_metadata;


// Function prototypes.
char get_code(prog_metadata*);
char* get_descriptor(prog_metadata*);


// End header guard.
#endif