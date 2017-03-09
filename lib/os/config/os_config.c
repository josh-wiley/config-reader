// Header guard.
#ifndef LIB_OS_CONFIG_C_
#define LIB_OS_CONFIG_C_


// Header.
#include "os_config.h"


// Initialize.
bool init_config(os_config* this)
{
	// Default initialize all fields.
	this->log_dest = TO_BOTH;
	this->processor_period_ms = 0;
	this->memory_period_ms = 0;
	this->hdd_period_ms = 0;
	this->hdd_quantity = 1;
	this->monitor_period_ms = 0;
	this->monitor_quantity = 1;
	this->speaker_period_ms = 0;
	this->speaker_quantity = 1;
	this->printer_period_ms = 0;
	this->printer_quantity = 1;
	this->keyboard_period_ms = 0;
	this->keyboard_quantity = 1;
	this->mouse_period_ms = 0;
	this->mouse_quantity = 1;


	// Success.
	return true;
}


// End header guard.
#endif