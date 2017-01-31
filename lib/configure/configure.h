// Header guard.
#ifndef LIB_CONFIGURE_H_
#define LIB_CONFIGURE_H_


// Headers.
#include "../bool/bool.h"
#include "../file_io/file_io.h"
#include "../os_config/os_config.h"


// Constants.
const unsigned char* DEFAULT_CONFIG = "./conf/default.conf";
const unsigned char* SUPPORTED_FILE_TYPES[] = { "mdf", "conf" };


// Function prototypes.
bool configure_os(char*, os_config*);


// End header guard.
#endif