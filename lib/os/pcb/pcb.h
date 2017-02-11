// Header guard.
#ifndef LIB_OS_PCB_H_
#define LIB_OS_PCB_H_


// PCB state.
typedef enum { START, READY, RUNNING, WAITING, EXIT } pcb_state;


// PCB.
typedef struct
{
	pcb_state state;
} pcb;


// Function prototypes.
pcb_state get_state(pcb*);
bool set_state(pcb*, pcb_state);


// End header guard.
#endif