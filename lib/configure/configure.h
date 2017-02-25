// Header guard.
#ifndef LIB_CONFIGURE_H_
#define LIB_CONFIGURE_H_


// Headers.
#include <stdlib.h>
#include <string.h>
#include "./config_tokens.h"
#include "../bool/bool.h"
#include "../file_io/file_io.h"
#include "../os/os.h"


// Definitions.
#define BUFFER_SIZE (size_t) 256


// Function prototypes.
bool configure_os(char*, os*);


// End header guard.
#endif