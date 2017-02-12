// Header guard.
#ifndef LIB_OS_PROGRAM_SIM_C_
#define LIB_OS_PROGRAM_SIM_C_


// Header.
#include "program_sim.h"


// Run program sim.
bool sim_prog(os_metadata* metadata_ptr, char* results_ptr)
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