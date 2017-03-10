// Header guard.
#ifndef LIB_LOGGER_H_
#define LIB_LOGGER_H_


// Headers.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config_tokens.h"
#include "metadata_tokens.h"
#include "../file_io/file_io.h"
#include "../../os/os.h"
#include "../../os/config/os_config.h"
#include "../../os/prog_metadata/prog_metadata.h"
#include "../../os/mem_man/mem_man.h"


// Function prototypes.
int log_os(os*);
int log_metadata_begin_op(os_config*, prog_metadata*, double);
int log_metadata_end_op(os*, prog_metadata*, double);


// End header guard.
#endif