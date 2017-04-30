// Header guard.
#ifndef LIB_OS_CONFIG_H_
#define LIB_OS_CONFIG_H_


// Headers.
#include <stdlib.h>
#include <string.h>


// Definitions.
#define STRING_SIZE (size_t) 128
#define ROUND_ROBIN_SCHED_CODE "RR"


// Scheduler type.
typedef enum { RR } sched_type;


// Log destination.
typedef enum { TO_BOTH, TO_FILE, TO_DISPLAY } destination;


// OS config.
typedef struct
{
	// Fields.
	float version;
	char metadata_file_path[STRING_SIZE];
	char log_file_path[STRING_SIZE];
	destination log_dest;
	unsigned int cpu_quantum;
	sched_type cpu_scheduling;


	// Times.
	unsigned int processor_period_ms;
	unsigned int memory_period_ms;
	unsigned int hdd_period_ms;
	unsigned int monitor_period_ms;
	unsigned int speaker_period_ms;
	unsigned int printer_period_ms;
	unsigned int keyboard_period_ms;
	unsigned int mouse_period_ms;


	// I/O devices.
	unsigned int total_mice;
	unsigned int total_keyboards;
	unsigned int total_hdds;
	unsigned int total_monitors;
	unsigned int total_speakers;
	unsigned int total_printers;
} os_config;


// Function prototypes.
void init_config(os_config*);
int set_cpu_scheduling(os_config*, char*);


// End header guard.
#endif