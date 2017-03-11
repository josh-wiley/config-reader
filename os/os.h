// Header guard.
#ifndef LIB_OS_H_
#define LIB_OS_H_


// Headers.
#include <stdlib.h>
#include <string.h>
#include "../utils/file_io/file_io.h"
#include "config/os_config.h"
#include "mem_man/mem_man.h"
#include "io_man/io_man.h"
#include "pcb/pcb.h"
#include "config_tokens.h"


// Definitions.
#define FILE_IO_BUFFER_SIZE (size_t) 256


// OS.
typedef struct {
	os_config config;
	mem_man memory_manager;
	io_man io_manager;
	pcb pcb;
} os;


// Function prototypes.
int configure_os(os*, char*);
void destroy_os(os*);


// End header guard.
#endif