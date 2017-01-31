// Header guard.
#ifndef LIB_CONFIGURE_H_
#define LIB_CONFIGURE_H_


// Headers.
#include <stdlib.h>
#include "../bool/bool.h"
#include "../file_io/file_io.h"
#include "../os_config/os_config.h"


// Definitions.
#define CONFIG_DELIMITER '\n'
#define METADATA_DELIMITER ';'
#define BUFFER_SIZE (size_t) 128
#define DEFAULT_CONFIG "./conf/default.conf"


// Function prototypes.
bool configure_os(char*, os_config*);


// End header guard.
#endif