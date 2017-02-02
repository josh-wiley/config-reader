// Header guard.
#ifndef LIB_CONFIGURE_H_
#define LIB_CONFIGURE_H_


// Headers.
#include <stdlib.h>
#include <string.h>
#include "./token_definitions/config_tokens.h"
#include "./token_definitions/metadata_tokens.h"
#include "../bool/bool.h"
#include "../file_io/file_io.h"
#include "../os_config/os_config.h"


// Definitions.
#define BUFFER_SIZE (size_t) 128


// Function prototypes.
bool configure_os(char*, os_config*);
bool consume_metadata(os_config*);


// End header guard.
#endif