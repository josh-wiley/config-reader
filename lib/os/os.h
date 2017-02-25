// Header guard.
#ifndef LIB_OS_H_
#define LIB_OS_H_


// Headers.
#include <stdlib.h>
#include <string.h>
#include "../bool/bool.h"
#include "../file_io/file_io.h"
#include "config/os_config.h"
#include "pcb/pcb.h"
#include "config_tokens.h"


// Definitions.
#define FILE_IO_BUFFER_SIZE (size_t) 256


// OS.
typedef struct {
	os_config config;
	pcb pcb;
} os;


// Function prototypes.
bool configure(os*, char*);


// End header guard.
#endif