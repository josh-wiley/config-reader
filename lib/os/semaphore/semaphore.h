// Header guard.
#ifndef OS_SEMAPHORE_H_
#define OS_SEMAPHORE_H_


// Headers.
#include "../../bool/bool.h"
#include "../pcb/pcb.h"


// Definitions.
#define MAXIMUM_PROCESSES_PER_SEMAPHORE_QUEUE 255


// Semaphore.
typedef struct
{
	int available;
	pcb** process_queue[MAXIMUM_PROCESSES_PER_SEMAPHORE_QUEUE];
	int waiting_processes;
} semaphore;


// Function prototypes.
void init(semaphore*);
bool wait(semaphore*, pcb*);
void signal(semaphore*, pcb*);


// End header guard.
#endif