// Header guard.
#ifndef LIB_OS_H_
#define LIB_OS_H_


// Headers.
#include "./config/os_config.h"
#include "./pcb/pcb.h"


// OS.
typedef struct {
	os_config config;
	pcb pcb;
} os;


// End header guard.
#endif