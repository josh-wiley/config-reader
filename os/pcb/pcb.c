// Header guard.
#ifndef LIB_OS_PCB_C_
#define LIB_OS_PCB_C_


// Header.
#include "pcb.h"


// Function declarations.
static inline int create_op(prog_metadata*, op*);


// Create.
int create_pcb(pcb* this, proj_metadata* metadata_buffer, unsigned int num_operations)
{
	// Save the number of operations.
	this->num_operations = num_operations;


	// Allocate memory.
	malloc(num_operations, sizeof(op));


	// Import operations.
	for (unsigned int i = 0; i < num_operations; i++)
	{
		// Create operation.
		create_op(&metadata_buffer[i], &this->operations[i]);
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


// Create operation.
static inline int create_op(prog_metadata*, op*)
{
	// Done.
	return 0;
}


// End header guard.
#endif