// Header guard.
#ifndef LIB_OS_METADATA_
#define LIB_OS_METADATA_


// Definitions.
#define MAX_OPERATIONS (size_t) 128


// Metadata code.
typedef enum { OS, APPLICATION, PROCESS, INPUT, OUTPUT, MEMORY } metadata_code;


// Metadata descriptor.
typedef enum { START, END, RUN, HDD, KEYBOARD, MOUSE, MONITOR, SPEAKER, BLOCK, ALLOCATE } metadata_descriptor;


// Metadata.
typedef struct
{
	metadata_code code;
	metadata_descriptor descriptor;
	unsigned int cycles;
} os_metadata;


// End header guard.
#endif