// Header guard.
#ifndef LIB_CONFIGURE_C_
#define LIB_CONFIGURE_C_


// Header.
#include "configure.h"


// Config attribute mapper.
bool map_attribute_to_config(char* buffer_ptr, FILE* stream_ptr, os_config* config_ptr)
{
	// Version/Phase attribute?
	if (strcmp(buffer_ptr, VERSION_PHASE_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->version = atof(buffer_ptr);


		// Success.
		return true;
	}


	// Processor cycle time attribute?
	else if (strcmp(buffer_ptr, PROCESSOR_PERIOD_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->processor_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Memory cycle time attribute?
	else if (strcmp(buffer_ptr, MEMORY_PERIOD_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->memory_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Hard drive cycle time attribute?
	else if (strcmp(buffer_ptr, HDD_PERIOD_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->hdd_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Keyboard cycle time attribute?
	else if (strcmp(buffer_ptr, KEYBOARD_PERIOD_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);

		
		// Save.
		config_ptr->keyboard_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Mouse cycle time attribute?
	else if (strcmp(buffer_ptr, MOUSE_PERIOD_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->mouse_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}



	// Monitor display period attribute?
	else if (strcmp(buffer_ptr, MONITOR_DISPLAY_TIME_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->monitor_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Speaker period attribute?
	else if (strcmp(buffer_ptr, SPEAKER_PERIOD_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->speaker_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Printer period attribute?
	else if (strcmp(buffer_ptr, PRINTER_PERIOD_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->printer_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Log destination attribute?
	else if (strcmp(buffer_ptr, LOG_DESTINATION_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Log to both?
		if (strcmp(buffer_ptr, LOG_TO_BOTH_VALUE) == 0)
		{
			// Save.
			config_ptr->log_dest = TO_BOTH;
		}


		// Log to file?
		else if (strcmp(buffer_ptr, LOG_TO_FILE_VALUE) == 0)
		{
			// Save.
			config_ptr->log_dest = TO_FILE;
		}


		// Log to display?
		else if (strcmp(buffer_ptr, LOG_TO_DISPLAY_VALUE) == 0)
		{
			// Save.
			config_ptr->log_dest = TO_DISPLAY;
		}


		// Success.
		return true;
	}


	// Log file path attribute?
	else if (strcmp(buffer_ptr, LOG_FILE_PATH_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		strcpy(config_ptr->log_file_path, buffer_ptr);


		// Success.
		return true;
	}


	// Metadata file path attribute?
	else if (strcmp(buffer_ptr, METADATA_FILE_PATH_ATTRIBUTE))
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		strcpy(config_ptr->metadata_file_path, buffer_ptr);


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
	read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, '\n');


	// Read from stream.
	while (read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_ATTRIBUTE_DELIMITER))
	{
		// Try to map attribute to OS config.
		if (!map_attribute_to_config(buffer_ptr, stream_ptr, config_ptr))
		{
			// Abort.
			return false;
		};
	}


	// Close stream.
	close_file(stream_ptr);


	// Free buffer.
	free(buffer_ptr);


	// Checkpoint.
	printf("\n\nConfigured operating system.\n\n");


	// Success.
	return true;
}


// Consume metadata.
bool consume_metadata(os_config* config_ptr)
{
	// Buffer.
	char* buffer_ptr = malloc(BUFFER_SIZE);


	// Get relative metadata file path.
	strcpy(buffer_ptr, METADATA_FOLDER_PATH);
	strcpy(buffer_pt, config_ptr->meta_data_file_path);


	// Get file stream.
	FILE* stream_ptr = open_file(buffer_ptr);


	// Consume initial, utterly useless, line.
	read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, '\n');


	// Read from stream.
	while (read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, OPERATION_DELIMITER))
	{
		// Try to map attribute to OS config.
		if (false) // TODO: SAVE TO METADATA DATA STRUCTURE
		{
			// Abort.
			return false;
		};
	}


	// Close stream.
	close_file(stream_ptr);


	// Free buffer.
	free(buffer_ptr);


	// Checkpoint.
	printf("\n\nConsumed metadata.\n\n");


	// Success.
	return true;
}


// End header guard.
#endif