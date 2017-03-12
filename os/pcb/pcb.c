// Header guard.
#ifndef LIB_OS_PCB_C_
#define LIB_OS_PCB_C_


// Header.
#include "pcb.h"


// Function prototypes.
inline int add_metadata(pcb*, char*, FILE*);
inline int add_metadata_descriptor(prog_metadata*, char*);


// Create.
int create_pcb(pcb* this, char* mdf_file_path)
{
	// Get file stream.
	FILE* stream_ptr = open_file(mdf_file_path, "r");


	// Buffer.
	char* buffer_ptr = malloc(STREAM_BUFFER_SIZE);
	memset(buffer_ptr, '\0', STREAM_BUFFER_SIZE);


	// Clear metadata.
	this->num_metadata = 0;


	// Consume initial, utterly useless, line.
	read_until(stream_ptr, buffer_ptr, STREAM_BUFFER_SIZE, '\n');


	// Read from stream.
	while (read_until(stream_ptr, buffer_ptr, STREAM_BUFFER_SIZE, METADATA_CODE_TERMINATOR) == 0)
	{
		// Map attribute to metadata.
		if (add_metadata(this, buffer_ptr, stream_ptr))
		{
			// Abort.
			close_file(stream_ptr);
			free(buffer_ptr);
			return 1;
		};
	}


	// Checkpoint.
	printf("\n\nConsumed metadata.\n\n");


	// Clean up.
	close_file(stream_ptr);
	free(buffer_ptr);


	// State.
	this->state = CREATED;


	// Success.
	return 0;
}


// Terminate.
int terminate_pcb(pcb* this)
{
	// Was metadata consumed?
	if (this->num_metadata > 0)
	{
		// Clear.
		this->num_metadata = 0;
	}


	// Set state.
	this->state = TERMINATED;


	// Successful.
	return 0;
}


// Get state.
pcb_state get_state(pcb* this)
{
	// Return.
	return this->state;
}


// Get state.
void set_state(pcb* this, pcb_state state)
{
	// Set.
	this->state = state;
}


// Add metadata.
int add_metadata(pcb* this, char* buffer_ptr, FILE* stream_ptr)
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
			read_until(stream_ptr, buffer_ptr, STREAM_BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Add the descriptor.
			if (add_metadata_descriptor(&this->metadata[i], buffer_ptr))
			{
				// Alert.
				printf("\n\n\
					ERROR READING DESCRIPTOR %i:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					i + 1, buffer_ptr, OS_CODE
				);


				// Abort.
				return 1;
			}


			// Get cycles.
			read_until(stream_ptr, buffer_ptr, STREAM_BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles (always 0 for OS start and end).
			this->metadata[i].cycles = 0;


			// Increment number of metadata.
			this->num_metadata++;


			// Done.
			return 0;
		

		// Application?
		case APPLICATION_CODE:
			// Add code.
			this->metadata[i].code = APPLICATION;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, STREAM_BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Add the descriptor.
			if (add_metadata_descriptor(&this ->metadata[i], buffer_ptr))
			{
				// Alert.
				printf("\n\n\
					ERROR READING DESCRIPTOR %i:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					i + 1, buffer_ptr, APPLICATION_CODE
				);


				// Abort.
				return 1;
			}


			// Get cycles.
			read_until(stream_ptr, buffer_ptr, STREAM_BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles.
			this->metadata[i].cycles = atoi(buffer_ptr);


			// Increment number of metadata.
			this->num_metadata++;


			// Done.
			return 0;
		

		// Process?
		case PROCESS_CODE:
			// Add code.
			this->metadata[i].code = PROCESS;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, STREAM_BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Add the descriptor.
			if (add_metadata_descriptor(&this ->metadata[i], buffer_ptr))
			{
				// Alert.
				printf("\n\n\
					ERROR READING DESCRIPTOR %i:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					i + 1, buffer_ptr, PROCESS_CODE
				);


				// Abort.
				return 1;
			}


			// Get cycles.
			read_until(stream_ptr, buffer_ptr, STREAM_BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles.
			this->metadata[i].cycles = atoi(buffer_ptr);


			// Increment number of metadata.
			this->num_metadata++;


			// Done.
			return 0;


		// Input?
		case INPUT_CODE:
			// Add code.
			this->metadata[i].code = INPUT;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, STREAM_BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Add the descriptor.
			if (add_metadata_descriptor(&this->metadata[i], buffer_ptr))
			{
				// Alert.
				printf("\n\n\
					ERROR READING DESCRIPTOR %i:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					i + 1, buffer_ptr, INPUT_CODE
				);


				// Abort.
				return 1;
			}


			// Get cycles.
			read_until(stream_ptr, buffer_ptr, STREAM_BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles.
			this->metadata[i].cycles = atoi(buffer_ptr);


			// Increment number of metadata.
			this->num_metadata++;


			// Done.
			return 0;


		// Output?
		case OUTPUT_CODE:
			// Add code.
			this->metadata[i].code = OUTPUT;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, STREAM_BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Add the descriptor.
			if (add_metadata_descriptor(&this->metadata[i], buffer_ptr))
			{
				// Alert.
				printf("\n\n\
					ERROR READING DESCRIPTOR %i:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					i + 1, buffer_ptr, OUTPUT_CODE
				);


				// Abort.
				return 1;
			}


			// Get cycles.
			read_until(stream_ptr, buffer_ptr, STREAM_BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles.
			this->metadata[i].cycles = atoi(buffer_ptr);


			// Increment number of metadata.
			this->num_metadata++;


			// Done.
			return 0;
		

		// Memory?
		case MEMORY_CODE:
			// Add code.
			this->metadata[i].code = MEMORY;


			// Get descriptor.
			read_until(stream_ptr, buffer_ptr, STREAM_BUFFER_SIZE, METADATA_DESCRIPTOR_TERMINATOR);


			// Add the descriptor.
			if (add_metadata_descriptor(&this ->metadata[i], buffer_ptr))
			{
				// Alert.
				printf("\n\n\
					ERROR READING DESCRIPTOR %i:\n\
					Invalid descriptor \"%s\" for code \"%c\".\
					\n\n",
					i + 1, buffer_ptr, MEMORY_CODE
				);


				// Abort.
				return 1;
			}


			// Get cycles.
			read_until(stream_ptr, buffer_ptr, STREAM_BUFFER_SIZE, METADATA_CYCLES_TERMINATOR);


			// Add cycles.
			this->metadata[i].cycles = atoi(buffer_ptr);


			// Increment number of metadata.
			this->num_metadata++;


			// Done.
			return 0;


		// No match?
		default:
			// Alert.
			printf("\n\n\
				ERROR READING CODE %i:\n\
				Invalid code \"%c\".\
				\n\n",
				i + 1, buffer_ptr[0]
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