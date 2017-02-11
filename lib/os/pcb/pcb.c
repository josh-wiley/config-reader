// Header guard.
#ifndef LIB_OS_PCB_C_
#define LIB_OS_PCB_C_


// Header.
#include "pcb.h"


// Get state.
pcb_state get_state(pcb* pcb_ptr)
{
	// Return.
	return pcb_ptr->state;
}


// Set state.
bool set_state(pcb* pcb_ptr, pcb_state state)
{
	// Set.
	pcb_ptr->state = state;


	// Success.
	return true;
}


// End header guard.
#endif