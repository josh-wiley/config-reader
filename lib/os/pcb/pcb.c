// Header guard.
#ifndef LIB_OS_PCB_C_
#define LIB_OS_PCB_C_


// Header.
#include "pcb.h"


// Function prototypes.
bool consume_metadata(os_config*);
bool add_metadata(os_config*, char*, FILE*);
bool add_metadata_descriptor(prog_metadata*, char*);


// Initialize.
bool init(pcb* this, char* mdf_file_path)
{
	// Get file stream.
	FILE* stream_ptr = open_file(mdf_file_path, "r");


	// Buffer.
	char* buffer_ptr = malloc(BUFFER_SIZE);
	memset(buffer_ptr, '\0', BUFFER_SIZE);


	// Clear metadata.
	this->num_metadata = 0;


	// Consume initial, utterly useless, line.
	read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, '\n');


	// Read from stream.
	while (read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_CODE_TERMINATOR))
	{
		// Try to map attribute to metadata.
		if (!add_metadata(this, buffer_ptr, stream_ptr))
		{
			// Abort.
			close_file(stream_ptr);
			free(buffer_ptr);
			return false;
		};
	}


	// Checkpoint.
	printf("\n\nConsumed metadata.\n\n");


	// Clean up.
	close_file(stream_ptr);
	free(buffer_ptr);


	// Success.
	return true;
}


// Terminate.
bool terminate(pcb* this)
{
	// Was metadata consumed?
	if (this->num_metadata > 0)
	{
		// Clear.
		free(this->metadata);
		this->num_metadata = 0;
	}


	// Set state.
	this->state = TERMINATED;
}


// Get state.
pcb_state get_state(pcb* this)
{
	// Return.
	return this->state;
}


// Add metadata.
bool add_metadata(pcb* this, char* buffer_ptr, FILE* stream_ptr)
{
	// Save current metadata position.
	unsigned int i = this->num_metadata;


	// Match first character to metadata code.
	switch (buffer_ptr[0])
	{
		// OS?
		case OS_CODE:
			// Add code.
			this->metadata[i].code = OS;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Try to add the descriptor.
			if (!add_metadata_descriptor(&config_ptr->metadata[i], buffer_ptr))
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


			// Add cycles (always 0 for OS start and end).
			this->metadata[i].cycles = 0;


			// Increment number of metadata.
			this->num_metadata++;


			// Done.
			return true;
		

		// Application?
		case APPLICATION_CODE:
			// Add code.
			this->metadata[i].code = APPLICATION;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Try to add the descriptor.
			if (!add_metadata_descriptor(&config_ptr->metadata[i], buffer_ptr))
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
			this->metadata[i].cycles = atoi(buffer_ptr);


			// Increment number of metadata.
			this->num_metadata++;


			// Done.
			return true;
		

		// Process?
		case PROCESS_CODE:
			// Add code.
			this->metadata[i].code = PROCESS;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Try to add the descriptor.
			if (!add_metadata_descriptor(&config_ptr->metadata[i], buffer_ptr))
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
			this->metadata[i].cycles = atoi(buffer_ptr);


			// Increment number of metadata.
			this->num_metadata++;


			// Done.
			return true;


		// Input?
		case INPUT_CODE:
			// Add code.
			this->metadata[i].code = INPUT;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Try to add the descriptor.
			if (!add_metadata_descriptor(&this->metadata[i], buffer_ptr))
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
			this->metadata[i].cycles = atoi(buffer_ptr);


			// Increment number of metadata.
			this->num_metadata++;


			// Done.
			return true;


		// Output?
		case OUTPUT_CODE:
			// Add code.
			this->metadata[i].code = OUTPUT;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Try to add the descriptor.
			if (!add_metadata_descriptor(&this->metadata[i], buffer_ptr))
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
			this->metadata[i].cycles = atoi(buffer_ptr);


			// Increment number of metadata.
			this->num_metadata++;


			// Done.
			return true;
		

		// Memory?
		case MEMORY_CODE:
			// Add code.
			this->metadata[i].code = MEMORY;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Try to add the descriptor.
			if (!add_metadata_descriptor(&config_ptr->metadata[i], buffer_ptr))
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
			this->metadata[i].cycles = atoi(buffer_ptr);


			// Increment number of metadata.
			this->num_metadata++;


			// Done.
			return true;


		// No match?
		default:
			// Abort.
			printf("\n\n\
				ERROR READING CODE %i:\n\
				Invalid code \"%c\".\
				\n\n",
				i + 1, buffer_ptr[0]
			);
			return false;
	}
}


// Is valid descriptor for code?
bool add_metadata_descriptor(prog_metadata* metadata, char* buffer_ptr)
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
				return true;
			}


			// End?
			if (strcmp(buffer_ptr, END_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = END;
				return true;
			}


			// Descriptor DNE.
			return false;


		// Process?
		case PROCESS:
			// Run?
			if (strcmp(buffer_ptr, RUN_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = RUN;
				return true;
			}


			// Descriptor DNE.
			return false;


		// Input?
		case INPUT:
			// HDD?
			if (strcmp(buffer_ptr, HDD_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = HDD;
				return true;
			}


			// Keyboard?
			if (strcmp(buffer_ptr, KEYBOARD_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = KEYBOARD;
				return true;
			}


			// Mouse?
			if (strcmp(buffer_ptr, MOUSE_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = MOUSE;
				return true;
			}
			
			
			// Printer?
			if (strcmp(buffer_ptr, PRINTER_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = PRINTER;
				return true;
			}


			// Descriptor DNE.
			return false;


		// Output? 
		case OUTPUT:
			// HDD?
			if (strcmp(buffer_ptr, HDD_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = HDD;
				return true;
			}


			// Monitor?
			if (strcmp(buffer_ptr, MONITOR_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = MONITOR;
				return true;
			}
			
			
			// Speaker?
			if (strcmp(buffer_ptr, SPEAKER_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = SPEAKER;
				return true;
			}


			// Speaker?
			if (strcmp(buffer_ptr, PRINTER_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = PRINTER;
				return true;
			}


			// Descriptor DNE.
			return false;


		// Memory?
		case MEMORY:
			// Block?
			if (strcmp(buffer_ptr, BLOCK_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = BLOCK;
				return true;
			}


			// Allocate?
			if (strcmp(buffer_ptr, ALLOCATE_DESCRIPTOR) == 0)
			{
				// Add.
				metadata->descriptor = ALLOCATE;
				return true;
			}


			// Descriptor DNE.
			return false;
		

		// Default.
		default:
			return false;
	}
}


// End header guard.
#endif