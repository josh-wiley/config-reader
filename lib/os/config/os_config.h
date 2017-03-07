// Header guard.
#ifndef LIB_OS_CONFIG_H_
#define LIB_OS_CONFIG_H_


// Headers.
#include <stdlib.h>
#include "../../bool/bool.h"


// Definitions.
#define STRING_SIZE (size_t) 128


// Log destination.
typedef enum { TO_BOTH, TO_FILE, TO_DISPLAY } destination;


// OS config.
typedef struct
{
	float version;
	char metadata_file_path[STRING_SIZE];
	char log_file_path[STRING_SIZE];
	destination log_dest;
	unsigned int processor_period_ms;
	unsigned int memory_period_ms;
	unsigned int hdd_period_ms;
	unsigned int hdd_quantity;
	unsigned int monitor_period_ms;
	unsigned int monitor_quantity;
	unsigned int speaker_period_ms;
	unsigned int speaker_quantity;
	unsigned int printer_period_ms;
	unsigned int printer_quantity;
	unsigned int keyboard_period_ms;
	unsigned int keyboard_quantity;
	unsigned int mouse_period_ms;
	unsigned int mouse_quantity;
	unsigned int system_memory_bytes;
} os_config;


// Function prototypes.
bool init_config(os_config*);


// End header guard.
#endif