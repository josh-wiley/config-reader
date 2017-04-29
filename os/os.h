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
#include "sched/sched.h"
#include "pcb/pcb.h"
#include "op/op.h"
#include "config_tokens.h"
#include "metadata_tokens.h"


// Definitions.
#define FILE_IO_BUFFER_SIZE (size_t) 256
#define MAX_PCB_COUNT (size_t) 256
#define MAX_METADATA_PER_PROCESS (size_t) 512


// OS.
typedef struct {
	os_config config;
	mem_man memory_manager;
	io_man io_manager;
	pcb* pcb_tree[MAX_PCB_COUNT];
	unsigned int pcb_count;
} os;


// Function prototypes.
int configure_os(os*, char*);
int init_os(os*);
void destroy_os(os*);


// End header guard.
#endif