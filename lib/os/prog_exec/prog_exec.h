// Header guard.
#ifndef LIB_OS_PROG_EXEC_H_
#define LIB_OS_PROG_EXEC_H_


// Definitions.
#define FILE_PATH_BUFFER_SIZE 256
#define PROG_RESULTS_BUFFER_SIZE 100000
#define _BSD_SOURCE


// Headers.
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "../../bool/bool.h"
#include "../../file_io/file_io.h"
#include "../../logger/logger.h"
#include "../os.h"
#include "../mem_alloc/mem_alloc.h"


// Definitions.
#define METADATA_FOLDER_PATH "./conf/"


// Function prototypes.
bool exec(os*);


// End header guard.
#endif