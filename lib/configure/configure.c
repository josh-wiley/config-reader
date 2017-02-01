// Header guard.
#ifndef LIB_CONFIGURE_C_
#define LIB_CONFIGURE_C_


// Header.
#include "configure.h"


// Attribute mapper.
bool map_attribute_to_config(char* attribute, FILE* stream_ptr, os_config* config_ptr)
{
	// Version/Phase attribute?
	if (strcmp(buffer_ptr, "Version/Phase") == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER, true);


		// Success.
		return true;
	}


	// File Path attribute?
	else if (strcmp(buffer_ptr, "File Path") == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER, true);


		// Success.
		return true;
	}


	// Processor cycle time attribute?
	else if (strcmp(buffer_ptr, "Processor cycle time (msec)"))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER, true);


		// Success.
		return true;
	}


	// Monitor display time attribute?
	else if (strcmp(buffer_ptr, "Monitor display time (msec)"))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER, true);


		// Success.
		return true;
	}


	// File end?
	else if (strcmp(buffer_ptr, "End Simulator Configuration File") == 0)
	{
		// Done.
		return true;
	}


	// No mapping.
	return false;
}


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


	// Consume initial, utterly useless, line.
	read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, '\n', true);


	// Read line.
	while (read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_ATTRIBUTE_DELIMITER, false))
	{
		// TODO: REMOVE
		printf("\n\n");
		printf(buffer_ptr);
		printf("\n\n");


		// Try to map attribute to OS config.
		if (!map_attribute_to_config(buffer_ptr, stream_ptr, config_ptr))
		{
			// Alert.
			printf("\n\nNo OS attribute for:\n");
			printf(buffer_ptr);
			printf("\n\n");


			// Abort.
			return false;
		};


		// Ignore incoming whitespace.
		ignore_incoming_whitespace(stream_ptr);
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