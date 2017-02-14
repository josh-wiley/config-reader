// Header guard.
#ifndef LIB_OS_PROG_EXEC_C_
#define LIB_OS_PROG_EXEC_C_


// Header.
#include "prog_exec.h"


// Execute program.
bool exec(prog_metadata* metadata_ptr, char* buffer_ptr, long buffer_size)
{
	// Get start time.
	clock_t start_time = clock();


	// Elapsed time.
	double elapsed_time_ms = (double) (clock() - start_time) * 1000 / CLOCKS_PER_SEC;


	// Success.
	return true;
}


// End header guard.
#endif