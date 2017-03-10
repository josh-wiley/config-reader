// Header guard.
#ifndef LIB_OS_C_
#define LIB_OS_C_


// Headers.
#include "os.h"

// Function prototypes.
int map_config(os*, char*, FILE*);
int get_memory_unit_multiplier(char*, unsigned int*);


// Configure OS.
int configure(os* this, char* file_path)
{
	// Get stream.
	FILE* stream_ptr = open_file(file_path, "r");


	// Initialize config.
	init_config(&this->config);


	// Buffer.
	char* buffer_ptr = malloc(FILE_IO_BUFFER_SIZE);
	memset(buffer_ptr, '\0', FILE_IO_BUFFER_SIZE);


	// Consume initial, utterly useless, line.
	read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, '\n');


	// Read from stream.
	while (read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_ATTRIBUTE_DELIMITER) == 0)
	{
		// Map attribute to OS config.
		if (map_config(this, buffer_ptr, stream_ptr))
		{
			// Abort.
			close_file(stream_ptr);
			free(buffer_ptr);
			return 1;
		}
	}


	// Checkpoint.
	printf("\n\nConfigured operating system.\n\n");


	// Clean up.
	close_file(stream_ptr);
	free(buffer_ptr);


	// Success.
	return 0;
}


// Config attribute mapper.
int map_config(os* this, char* buffer_ptr, FILE* stream_ptr)
{
	// Version/Phase attribute?
	if (strcmp(buffer_ptr, VERSION_PHASE_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		this->config.version = atof(buffer_ptr);


		// Success.
		return 0;
	}


	// Processor cycle time attribute?
	else if (strcmp(buffer_ptr, PROCESSOR_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		this->config.processor_period_ms = atoi(buffer_ptr);


		// Success.
		return 0;
	}


	// Memory cycle time attribute?
	else if (strcmp(buffer_ptr, MEMORY_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		this->config.memory_period_ms = atoi(buffer_ptr);


		// Success.
		return 0;
	}


	// System memory attribute?
	else if (strstr(buffer_ptr, SYSTEM_MEMORY_ATTRIBUTE))
	{
		// Conversion multiplier.
		unsigned int multiplier;


		// Units?
		if (get_memory_unit_multiplier(buffer_ptr, &multiplier))
		{
			// Alert.
			printf("\n\nInvalid system memory units...\n\n");


			// Abort.
			return 1;
		}


		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		this->memory_manager.total_mem_bytes = multiplier * atoi(buffer_ptr);


		// Success.
		return 0;
	}


	// Memory block size attribute?
	else if (strstr(buffer_ptr, MEMORY_BLOCK_SIZE_ATTRIBUTE))
	{
		// Conversion multiplier.
		unsigned int multiplier;


		// Units?
		if (get_memory_unit_multiplier(buffer_ptr, &multiplier))
		{
			// Alert.
			printf("\n\nInvalid system memory units...\n\n");


			// Abort.
			return 1;
		}


		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		this->memory_manager.block_size_bytes = multiplier * atoi(buffer_ptr);


		// Success.
		return 0;
	}


	// Hard drive cycle time attribute?
	else if (strcmp(buffer_ptr, HDD_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		this->config.hdd_period_ms = atoi(buffer_ptr);


		// Success.
		return 0;
	}


	// Hard drive quantity attribute?
	else if (strcmp(buffer_ptr, HDD_QUANTITY_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Set.
		set_available(&this->io_manager, HDD, atoi(buffer_ptr));


		// Success.
		return 0;
	}


	// Keyboard cycle time attribute?
	else if (strcmp(buffer_ptr, KEYBOARD_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);

		
		// Save.
		this->config.keyboard_period_ms = atoi(buffer_ptr);


		// Success.
		return 0;
	}


	// Keyboard quantity attribute?
	else if (strcmp(buffer_ptr, KEYBOARD_QUANTITY_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);

		
		// Set.
		set_available(&this->io_manager, KEYBOARD, atoi(buffer_ptr));


		// Success.
		return 0;
	}


	// Mouse cycle time attribute?
	else if (strcmp(buffer_ptr, MOUSE_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		this->config.mouse_period_ms = atoi(buffer_ptr);


		// Success.
		return 0;
	}


	// Mouse quantity attribute?
	else if (strcmp(buffer_ptr, MOUSE_QUANTITY_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);

		
		// Set.
		set_available(&this->io_manager, MOUSE, atoi(buffer_ptr));


		// Success.
		return 0;
	}


	// Monitor display period attribute?
	else if (strcmp(buffer_ptr, MONITOR_DISPLAY_TIME_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		this->config.monitor_period_ms = atoi(buffer_ptr);


		// Success.
		return 0;
	}


	// Monitor quantity attribute?
	else if (strcmp(buffer_ptr, MONITOR_QUANTITY_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);

		
		// Set.
		set_available(&this->io_manager, MONITOR, atoi(buffer_ptr));


		// Success.
		return 0;
	}


	// Speaker period attribute?
	else if (strcmp(buffer_ptr, SPEAKER_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		this->config.speaker_period_ms = atoi(buffer_ptr);


		// Success.
		return 0;
	}


	// Speaker quantity attribute?
	else if (strcmp(buffer_ptr, SPEAKER_QUANTITY_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);

		
		// Set.
		set_available(&this->io_manager, SPEAKER, atoi(buffer_ptr));


		// Success.
		return 0;
	}


	// Printer period attribute?
	else if (strcmp(buffer_ptr, PRINTER_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		this->config.printer_period_ms = atoi(buffer_ptr);


		// Success.
		return 0;
	}


	// Printer quantity attribute?
	else if (strcmp(buffer_ptr, PRINTER_QUANTITY_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Set.
		set_available(&this->io_manager, PRINTER, atoi(buffer_ptr));


		// Success.
		return 0;
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
			this->config.log_dest = TO_BOTH;
		}


		// Log to file?
		else if (strcmp(buffer_ptr, LOG_TO_FILE_VALUE) == 0)
		{
			// Save.
			this->config.log_dest = TO_FILE;
		}


		// Log to display?
		else if (strcmp(buffer_ptr, LOG_TO_DISPLAY_VALUE) == 0)
		{
			// Save.
			this->config.log_dest = TO_DISPLAY;
		}


		// Success.
		return 0;
	}


	// Log file path attribute?
	else if (strcmp(buffer_ptr, LOG_FILE_PATH_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		strcpy(this->config.log_file_path, buffer_ptr);


		// Success.
		return 0;
	}


	// Metadata file path attribute?
	else if (strcmp(buffer_ptr, METADATA_FILE_PATH_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		strcpy(this->config.metadata_file_path, buffer_ptr);


		// Success.
		return 0;
	}


	// File end?
	else if (strcmp(buffer_ptr, CONFIG_TERMINATOR_ATTRIBUTE) == 0)
	{
		// Done.
		return 0;
	}


	// No mapping.
	printf("\n\nNo OS attribute for: %s\n\n", buffer_ptr);
	return 1;
}


// Get memory unit multiplier.
int get_memory_unit_multiplier(char* buffer_ptr, unsigned int* multiplier_ptr)
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
			return 1;
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
			return 1;
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
		// Free.
		free(unit_token_ptr);


		// Abort.
		return 1;
	}


	// Free.
	free(unit_token_ptr);


	// Success.
	return 0;
}


// End header guard.
#endif