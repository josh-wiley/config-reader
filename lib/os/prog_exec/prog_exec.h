// Header guard.
#ifndef LIB_OS_PROG_EXEC_H_
#define LIB_OS_PROG_EXEC_H_


// Definitions.
#define BUFFER_SIZE 256
#define PROG_RESULTS_BUFFER_SIZE 100000


// Headers.
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "metadata_tokens.h"
#include "../../bool/bool.h"
#include "../../file_io/file_io.h"
#include "../../logger/logger.h"
#include "../os.h"
#include "../mem_alloc/mem_alloc.h"


// Function prototypes.
bool exec(os*);


// End header guard.
#endif