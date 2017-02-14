// Header guard.
#ifndef LIB_OS_PROG_EXEC_H_
#define LIB_OS_PROG_EXEC_H_


// Definitions.
#define PROG_RESULTS_BUFFER_SIZE 100000


// Headers.
#include <string.h>
#include <time.h>
#include "../../bool/bool.h"
#include "../prog_metadata/prog_metadata.h"
#include "../mem_alloc/mem_alloc.h"


// Function prototypes.
bool exec(prog_metadata*, char*, long);


// End header guard.
#endif