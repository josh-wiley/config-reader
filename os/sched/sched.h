// Header guard.
#ifndef OS_SCHED_H_
#define OS_SCHED_H_


// Definitions.
#define FILE_PATH_BUFFER_SIZE 256
#define PROG_RESULTS_BUFFER_SIZE 100000
#define _BSD_SOURCE


// Headers.
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "../os.h"
#include "../pcb/pcb.h"
#include "../config/os_config.h"
#include "../../utils/file_io/file_io.h"
#include "../../utils/logger/logger.h"


// Definitions.
#define METADATA_FOLDER_PATH "./conf/"


// Function prototypes.
int start_sched(pcb*, const os_config*);


// End header guard.
#endif