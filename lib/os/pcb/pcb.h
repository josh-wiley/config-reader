// Header guard.
#ifndef LIB_OS_PCB_H_
#define LIB_OS_PCB_H_


// Headers.
#include <string.h>
#include "../../bool/bool.h"
#include "../../file_io/file_io.h"
#include "../config/os_config.h"
#include "../prog_metadata/prog_metadata.h"
#include "metadata_tokens.h"


// Definitions.
#define STREAM_BUFFER_SIZE 256
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
bool create_pcb(pcb*, char*);
bool terminate_pcb(pcb*);
pcb_state get_state(pcb*);
void set_state(pcb*, pcb_state);


// End header guard.
#endif