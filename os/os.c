// Header guard.
#ifndef LIB_OS_C_
#define LIB_OS_C_


// Headers.
#include "os.h"


// Function declarations.
static inline int map_config(os*, char*, FILE*);
static inline int get_memory_unit_multiplier(char*, unsigned int*);
static inline int ingest_metadata(char*, prog_metadata*, FILE*);
static inline int add_metadata_descriptor(prog_metadata*, char*);


// Configure OS.
int configure_os(os* this, char* file_path)
{
	// Get stream.
	FILE* stream_ptr = open_file(file_path, "r");


	// Initialize the config structure.
	init_config(&this->config);


	// Create buffer.
	char* buffer_ptr = calloc(FILE_IO_BUFFER_SIZE, sizeof(char));


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


	// Initialize I/O manager with new config.
	init_io_man(&this->io_manager, &this->config);


	// Checkpoint.
	printf("\n\nConfigured operating system.\n\n");


	// Clean up.
	close_file(stream_ptr);
	free(buffer_ptr);


	// Success.
	return 0;
}


// Start the OS.
int init_os(os* this)
{
	// OS flags.
	int has_os_start_in_md = 0;
	int has_os_end_in_md = 0;


	// Set total PCBs.
	this->pcb_count = 0;


	// Get file stream.
	FILE* stream_ptr = open_file(this->config.metadata_file_path, "r");


	// Create file input buffer.
	char* fin_buffer_ptr = calloc(STREAM_BUFFER_SIZE, sizeof(char));


	// Metadata buffer management.
	unsigned int current_md_index = 0;
	unsigned int md_buffer_size = MAX_METADATA_PER_PROCESS;


	// Create metadata buffer.
	prog_metadata* md_buffer_ptr = malloc(md_buffer_size * sizeof(prog_metadata));


	// Consume initial, utterly useless, line.
	read_until(stream_ptr, fin_buffer_ptr, STREAM_BUFFER_SIZE, '\n');


	// Read from stream.
	while (read_until(stream_ptr, fin_buffer_ptr, STREAM_BUFFER_SIZE, METADATA_CODE_TERMINATOR) == 0)
	{
		// If room, ingest metadata.
		if (current_md_index == md_buffer_size || ingest_metadata(fin_buffer_ptr, &md_buffer_ptr[current_md_index], stream_ptr))
		{
			// Abort.
			close_file(stream_ptr);
			free(fin_buffer_ptr);
			free(md_buffer_ptr);
			return 1;
		};


		// Get the ingested metadata.
		prog_metadata ingested_md = md_buffer_ptr[current_md_index];


		// Is the ingested metadata signaling the end of a process?
		if (ingested_md.code == APPLICATION && ingested_md.descriptor == END)
		{
			// Create and add the PCB.
			create_pcb(&this->pcb_tree[this->pcb_count], md_buffer_ptr, current_md_index + 1);
			this->pcb_count++;


			// Reset metadata buffer.
			current_md_index = 0;
		}


		// OS metadata ingested?
		else if (ingested_md.code == OS)
		{
			// Start?
			if (ingested_md.descriptor == START)
			{
				// Flag.
				has_os_start_in_md = 1;
			}


			// End?
			else if (ingested_md.descriptor == END)
			{
				// Flag.
				has_os_end_in_md = 1;


				// Done.
				break;
			}
		}


		// If not OS or APPLICATION END, save (increment index);
		else
		{
			// Increment current index.
			current_md_index++;
		}
	}


	// Clean up.
	close_file(stream_ptr);
	free(fin_buffer_ptr);
	free(md_buffer_ptr);


	// Checkpoint.
	printf("\n\nCreated process tree.\n\n");


	// Has appropriate OS flags?
	if (!(has_os_start_in_md && has_os_end_in_md))
	{
		// Alert.
		printf("\n\nMetadata file does not start and stop the OS.\n\n");


		// Abort.
		return 1;
	}


	// Start the scheduler.
	if (start_sched(this->pcb_tree, this->pcb_count, &this->config))
	{
		// Alert.
		printf("\n\nOS failed to start scheduler.\n\n");


		// Abort.
		return 1;
	}


	// Done.
	return 0;
}


