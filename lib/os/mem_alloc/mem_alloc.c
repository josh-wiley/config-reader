// Header guard.
#ifndef LIB_OS_MEM_ALLOC_C_
#define LIB_OS_MEM_ALLOC_C_


// Headers.
#include "mem_alloc.h"


// Init.
void init(mem_man* this, os_config* config_ptr)
{
	// Initialize.
	this->blocks_allocated = 0;


	// Impart state.
	this->total_mem = config_ptr->system_memory_bytes;
	this->block_size = config_ptr->memory_block_size;
}


// Allocate memory.
unsigned int alloc_mem(mem_man* this)
{
	// Generate next address.
	return (this->blocks_allocated * this->block_size) % this->total_mem;
}

#endif