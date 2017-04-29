// Header guard.
#ifndef LIB_OS_PCB_C_
#define LIB_OS_PCB_C_


// Header.
#include "pcb.h"


// Create.
int create_pcb(pcb* this, prog_metadata* metadata_buffer, unsigned int num_operations)
{
	// Save the number of operations.
	this->num_operations = num_operations;


	// Allocate memory.
	malloc(num_operations, sizeof(op));


	// Import operations.
	for (unsigned int i = 0; i < num_operations; i++)
	{
		// Create operation.
		create_op(&this->operations[i], &metadata_buffer[i]);
	}


	// Set current operation.
	this->current_op_index = 0;


	// State.
	this->state = CREATED;


	// Success.
	return 0;
}


// Terminate.
int terminate_pcb(pcb* this)
{
	// Operations?
	if (this->operations)
	{
		// Free.
		free(this->operations);
	}


	// Set state.
	this->state = TERMINATED;


	// Successful.
	return 0;
}


// Get state.
pcb_state get_state(pcb* this)
{
	// Return.
	return this->state;
}


// Get state.
void set_state(pcb* this, pcb_state state)
{
	// Set.
	this->state = state;
}


// End header guard.
#endif