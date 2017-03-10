// Header guard.
#ifndef LIB_OS_MEM_MAN_H_
#define LIB_OS_MEM_MAN_H_


// Headers.
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "../config/os_config.h"


// Memory management unit.
typedef struct {
	unsigned int total_mem_bytes;
	unsigned int block_size_bytes;
	unsigned int blocks_allocated;
} mem_man;


// Function prototypes.
void init(mem_man*);
unsigned int alloc_mem(mem_man*);


// End header guard
#endif