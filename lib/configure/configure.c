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
	else if (strcmp(buffer_ptr, FILE_PATH_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER, true);


		// Success.
		return true;
	}


	// Processor cycle time attribute?
	else if (strcmp(buffer_ptr, PROCESSOR_CYCLE_TIME_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER, true);


		// Success.
		return true;
	}


	// Memory cycle time attribute?
	else if (strcmp(buffer_ptr, MEMORY_CYCLE_TIME_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER, true);


		// Success.
		return true;
	}


	// Hard drive cycle time attribute?
	else if (strcmp(buffer_ptr, HDD_CYCLE_TIME_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER, true);


		// Success.
		return true;
	}


	// Keyboard cycle time attribute?
	else if (strcmp(buffer_ptr, KEYBOARD_CYCLE_TIME_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER, true);


		// Success.
		return true;
	}


	// Mouse cycle time attribute?
	else if (strcmp(buffer_ptr, MOUSE_CYCLE_TIME_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER, true);


		// Success.
		return true;
	}



	// Monitor display time attribute?
	else if (strcmp(buffer_ptr, MONITOR_DISPLAY_TIME_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER, true);


		// Success.
		return true;
	}


	// Speaker cycle time attribute?
	else if (strcmp(buffer_ptr, SPEAKER_CYCLE_TIME_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER, true);


		// Success.
		return true;
	}


	// Printer cycle time attribute?
	else if (strcmp(buffer_ptr, PRINTER_CYCLE_TIME_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER, true);


		// Success.
		return true;
	}


	// Log destination attribute?
	else if (strcmp(buffer_ptr, LOG_DESTINATION_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER, true);


		// Success.
		return true;
	}


	// Log file path attribute?
	else if (strcmp(buffer_ptr, LOG_FILE_PATH_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER, true);


		// Success.
		return true;
	}


	// Metadate file path attribute?
	else if (strcmp(buffer_ptr, METADATA_FILE_PATH_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER, true);


		// Success.
		return true;
	}



	// File end?
	else if (strcmp(buffer_ptr, CONFIG_TERMINATOR_ATTRIBUTE) == 0)
	{
		// Done.
		return true;
	}


	// No mapping.
	printf("\n\nNo OS attribute for: %s\n\n", buffer_ptr);
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