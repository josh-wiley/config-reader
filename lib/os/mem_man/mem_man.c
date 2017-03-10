// Header guard.
#ifndef LIB_OS_MEM_MAN_C_
#define LIB_OS_MEM_MAN_C_


// Headers.
#include "mem_man.h"


// Init.
void init(mem_man* this)
{
	// Initialize.
	this->blocks_allocated = 0;
	this->total_mem_bytes = 1024;
	this->block_size_bytes = 256;
}


// Allocate memory.
unsigned int alloc_mem(mem_man* this)
{
	// Generate next addressa and increment blocks allocated.
	return (this->blocks_allocated++ * this->block_size_bytes) % this->total_mem_bytes;
}


// End header guard.
#endif