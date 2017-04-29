// Header guard.
#ifndef LIB_OS_CONFIG_C_
#define LIB_OS_CONFIG_C_


// Header.
#include "os_config.h"


// Initialize.
void init_config(os_config* this)
{
	// Initialize fields.
	this->log_dest = TO_BOTH;
	this->cpu_quantum = 0;


	// Initialize times.
	this->processor_period_ms = 
	this->memory_period_ms = 
	this->hdd_period_ms = 
	this->monitor_period_ms = 
	this->speaker_period_ms = 
	this->printer_period_ms = 
	this->keyboard_period_ms = 
	this->mouse_period_ms = 0;


	// Initialize I/O devices.
	this->total_mice = 
	this->total_keyboards = 
	this->total_hdds = 
	this->total_speakers = 
	this->total_monitors = 
	this->total_printers = 1;
}


// Set CPU scheduling.
int set_cpu_scheduling(os_config* this, char* buffer_ptr)
{
	// Round robin?
	if (strcmp(ROUND_ROBIN_SCHED_CODE, buffer_ptr) == 0)
	{
		// Set.
		this->cpu_scheduling = RR;


		// Done.
		return 0;
	}


	// Alert.
	printf("\n\nInvalid scheduling code.\n\n");


	// Abort.
	return 1;
}


// End header guard.
#endif