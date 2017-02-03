// Header guard.
#ifndef LIB_CONFIGURE_C_
#define LIB_CONFIGURE_C_


// Header.
#include "configure.h"


// Config attribute mapper.
bool map_to_config(char* buffer_ptr, FILE* stream_ptr, os_config* config_ptr)
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
	else if (strcmp(buffer_ptr, PROCESSOR_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->processor_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Memory cycle time attribute?
	else if (strcmp(buffer_ptr, MEMORY_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->memory_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Hard drive cycle time attribute?
	else if (strcmp(buffer_ptr, HDD_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->hdd_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Keyboard cycle time attribute?
	else if (strcmp(buffer_ptr, KEYBOARD_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);

		
		// Save.
		config_ptr->keyboard_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Mouse cycle time attribute?
	else if (strcmp(buffer_ptr, MOUSE_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->mouse_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}



	// Monitor display period attribute?
	else if (strcmp(buffer_ptr, MONITOR_DISPLAY_TIME_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->monitor_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Speaker period attribute?
	else if (strcmp(buffer_ptr, SPEAKER_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->speaker_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Printer period attribute?
	else if (strcmp(buffer_ptr, PRINTER_PERIOD_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		config_ptr->printer_period_ms = atoi(buffer_ptr);


		// Success.
		return true;
	}


	// Log destination attribute?
	else if (strcmp(buffer_ptr, LOG_DESTINATION_ATTRIBUTE) == 0)
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
	else if (strcmp(buffer_ptr, LOG_FILE_PATH_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		strcpy(config_ptr->log_file_path, buffer_ptr);


		// Success.
		return true;
	}


	// Metadata file path attribute?
	else if (strcmp(buffer_ptr, METADATA_FILE_PATH_ATTRIBUTE) == 0)
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


// Is valid descriptor for code?
bool is_valid_metadata_descriptor(metadata_code code, char* descriptor)
{
	// Valid descriptor based on code?
	switch (code)
	{
		// OS?
		case OS:
			return strcmp(descriptor, START_DESCRIPTOR) == 0 ||
				strcmp(descriptor, END_DESCRIPTOR) == 0;


		// Application?
		case APPLICATION:
			return strcmp(descriptor, START_DESCRIPTOR) == 0 ||
				strcmp(descriptor, END_DESCRIPTOR) == 0;


		// Process?
		case PROCESS:
			return strcmp(descriptor, RUN_DESCRIPTOR) == 0;


		// Input?
		case INPUT:
			return strcmp(descriptor, HDD_DESCRIPTOR) == 0 ||
				strcmp(descriptor, KEYBOARD_DESCRIPTOR) == 0 ||
				strcmp(descriptor, MOUSE_DESCRIPTOR) == 0 ||
				strcmp(descriptor, PRINTER_DESCRIPTOR);


		// Output? 
		case OUTPUT:
			return strcmp(descriptor, HDD_DESCRIPTOR) == 0 ||
				strcmp(descriptor, MONITOR_DESCRIPTOR) == 0 ||
				strcmp(descriptor, SPEAKER_DESCRIPTOR) == 0;


		// Memory?
		case MEMORY:
			return strcmp(descriptor, BLOCK_DESCRIPTOR) == 0 ||
				strcmp(descriptor, ALLOCATE_DESCRIPTOR) == 0;
		

		// Default.
		default:
			return false;
	}
}


// Add metadata.
bool add_metadata(os_config* config_ptr, char* buffer_ptr, FILE* stream_ptr)
{
	// Save current metadata position.
	unsigned int i = config_ptr->num_metadata;


	// Match first character to metadata code.
	switch (buffer_ptr[0])
	{
		// OS?
		case OS_CODE:
			// Add code.
			config_ptr->metadata[i].code = OS;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Try to add the descriptor.
			if (!is_valid_metadata_descriptor(OS, buffer_ptr))
			{
				// Abort.
				printf("\n\n\
					ERROR READING DESCRIPTOR %i:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					i + 1, buffer_ptr, OS_CODE
				);
				return false;
			}


			// Get cycles.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles.
			config_ptr->metadata[i].cycles = atoi(buffer_ptr); // TODO: USE PROPER ENUM VALUE


			// Increment number of metadata.
			config_ptr->num_metadata++;


			// Done.
			return true;
		

		// Application?
		case APPLICATION_CODE:
			// Add code.
			config_ptr->metadata[i].code = APPLICATION;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Try to add the descriptor.
			if (!is_valid_metadata_descriptor(APPLICATION, buffer_ptr))
			{
				// Abort.
				printf("\n\n\
					ERROR READING DESCRIPTOR %i:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					i + 1, buffer_ptr, APPLICATION_CODE
				);
				return false;
			}


			// Get cycles.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles.
			config_ptr->metadata[i].cycles = atoi(buffer_ptr);


			// Increment number of metadata.
			config_ptr->num_metadata++;


			// Done.
			return true;
		

		// Process?
		case PROCESS_CODE:
			// Add code.
			config_ptr->metadata[i].code = PROCESS;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Try to add the descriptor.
			if (!is_valid_metadata_descriptor(PROCESS, buffer_ptr))
			{
				// Abort.
				printf("\n\n\
					ERROR READING DESCRIPTOR %i:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					i + 1, buffer_ptr, PROCESS_CODE
				);
				return false;
			}


			// Get cycles.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles.
			config_ptr->metadata[i].cycles = atoi(buffer_ptr);


			// Increment number of metadata.
			config_ptr->num_metadata++;


			// Done.
			return true;


		// Input?
		case INPUT_CODE:
			// Add code.
			config_ptr->metadata[i].code = INPUT;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Try to add the descriptor.
			if (!is_valid_metadata_descriptor(INPUT, buffer_ptr))
			{
				// Abort.
				printf("\n\n\
					ERROR READING DESCRIPTOR %i:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					i + 1, buffer_ptr, INPUT_CODE
				);
				return false;
			}


			// Get cycles.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles.
			config_ptr->metadata[i].cycles = atoi(buffer_ptr);


			// Increment number of metadata.
			config_ptr->num_metadata++;


			// Done.
			return true;


		// Output?
		case OUTPUT_CODE:
			// Add code.
			config_ptr->metadata[i].code = OUTPUT;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Try to add the descriptor.
			if (!is_valid_metadata_descriptor(OUTPUT, buffer_ptr))
			{
				// Abort.
				printf("\n\n\
					ERROR READING DESCRIPTOR %i:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					i + 1, buffer_ptr, OUTPUT_CODE
				);
				return false;
			}


			// Get cycles.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles.
			config_ptr->metadata[i].cycles = atoi(buffer_ptr);


			// Increment number of metadata.
			config_ptr->num_metadata++;


			// Done.
			return true;
		

		// Memory?
		case MEMORY_CODE:
			// Add code.
			config_ptr->metadata[i].code = MEMORY;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Try to add the descriptor.
			if (!is_valid_metadata_descriptor(MEMORY, buffer_ptr))
			{
				// Abort.
				printf("\n\n\
					ERROR READING DESCRIPTOR %i:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					i + 1, buffer_ptr, MEMORY_CODE
				);
				return false;
			}


			// Get cycles.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles.
			config_ptr->metadata[i].cycles = atoi(buffer_ptr);


			// Increment number of metadata.
			config_ptr->num_metadata++;


			// Done.
			return true;


		// No match?
		default:
			// Abort
			printf("\n\n\
				ERROR READING CODE %i:\n\
				Invalid code \"%c\".\
				\n\n",
				i + 1, buffer_ptr[0]
			);
			return false;
	}
}


// Configure OS.
bool configure_os(char* file_path, os_config* config_ptr)
{
	// Get stream.
	FILE* stream_ptr = open_file(file_path);


	// Buffer.
	char* buffer_ptr = malloc(BUFFER_SIZE);
	memset(buffer_ptr, '\0', BUFFER_SIZE);


	// Consume initial, utterly useless, line.
	read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, '\n');


	// Read from stream.
	while (read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, CONFIG_ATTRIBUTE_DELIMITER))
	{
		// Try to map attribute to OS config.
		if (!map_to_config(buffer_ptr, stream_ptr, config_ptr))
		{
			// Abort.
			close_file(stream_ptr);
			free(buffer_ptr);
			return false;
		}
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
	memset(buffer_ptr, '\0', BUFFER_SIZE);


	// Get relative metadata file path.
	strcat(buffer_ptr, METADATA_FOLDER_PATH);
	strcat(buffer_ptr, config_ptr->metadata_file_path);


	// Get file stream.
	FILE* stream_ptr = open_file(buffer_ptr);


	// Clear metadata.
	config_ptr->num_metadata = 0;


	// Consume initial, utterly useless, line.
	read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, '\n');


	// Read from stream.
	while (read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_CODE_TERMINATOR))
	{
		// Try to map attribute to OS config.
		if (!add_metadata(config_ptr, buffer_ptr, stream_ptr))
		{
			// Abort.
			close_file(stream_ptr);
			free(buffer_ptr);
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