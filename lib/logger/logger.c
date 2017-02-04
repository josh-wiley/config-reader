// Header guard.
#ifndef LIB_LOGGER_C_
#define LIB_LOGGER_C_


// Headers.
#include "logger.h"


// Function prototypes.
bool log_to_file(os_config*);
bool log_to_display(os_config*);


// Log OS config.
bool log(os_config* config_ptr)
{
	// Log to both?
	if (config_ptr->log_dest == TO_BOTH)
	{
		// Log to both.
		return log_to_file(config_ptr) && log_to_display(config_ptr);
	}


	// Log to file?
	if (config_ptr->log_dest == TO_FILE)
	{
		// Log to file.
		return log_to_file(config_ptr);
	}


	// Log to display?
	if (config_ptr->log_dest == TO_DISPLAY)
	{
		// Log to display.
		return log_to_display(config_ptr);
	}


	// Not sure what happened, but failed.
	return false;
}


// End header guard.
#endif