// Header guard.
#ifndef LIB_OS_PCB_H_
#define LIB_OS_PCB_H_


// Headers.
#include "../../bool/bool.h"
#include "../prog_metadata/prog_metadata.h"


// Definitions.
#define TOTAL_METADATA 512


// PCB state.
typedef enum { CREATED, READY, RUNNING, WAITING, TERMINATED } pcb_state;


// PCB.
typedef struct
{
	pcb_state state;
	prog_metadata metadata[TOTAL_METADATA];
	unsigned int num_metadata;
} pcb;


// Function prototypes.
bool init(pcb*, char*);
bool terminate(pcb*);
pcb_state get_state(pcb*);


// End header guard.
#endif