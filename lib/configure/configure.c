// Header guard.
#ifndef LIB_CONFIGURE_C_
#define LIB_CONFIGURE_C_


// Header.
#include "configure.h"


// Configure OS.
bool configure_os(char* file_path, os_config* config_ptr)
{
	// Variables.
	FILE* stream_ptr = open_file(file_path);
	char* buffer_ptr = malloc(BUFFER_SIZE);


	// Open file.
	if (!stream_ptr)
	{
		// Abort.
		return false;
	}


	// Read line.
	while (read_line(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_DELIMITER))
	{
		// Configure.
		printf(buffer_ptr); // TODO: REMOVE
	}


	// Close stream.
	close_file(stream_ptr);


	// Free buffer.
	free(buffer_ptr);


	// Success.
	return true;
}


// End header guard.
#endif