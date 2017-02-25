// Header guard.
#ifndef LIB_OS_C_
#define LIB_OS_C_


// Headers.
#include "os.h"

// Function prototypes.
bool map_to_config(char*, FILE*, os_config*);
bool get_memory_unit_multiplier(char*, unsigned int*);


// Configure OS.
bool configure(os* this, char* file_path)
{
	// Get stream.
	FILE* stream_ptr = open_file(file_path, "r");


	// Buffer.
	char* buffer_ptr = malloc(FILE_IO_BUFFER_SIZE);
	memset(buffer_ptr, '\0', FILE_IO_BUFFER_SIZE);


	// Consume initial, utterly useless, line.
	read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, '\n');


	// Read from stream.
	while (read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_ATTRIBUTE_DELIMITER))
	{
		// Try to map attribute to OS config.
		if (!map_to_config(buffer_ptr, stream_ptr, &this->config))
		{
			// Abort.
			close_file(stream_ptr);
			free(buffer_ptr);
			return false;
		}
	}


	// Checkpoint.
	printf("\n\nConfigured operating system.\n\n");


	// Clean up.
	close_file(stream_ptr);
	free(buffer_ptr);


	// Success.
	return true;
}


// Config attribute mapper.
bool map_to_config(char* buffer_ptr, FILE* stream_ptr, os_config* config_ptr)
{
	// Version/Phase attribute?
	if (strcmp(buffer_ptr, VERSION_PHASE_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->version = atof(buffer_ptr);


		// Success.
		return true;
	}


	// Processor cycle time attribute?
	else if (strcmp(buffer_ptr, PROCESSOR_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->processor_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Memory cycle time attribute?
	else if (strcmp(buffer_ptr, MEMORY_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->memory_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// System memory attribute?
	else if (strstr(buffer_ptr, SYSTEM_MEMORY_ATTRIBUTE))
	{
		// Conversion multiplier.
		unsigned int multiplier;


		// Units?
		if (!get_memory_unit_multiplier(buffer_ptr, &multiplier))
		{
			// Alert.
			printf("\n\nSYSTEM MEMORY ERROR: Invalid units\n\n");


			// Abort.
			return false;
		}


		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->system_memory_bytes = multiplier * atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Hard drive cycle time attribute?
	else if (strcmp(buffer_ptr, HDD_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->hdd_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Keyboard cycle time attribute?
	else if (strcmp(buffer_ptr, KEYBOARD_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);

		
		// Save.
		config_ptr->keyboard_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Mouse cycle time attribute?
	else if (strcmp(buffer_ptr, MOUSE_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->mouse_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}



	// Monitor display period attribute?
	else if (strcmp(buffer_ptr, MONITOR_DISPLAY_TIME_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->monitor_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Speaker period attribute?
	else if (strcmp(buffer_ptr, SPEAKER_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->speaker_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Printer period attribute?
	else if (strcmp(buffer_ptr, PRINTER_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->printer_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Log destination attribute?
	else if (strcmp(buffer_ptr, LOG_DESTINATION_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


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
	else if (strcmp(buffer_ptr, LOG_FILE_PATH_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		strcpy(config_ptr->log_file_path, buffer_ptr);


		// Success.
		return true;
	}


	// Metadata file path attribute?
	else if (strcmp(buffer_ptr, METADATA_FILE_PATH_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


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


// Get memory unit multiplier.
bool get_memory_unit_multiplier(char* buffer_ptr, unsigned int* multiplier_ptr)
{
	// Counter.
	unsigned int i = 0;
	char item = buffer_ptr[i];


	// Ignore up to start delimiter.
	while (item != '(')
	{
		// End of buffer?
		if (item == 0 || i == 64)
		{
			// Abort.
			return false;
		}


		// Advance.
		item = buffer_ptr[++i];
	}


	// Discard start delimiter.
	item = buffer_ptr[++i];


	// Unit token buffer.
	char* unit_token_ptr = malloc(64);
	memset(unit_token_ptr, 0, 64);


	// Unit token buffer index.
	unsigned int j = 0;


	// Copy unit token.
	while (item != ')')
	{
		// End of buffer?
		if (item == 0 || i == 64)
		{
			// Free.
			free(unit_token_ptr);


			// Abort.
			return false;
		}


		// Save.
		unit_token_ptr[j++] = item;
		

		// Advance.
		item = buffer_ptr[++i];
	}


	// KB?
	if (strcmp(unit_token_ptr, SYSTEM_MEMORY_KB_UNIT) == 0)
	{
		// Set.
		*multiplier_ptr = 1024;
	}


	// MB?
	else if (strcmp(unit_token_ptr, SYSTEM_MEMORY_MB_UNIT) == 0)
	{
		// Set.
		*multiplier_ptr = 1048576;
	}


	// GB?
	else if (strcmp(unit_token_ptr, SYSTEM_MEMORY_GB_UNIT) == 0)
	{
		// Set.
		*multiplier_ptr = 1073741824;
	}


	// No match.
	else
	{
		// TODO: REMOVE
		printf("\n\n%s\n\n", unit_token_ptr);


		// Free.
		free(unit_token_ptr);


		// Abort.
		return false;
	}


	// Free.
	free(unit_token_ptr);


	// Success.
	return true;
}


// End header guard.
#endif