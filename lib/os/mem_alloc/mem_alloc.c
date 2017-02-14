// Header guard.
#ifndef LIB_OS_MEM_ALLOC_C_
#define LIB_OS_MEM_ALLOC_C_


// Headers.
#include "mem_alloc.h"


/**
 * @brief Memory Adress Return Function
 *
 * @details Reads in an integer representing kilobytes of total memory. Using
 *			the total memory, the function returns the address as a hexadecimal
 *			string.
 *          
 * @param in: total memory in kb (int)
 *
 * @pre None
 *
 * @post Hexadecimal string address returned
 *
 * @exception Requires value > 0
 *
 * @exception Address pointer should be null
 */
unsigned int alloc_mem(int total_memory)
{
	// No mem?
	if (total_memory < 1)
	{
		// Nope.
		return 0;
	}
	

	// Seed the RNG.
	srand(time(NULL));
	

	// Return address.
	return rand() % total_memory;
}

#endif