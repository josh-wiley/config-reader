// Header guard.
#ifndef LIB_OS_PCB_H_
#define LIB_OS_PCB_H_


// Headers.
#include "../op/op.h"
#include "../prog_metadata/prog_metadata.h"
#include "../op/op.h"


// Definitions.
#define STREAM_BUFFER_SIZE 256


// PCB state.
typedef enum { CREATED, READY, RUNNING, WAITING, TERMINATED } pcb_state;


// PCB.
typedef struct
{
	pcb_state state;
	op* operations;
	unsigned int num_operations;
	unsigned int current_op_index;
} pcb;


// Function declarations.
int create_pcb(pcb*, prog_metadata*, unsigned int);
int terminate_pcb(pcb*);
pcb_state get_state(pcb*);
void set_state(pcb*, pcb_state);


// End header guard.
#endif