// Header guard.
#ifndef OS_SEMAPHORE_C_
#define OS_SEMAPHORE_C_


// Header.
#include "semaphore.h"


// Init.
void init(semaphore* this)
{
	// Initialize number of PCBs in queue.
	this->waiting_processes = -1;
}


// Get resource.
bool wait(semaphore* this, pcb* requester_ptr)
{
	// Decrement available resources.
	this->available--;


	// None available to begin with?
	if (this->available < 0)
	{
		// Queue full?
		if (this->waiting_processes == MAXIMUM_PROCESSES_PER_SEMAPHORE_QUEUE)
		{
			// Message.
			printf("\n\nSemaphore process queue full.\n\n");


			// Abort.
			return false;
		}


		// Add to queue.
		this->process_queue[++this->waiting_processes] = requester_ptr;


		// Wait.


	}
}


// Release resource.
void signal(semaphore *this, pcb* releaser_ptr)
{
	// Increment available resources.
	this->available++;


	// Resource available and waiting processes?
	if (this->available > 0 && this->waiting_processes >= 0)
	{
		// Remove PCB from queue.
		pcb* receiver_ptr = this->process_queue[this->waiting_processes--];


		// Wake up.

		
	}
}


// End header guard.
#endif