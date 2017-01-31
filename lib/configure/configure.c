// Header guard.
#ifndef LIB_CONFIGURE_C_
#define LIB_CONFIGURE_C_


// Header.
#include "configure.h"


// Configure OS.
bool configure_os(char* file_path, os_config* config_ptr)
{
	// Variables.
	FILE* stream_ptr;


	// Open file.
	if (!open_file(file_path, stream_ptr))
	{
		// Abort.
		return false;
	}


	// Read line.
	while (read_line(stream_ptr))
	{
		// Configure.
	}


	// Close stream.
	close_file(stream_ptr);


	// Success.
	message = "\n\nConfiguration file imported successfully.\n\n";
	return true;
}


// End header guard.
#endif