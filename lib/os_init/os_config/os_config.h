// Header guard.
#ifndef LIB_OS_CONFIG_H_
#define LIB_OS_CONFIG_H_


// Headers.
#include <stdlib.h>
#include "os_metadata.h"


// Definitions.
#define STRING_SIZE (size_t) 128
#define MAX_METADATA (size_t) 512


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
	unsigned int monitor_period_ms;
	unsigned int speaker_period_ms;
	unsigned int printer_period_ms;
	unsigned int keyboard_period_ms;
	unsigned int mouse_period_ms;
	os_metadata metadata[MAX_METADATA];
	int num_metadata;
} os_config;


// End header guard.
#endif