// Destroy OS.
void destroy_os(os* this)
{
	// Destory I/O manager.
	destroy_io_man(&this->io_manager);
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
		this->config.total_hdds = atoi(buffer_ptr);


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
		this->config.total_keyboards = atoi(buffer_ptr);


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
		this->config.total_mice = atoi(buffer_ptr);


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
		this->config.total_monitors = atoi(buffer_ptr);


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
		this->config.total_speakers = atoi(buffer_ptr);


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
		this->config.total_printers = atoi(buffer_ptr);


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


	// CPU quantum number attribute?
	else if (strcmp(buffer_ptr, CPU_QUANTUM_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		this->config.cpu_quantum = atoi(buffer_ptr);


		// Success.
		return 0;
	}


	// CPU scheduling code attribute?
	else if (strcmp(buffer_ptr, CPU_SCHEDULING_CODE_ATTRIBUTE) == 0)
	{
		// Get value.
		read_until(stream_ptr, buffer_ptr, FILE_IO_BUFFER_SIZE, CONFIG_VALUE_DELIMITER);


		// Save.
		set_cpu_scheduling(&this->config, buffer_ptr);


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
	char* unit_token_ptr = malloc(64 * sizeof(char));
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


// Add metadata.
int ingest_metadata(char* fin_buffer_ptr, prog_metadata* metadata_ptr, FILE* stream_ptr)
{
	// Match first character to metadata code.
	switch (fin_buffer_ptr[0])
	{
		// OS?
		case OS_CODE:
			// Add code.
			metadata_ptr->code = OS;


			// Get descriptor.
			read_until(stream_ptr, fin_buffer_ptr, STREAM_BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Add the descriptor.
			if (add_metadata_descriptor(metadata_ptr, fin_buffer_ptr))
			{
				// Alert.
				printf("\n\n\
					ERROR READING DESCRIPTOR:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					fin_buffer_ptr, OS_CODE
				);


				// Abort.
				return 1;
			}


			// Get cycles.
			read_until(stream_ptr, fin_buffer_ptr, STREAM_BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles (always 0 for OS start and end).
			metadata_ptr->cycles = 0;


			// Done.
			return 0;
		

		// Application?
		case APPLICATION_CODE:
			// Add code.
			metadata_ptr->code = APPLICATION;


			// Get descriptor.
			read_until(stream_ptr, fin_buffer_ptr, STREAM_BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Add the descriptor.
			if (add_metadata_descriptor(metadata_ptr, fin_buffer_ptr))
			{
				// Alert.
				printf("\n\n\
					ERROR READING DESCRIPTOR:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					fin_buffer_ptr, APPLICATION_CODE
				);


				// Abort.
				return 1;
			}


			// Get cycles.
			read_until(stream_ptr, fin_buffer_ptr, STREAM_BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles.
			metadata_ptr->cycles = atoi(fin_buffer_ptr);


			// Done.
			return 0;
		

		// Process?
		case PROCESS_CODE:
			// Add code.
			metadata_ptr->code = PROCESS;


			// Get descriptor.
			read_until(stream_ptr, fin_buffer_ptr, STREAM_BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Add the descriptor.
			if (add_metadata_descriptor(metadata_ptr, fin_buffer_ptr))
			{
				// Alert.
				printf("\n\n\
					ERROR READING DESCRIPTOR:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					fin_buffer_ptr, PROCESS_CODE
				);


				// Abort.
				return 1;
			}


			// Get cycles.
			read_until(stream_ptr, fin_buffer_ptr, STREAM_BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles.
			metadata_ptr->cycles = atoi(fin_buffer_ptr);


			// Done.
			return 0;


		// Input?
		case INPUT_CODE:
			// Add code.
			metadata_ptr->code = INPUT;


			// Get descriptor.
			read_until(stream_ptr, fin_buffer_ptr, STREAM_BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Add the descriptor.
			if (add_metadata_descriptor(metadata_ptr, fin_buffer_ptr))
			{
				// Alert.
				printf("\n\n\
					ERROR READING DESCRIPTOR:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					fin_buffer_ptr, INPUT_CODE
				);


				// Abort.
				return 1;
			}


			// Get cycles.
			read_until(stream_ptr, fin_buffer_ptr, STREAM_BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles.
			metadata_ptr->cycles = atoi(fin_buffer_ptr);


			// Done.
			return 0;


		// Output?
		case OUTPUT_CODE:
			// Add code.
			metadata_ptr->code = OUTPUT;


			// Get descriptor.
			read_until(stream_ptr, fin_buffer_ptr, STREAM_BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Add the descriptor.
			if (add_metadata_descriptor(metadata_ptr, fin_buffer_ptr))
			{
				// Alert.
				printf("\n\n\
					ERROR READING DESCRIPTOR:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					fin_buffer_ptr, OUTPUT_CODE
				);


				// Abort.
				return 1;
			}


			// Get cycles.
			read_until(stream_ptr, fin_buffer_ptr, STREAM_BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles.
			metadata_ptr->cycles = atoi(fin_buffer_ptr);


			// Done.
			return 0;
		

		// Memory?
		case MEMORY_CODE:
			// Add code.
			metadata_ptr->code = MEMORY;


			// Get descriptor.
			read_until(stream_ptr, fin_buffer_ptr, STREAM_BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Add the descriptor.
			if (add_metadata_descriptor(metadata_ptr, fin_buffer_ptr))
			{
				// Alert.
				printf("\n\n\
					ERROR READING DESCRIPTOR:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					fin_buffer_ptr, MEMORY_CODE
				);


				// Abort.
				return 1;
			}


			// Get cycles.
			read_until(stream_ptr, fin_buffer_ptr, STREAM_BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles.
			metadata_ptr->cycles = atoi(fin_buffer_ptr);


			// Done.
			return 0;


		// No match?
		default:
			// Alert.
			printf("\n\n\
				ERROR READING DESCRIPTOR:\n\
				Invalid code \"%c\".\
				\n\n",
				fin_buffer_ptr[0]
			);


			// Abort.
			return 1;
	}
}


// Is valid descriptor for code?
int add_metadata_descriptor(prog_metadata* metadata, char* buffer_ptr)
{
	// Valid descriptor based on code?
	switch (metadata->code)
	{
		// OS or application?
		case OS:
		case APPLICATION:
			// Start?
			if (strcmp(buffer_ptr, START_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = START;
				return 0;
			}


			// End?
			if (strcmp(buffer_ptr, END_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = END;
				return 0;
			}


			// Descriptor DNE.
			return 1;


		// Process?
		case PROCESS:
			// Run?
			if (strcmp(buffer_ptr, RUN_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = RUN;
				return 0;
			}


			// Descriptor DNE.
			return 1;


		// Input?
		case INPUT:
			// HDD?
			if (strcmp(buffer_ptr, HDD_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = HDD;
				return 0;
			}


			// Keyboard?
			if (strcmp(buffer_ptr, KEYBOARD_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = KEYBOARD;
				return 0;
			}


			// Mouse?
			if (strcmp(buffer_ptr, MOUSE_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = MOUSE;
				return 0;
			}
			
			
			// Printer?
			if (strcmp(buffer_ptr, PRINTER_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = PRINTER;
				return 0;
			}


			// Descriptor DNE.
			return 1;


		// Output? 
		case OUTPUT:
			// HDD?
			if (strcmp(buffer_ptr, HDD_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = HDD;
				return 0;
			}


			// Monitor?
			if (strcmp(buffer_ptr, MONITOR_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = MONITOR;
				return 0;
			}
			
			
			// Speaker?
			if (strcmp(buffer_ptr, SPEAKER_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = SPEAKER;
				return 0;
			}


			// Speaker?
			if (strcmp(buffer_ptr, PRINTER_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = PRINTER;
				return 0;
			}


			// Descriptor DNE.
			return 1;


		// Memory?
		case MEMORY:
			// Block?
			if (strcmp(buffer_ptr, BLOCK_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = BLOCK;
				return 0;
			}


			// Allocate?
			if (strcmp(buffer_ptr, ALLOCATE_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = ALLOCATE;
				return 0;
			}


			// Descriptor DNE.
			return 1;
		

		// Default.
		default:
			return 1;
	}
}


// End header guard.
#endif