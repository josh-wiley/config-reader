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
#include <semaphore.h>
#include <pthread.h>
#include "../../utils/file_io/file_io.h"
#include "../../utils/logger/logger.h"
#include "../os.h"


// Definitions.
#define METADATA_FOLDER_PATH "./conf/"


// Function prototypes.
int exec(os*);


// End header guard.
#endif