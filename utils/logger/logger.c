// Header guard.
#ifndef LIB_LOGGER_C_
#define LIB_LOGGER_C_


// Headers.
#include "logger.h"


// Function prototypes.
inline int log_os_to_file(os*, unsigned int*);
inline int log_os_to_display(os*, unsigned int*);
inline int log_metadata_begin_op_to_file(FILE*, os*, prog_metadata*, double);
inline int log_metadata_end_op_to_file(FILE*, os*, prog_metadata*, double);
inline int log_metadata_begin_op_to_display(os*, prog_metadata*, double);
inline int log_metadata_end_op_to_display(os*, prog_metadata*, double);
inline int compute_metadata_metrics(os*, unsigned int*);


// Log OS.
int log_os(os* os_ptr)
{
	// Variables.
	int was_successful = 1;
	unsigned int* cycles_per_metadata_ptr = NULL;


	// Get the log destination.
	switch (os_ptr->config.log_dest)
	{
		// Both?
		case TO_BOTH:
			// Cycles per metadata item.
			cycles_per_metadata_ptr = malloc(os_ptr->pcb.num_metadata * sizeof(unsigned int));


			// Compute metrics and log, store result.
			was_successful = compute_metadata_metrics(os_ptr, cycles_per_metadata_ptr) && log_os_to_file(os_ptr, cycles_per_metadata_ptr) && log_os_to_display(os_ptr, cycles_per_metadata_ptr);
			
			
			// Done.
			break;
		

		// Log to file.
		case TO_FILE:
			// Cycles per metadata item.
			cycles_per_metadata_ptr = malloc(os_ptr->pcb.num_metadata * sizeof(unsigned int));


			// Compute metrics and log, store result.
			was_successful = compute_metadata_metrics(os_ptr, cycles_per_metadata_ptr) && log_os_to_file(os_ptr, cycles_per_metadata_ptr);
			
			
			// Done.
			break;
		

		// Log to display.
		case TO_DISPLAY:
			// Cycles per metadata item.
			cycles_per_metadata_ptr = malloc(os_ptr->pcb.num_metadata);
			memset(cycles_per_metadata_ptr, 0, os_ptr->pcb.num_metadata);


			// Compute metrics and log, store result.
			was_successful = compute_metadata_metrics(os_ptr, cycles_per_metadata_ptr) && log_os_to_display(os_ptr, cycles_per_metadata_ptr);
			
			
			// Done.
			break;
		

		// Default.
		default:
			was_successful = 1;
	}


	// Pointer?
	if (cycles_per_metadata_ptr)
	{
		// Free.
		free(cycles_per_metadata_ptr);
	}


	// Return.
	return was_successful;
}


// Log metadata begin operation.
int log_metadata_begin_op(os* os_ptr, prog_metadata* metadata_ptr, double elapsed_time)
{
	// Convenience.
	os_config* config_ptr = &os_ptr->config;


	// Declare stream pointer.
	FILE* stream_ptr;


	// Switch on log destination.
	switch (config_ptr->log_dest)
	{
		// Both?
		case TO_BOTH:
			// Get stream.
			stream_ptr = open_file(config_ptr->log_file_path, "w");


			// Log to both.
			return log_metadata_begin_op_to_display(os_ptr, metadata_ptr, elapsed_time) == 0 &&
				log_metadata_begin_op_to_file(stream_ptr, os_ptr, metadata_ptr, elapsed_time) == 0;
		

		// Log to file.
		case TO_FILE:
			// Get stream.
			stream_ptr = open_file(config_ptr->log_file_path, "w");


			// Log to file.
			return log_metadata_begin_op_to_file(stream_ptr, os_ptr, metadata_ptr, elapsed_time);
		

		// Log to display.
		case TO_DISPLAY:
			// Log to display.
			return log_metadata_begin_op_to_display(os_ptr, metadata_ptr, elapsed_time);
		

		// Default.
		default:
			// Abort.
			printf("\n\nInvalid log destination in OS config.\n\n");
			return 1;
	}
}


// Log metadata end operation.
int log_metadata_end_op(os* os_ptr, prog_metadata* metadata_ptr, double elapsed_time)
{
	// Declare stream pointer.
	FILE* stream_ptr;


	// Switch on log destination.
	switch (os_ptr->config.log_dest)
	{
		// Both?
		case TO_BOTH:
			// Get stream.
			stream_ptr = open_file(os_ptr->config.log_file_path, "w");


			// Log to both.
			return log_metadata_end_op_to_display(os_ptr, metadata_ptr, elapsed_time) &&
				log_metadata_end_op_to_file(stream_ptr, os_ptr, metadata_ptr, elapsed_time);
		

		// Log to file.
		case TO_FILE:
			// Get stream.
			stream_ptr = open_file(os_ptr->config.log_file_path, "w");


			// Log to file.
			return log_metadata_end_op_to_file(stream_ptr, os_ptr, metadata_ptr, elapsed_time);
		

		// Log to display.
		case TO_DISPLAY:
			// Log to display.
			return log_metadata_end_op_to_display(os_ptr, metadata_ptr, elapsed_time);
		

		// Default.
		default:
			// Abort.
			printf("\n\nInvalid log destination in OS config.\n\n");
			return 1;
	}
}


// Log to file.
int log_os_to_file(os* os_ptr, unsigned int* cycles_ptr)
{
	// Convenience.
	os_config* config_ptr = &os_ptr->config;


	// Get stream.
	FILE* file_ptr = open_file(config_ptr->log_file_path, "w");


	// File stream not obtained?
	if (!file_ptr)
	{
		// Abort.
		return 1;
	}


	// Config.
	fprintf(file_ptr,
		"\n\n\
		%s\n\
		%s %u %s\n\
		%s %u %s\n\
		%s %u %s\n\
		%s %u %s\n\
		%s %u %s\n\
		%s %u %s\n\
		%s %u %s\n\
		%s %u %s\n\
		\n\n\
		%s",
		CONFIG_LOG_START,
		CONFIG_PROCESSOR_LABEL, config_ptr->processor_period_ms, CONFIG_CYCLE_UNITS,
		CONFIG_PROCESSOR_LABEL, config_ptr->memory_period_ms, CONFIG_CYCLE_UNITS,
		CONFIG_HDD_LABEL, config_ptr->hdd_period_ms, CONFIG_CYCLE_UNITS,
		CONFIG_KEYBOARD_LABEL, config_ptr->keyboard_period_ms, CONFIG_CYCLE_UNITS,
		CONFIG_MOUSE_LABEL, config_ptr->mouse_period_ms, CONFIG_CYCLE_UNITS,
		CONFIG_SPEAKER_LABEL, config_ptr->speaker_period_ms, CONFIG_CYCLE_UNITS,
		CONFIG_PRINTER_LABEL, config_ptr->printer_period_ms, CONFIG_CYCLE_UNITS,
		CONFIG_MEMORY_LABEL, config_ptr->memory_period_ms, CONFIG_CYCLE_UNITS,
		METADATA_LOG_START
	);


	// Variables.
	prog_metadata* metadata_ptr = os_ptr->pcb.metadata;
	unsigned int total = os_ptr->pcb.num_metadata;
	prog_metadata metadata;

	
	// Log metadata metrics.
	for (unsigned int i = 0; i < total; i++) 
	{
		// Save.
		metadata = metadata_ptr[i];


		// Display.
		fprintf(
			file_ptr,
			"\n%c(%s)%u - %u %s",
			get_code(&metadata), get_descriptor(&metadata), metadata.cycles,
			cycles_ptr[i], METADATA_CYCLE_UNITS
		);
	}


	// Success.
	return 0;
}



// Log to display.
int log_os_to_display(os* os_ptr, unsigned int* cycles_ptr)
{
	// Convenience.
	os_config* config_ptr = &os_ptr->config;


	// Config.
	printf(
		"\n\n\
		%s\n\
		%s %u %s\n\
		%s %u %s\n\
		%s %u %s\n\
		%s %u %s\n\
		%s %u %s\n\
		%s %u %s\n\
		%s %u %s\n\
		%s %u %s\n\
		\n\n\
		%s",
		CONFIG_LOG_START,
		CONFIG_PROCESSOR_LABEL, config_ptr->processor_period_ms, CONFIG_CYCLE_UNITS,
		CONFIG_PROCESSOR_LABEL, config_ptr->memory_period_ms, CONFIG_CYCLE_UNITS,
		CONFIG_HDD_LABEL, config_ptr->hdd_period_ms, CONFIG_CYCLE_UNITS,
		CONFIG_KEYBOARD_LABEL, config_ptr->keyboard_period_ms, CONFIG_CYCLE_UNITS,
		CONFIG_MOUSE_LABEL, config_ptr->mouse_period_ms, CONFIG_CYCLE_UNITS,
		CONFIG_SPEAKER_LABEL, config_ptr->speaker_period_ms, CONFIG_CYCLE_UNITS,
		CONFIG_PRINTER_LABEL, config_ptr->printer_period_ms, CONFIG_CYCLE_UNITS,
		CONFIG_MEMORY_LABEL, config_ptr->memory_period_ms, CONFIG_CYCLE_UNITS,
		METADATA_LOG_START
	);


	// Variables.
	prog_metadata* metadata_ptr = os_ptr->pcb.metadata;
	unsigned int total = os_ptr->pcb.num_metadata;
	prog_metadata metadata;

	
	// Log metadata metrics.
	for (unsigned int i = 0; i < total; i++) 
	{
		// Save.
		metadata = metadata_ptr[i];


		// Display.
		printf(
			"\n%c(%s)%u - %u %s",
			get_code(&metadata), get_descriptor(&metadata), metadata.cycles,
			cycles_ptr[i], METADATA_CYCLE_UNITS
		);
	}


	// Done.
	printf("\n\n");


	// Success.
	return 0;
}


// Log metadata begin operation to file.
int log_metadata_begin_op_to_file(FILE* file_ptr, os* os_ptr, prog_metadata* metadata_ptr, double elapsed_time)
{
	// Switch on op code.
	switch (metadata_ptr->code)
	{
		// OS.
		case OS:
			// Switch on descriptor.
			switch (metadata_ptr->descriptor)
			{
				// Start.
				case START:
					fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, OS_START_OP_BEGIN_MESSAGE);
					return 0;


				// End.
				case END:
					fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, OS_END_OP_BEGIN_MESSAGE);
					return 0;

				
				// Default.
				default:
					// Abort.
					printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
					return 1;
			}


		// Application.
		case APPLICATION:
			// Switch on descriptor.
			switch (metadata_ptr->descriptor)
			{
				// Start.
				case START:
					fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, APPLICATION_START_OP_BEGIN_MESSAGE);
					return 0;


				// End.
				case END:
					fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, APPLICATION_END_OP_BEGIN_MESSAGE);
					return 0;

				
				// Default.
				default:
					// Abort.
					printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
					return 1;
			}
		

		// Process.
		case PROCESS:
			// Run?
			if (metadata_ptr->descriptor == RUN)
			{
				// Log.
				fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, PROCESS_RUN_OP_BEGIN_MESSAGE);
				return 0;
			}


			// Abort.
			printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
			return 1;
		

		// Memory.
		case MEMORY:
			// Switch on descriptor.
			switch (metadata_ptr->descriptor)
			{
				// Allocate.
				case ALLOCATE:
					fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, MEMORY_ALLOCATE_OP_BEGIN_MESSAGE);
					return 0;


				// Block.
				case BLOCK:
					fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, MEMORY_BLOCK_OP_BEGIN_MESSAGE);
					return 0;

				
				// Default.
				default:
					// Abort.
					printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
					return 1;
			}
			

		// Default.
		default:
			// Switch on descriptor.
			switch (metadata_ptr->descriptor)
			{
				// HDD.
				case HDD:
					// Switch on code.
					switch (metadata_ptr->code)
					{
						// Input.
						case INPUT:
							// Write.
							fprintf(
								file_ptr,
								"\n\n%f - %s %u\n\n",
								elapsed_time,
								INPUT_HDD_OP_BEGIN_MESSAGE,
								os_ptr->config.total_hdds - get_available(&os_ptr->io_manager, HDD) + 1
							);


							// Done.
							return 0;


						// Output.
						case OUTPUT:
							// Write.
							fprintf(
								file_ptr, "\n\n%f - %s %u\n\n",
								elapsed_time,
								OUTPUT_HDD_OP_BEGIN_MESSAGE,
								os_ptr->config.total_hdds - get_available(&os_ptr->io_manager, HDD) + 1
							);


							// Done.
							return 0;


						// Default.
						default:
							// Abort.
							printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
							return 1;
					}
				

				// Keyboard.
				case KEYBOARD:
					// Input?
					if (metadata_ptr->code == INPUT)
					{
						// Write.
						fprintf(
							file_ptr,
							"\n\n%f - %s %u\n\n",
							elapsed_time,
							INPUT_KEYBOARD_OP_BEGIN_MESSAGE,
							os_ptr->config.total_keyboards - get_available(&os_ptr->io_manager, KEYBOARD) + 1
						);


						// Done.
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;
				
				
				// Mouse.
				case MOUSE:
					// Input?
					if (metadata_ptr->code == INPUT)
					{
						// Write.
						fprintf(
							file_ptr,
							"\n\n%f - %s %u\n\n",
							elapsed_time,
							INPUT_MOUSE_OP_BEGIN_MESSAGE,
							os_ptr->config.total_mice - get_available(&os_ptr->io_manager, MOUSE) + 1
						);
						

						// Done.
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;
				
				
				// Monitor.
				case MONITOR:
					// Output?
					if (metadata_ptr->code == OUTPUT)
					{
						// Write.
						fprintf(
							file_ptr,
							"\n\n%f - %s %u\n\n",
							elapsed_time,
							OUTPUT_MONITOR_OP_BEGIN_MESSAGE,
							os_ptr->config.total_monitors - get_available(&os_ptr->io_manager, MONITOR) + 1
						);
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;
				
				
				// Speaker.
				case SPEAKER:
					// Output?
					if (metadata_ptr->code == OUTPUT)
					{
						// Write.
						fprintf(
							file_ptr,
							"\n\n%f - %s %u\n\n",
							elapsed_time,
							OUTPUT_SPEAKER_OP_BEGIN_MESSAGE,
							os_ptr->config.total_speakers - get_available(&os_ptr->io_manager, SPEAKER) + 1
						);
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;


				// Printer.
				case PRINTER:
					// Output?
					if (metadata_ptr->code == OUTPUT)
					{
						// Write.
						fprintf(
							file_ptr,
							"\n\n%f - %s %u\n\n",
							elapsed_time,
							OUTPUT_PRINTER_OP_BEGIN_MESSAGE,
							os_ptr->config.total_printers - get_available(&os_ptr->io_manager, PRINTER) + 1
						);
						
						
						// Done.
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;


				// Default.
				default:
					// Abort.
					printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
					return 1;
			}
	}
}


// Log metadata end operation to file.
int log_metadata_end_op_to_file(FILE* file_ptr, os* os_ptr, prog_metadata* metadata_ptr, double elapsed_time)
{
	// Switch on op code.
	switch (metadata_ptr->code)
	{
		// OS.
		case OS:
			// Switch on descriptor.
			switch (metadata_ptr->descriptor)
			{
				// Start or end?.
				case START:
				case END:
					return 0;

				
				// Default.
				default:
					// Abort.
					printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
					return 1;
			}


		// Application.
		case APPLICATION:
			// Switch on descriptor.
			switch (metadata_ptr->descriptor)
			{
				// Start.
				case START:
					fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, APPLICATION_START_OP_END_MESSAGE);
					return 0;


				// End.
				case END:
					return 0;

				
				// Default.
				default:
					// Abort.
					printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
					return 1;
			}
		

		// Process.
		case PROCESS:
			// Run?
			if (metadata_ptr->descriptor == RUN)
			{
				// Log.
				fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, PROCESS_RUN_OP_END_MESSAGE);
				return 0;
			}


			// Abort.
			printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
			return 1;
		

		// Memory.
		case MEMORY:
			// Switch on descriptor.
			switch (metadata_ptr->descriptor)
			{
				// Allocate.
				case ALLOCATE:
					fprintf(
						file_ptr,
						"\n\n%f - %s 0x%08x\n\n",
						elapsed_time,
						MEMORY_ALLOCATE_OP_END_MESSAGE,
						alloc_mem(&os_ptr->memory_manager)
					);
					return 0;


				// Block.
				case BLOCK:
					fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, MEMORY_BLOCK_OP_END_MESSAGE);
					return 0;

				
				// Default.
				default:
					// Abort.
					printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
					return 1;
			}
			

		// Default.
		default:
			// Switch on descriptor.
			switch (metadata_ptr->descriptor)
			{
				// HDD.
				case HDD:
					// Switch on code.
					switch (metadata_ptr->code)
					{
						// Input.
						case INPUT:
							fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, INPUT_HDD_OP_END_MESSAGE);
							return 0;


						// Output.
						case OUTPUT:
							fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, OUTPUT_HDD_OP_END_MESSAGE);
							return 0;


						// Default.
						default:
							// Abort.
							printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
							return 1;
					}
				

				// Keyboard.
				case KEYBOARD:
					// Input?
					if (metadata_ptr->code == INPUT)
					{
						// Log.
						fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, INPUT_KEYBOARD_OP_END_MESSAGE);
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;
				
				
				// Mouse.
				case MOUSE:
					// Input?
					if (metadata_ptr->code == INPUT)
					{
						// Log.
						fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, INPUT_MOUSE_OP_END_MESSAGE);
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;
				
				
				// Monitor.
				case MONITOR:
					// Output?
					if (metadata_ptr->code == OUTPUT)
					{
						// Log.
						fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, OUTPUT_MONITOR_OP_END_MESSAGE);
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;
				
				
				// Speaker.
				case SPEAKER:
					// Output?
					if (metadata_ptr->code == OUTPUT)
					{
						// Log.
						fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, OUTPUT_SPEAKER_OP_END_MESSAGE);
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;


				// Printer.
				case PRINTER:
					// Output?
					if (metadata_ptr->code == OUTPUT)
					{
						// Log.
						fprintf(file_ptr, "\n\n%f - %s\n\n", elapsed_time, OUTPUT_PRINTER_OP_END_MESSAGE);
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;


				// Default.
				default:
					// Abort.
					printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
					return 1;
			}
	}
}


// Log metadata begin operation to display.
int log_metadata_begin_op_to_display(os* os_ptr, prog_metadata* metadata_ptr, double elapsed_time)
{
	// Switch on op code.
	switch (metadata_ptr->code)
	{
		// OS.
		case OS:
			// Switch on descriptor.
			switch (metadata_ptr->descriptor)
			{
				// Start.
				case START:
					printf("\n\n%f - %s\n\n", elapsed_time, OS_START_OP_BEGIN_MESSAGE);
					return 0;


				// End.
				case END:
					printf("\n\n%f - %s\n\n", elapsed_time, OS_END_OP_BEGIN_MESSAGE);
					return 0;

				
				// Default.
				default:
					// Abort.
					printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
					return 1;
			}


		// Application.
		case APPLICATION:
			// Switch on descriptor.
			switch (metadata_ptr->descriptor)
			{
				// Start.
				case START:
					printf("\n\n%f - %s\n\n", elapsed_time, APPLICATION_START_OP_BEGIN_MESSAGE);
					return 0;


				// End.
				case END:
					printf("\n\n%f - %s\n\n", elapsed_time, APPLICATION_END_OP_BEGIN_MESSAGE);
					return 0;

				
				// Default.
				default:
					// Abort.
					printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
					return 1;
			}
		

		// Process.
		case PROCESS:
			// Run?
			if (metadata_ptr->descriptor == RUN)
			{
				// Log.
				printf("\n\n%f - %s\n\n", elapsed_time, PROCESS_RUN_OP_BEGIN_MESSAGE);
				return 0;
			}


			// Abort.
			printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
			return 1;
		

		// Memory.
		case MEMORY:
			// Switch on descriptor.
			switch (metadata_ptr->descriptor)
			{
				// Allocate.
				case ALLOCATE:
					printf("\n\n%f - %s\n\n", elapsed_time, MEMORY_ALLOCATE_OP_BEGIN_MESSAGE);
					return 0;


				// Block.
				case BLOCK:
					printf("\n\n%f - %s\n\n", elapsed_time, MEMORY_BLOCK_OP_BEGIN_MESSAGE);
					return 0;

				
				// Default.
				default:
					// Abort.
					printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
					return 1;
			}
			

		// Default.
		default:
			// Switch on descriptor.
			switch (metadata_ptr->descriptor)
			{
				// HDD.
				case HDD:
					// Switch on code.
					switch (metadata_ptr->code)
					{
						// Input.
						case INPUT:
							// Write.
							printf(
								"\n\n%f - %s %u\n\n",
								elapsed_time,
								INPUT_HDD_OP_BEGIN_MESSAGE,
								os_ptr->config.total_hdds - get_available(&os_ptr->io_manager, HDD) + 1
							);


							// Done.
							return 0;


						// Output.
						case OUTPUT:
							// Write.
							printf(
								"\n\n%f - %s %u\n\n",
								elapsed_time,
								OUTPUT_HDD_OP_BEGIN_MESSAGE,
								os_ptr->config.total_hdds - get_available(&os_ptr->io_manager, HDD) + 1
							);


							// Done.
							return 0;


						// Default.
						default:
							// Abort.
							printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
							return 1;
					}
				

				// Keyboard.
				case KEYBOARD:
					// Input?
					if (metadata_ptr->code == INPUT)
					{
						// Write.
						printf(
							"\n\n%f - %s %u\n\n",
							elapsed_time,
							INPUT_KEYBOARD_OP_BEGIN_MESSAGE,
							os_ptr->config.total_keyboards - get_available(&os_ptr->io_manager, KEYBOARD) + 1
						);


						// Done.
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;
				
				
				// Mouse.
				case MOUSE:
					// Input?
					if (metadata_ptr->code == INPUT)
					{
						// Write.
						printf(
							"\n\n%f - %s %u\n\n",
							elapsed_time,
							INPUT_MOUSE_OP_BEGIN_MESSAGE,
							os_ptr->config.total_mice - get_available(&os_ptr->io_manager, MOUSE) + 1
						);


						// Done.
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;
				
				
				// Monitor.
				case MONITOR:
					// Output?
					if (metadata_ptr->code == OUTPUT)
					{
						// Write.
						printf(
							"\n\n%f - %s %u\n\n",
							elapsed_time,
							OUTPUT_MONITOR_OP_BEGIN_MESSAGE,
							os_ptr->config.total_monitors - get_available(&os_ptr->io_manager, MONITOR) + 1
						);


						// Done.
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;
				
				
				// Speaker.
				case SPEAKER:
					// Output?
					if (metadata_ptr->code == OUTPUT)
					{
						// Write.
						printf(
							"\n\n%f - %s %u\n\n",
							elapsed_time,
							OUTPUT_SPEAKER_OP_BEGIN_MESSAGE,
							os_ptr->config.total_speakers - get_available(&os_ptr->io_manager, SPEAKER) + 1
						);


						// Done.
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;


				// Printer.
				case PRINTER:
					// Output?
					if (metadata_ptr->code == OUTPUT)
					{
						// Write.
						printf(
							"\n\n%f - %s %u\n\n",
							elapsed_time,
							OUTPUT_PRINTER_OP_BEGIN_MESSAGE,
							os_ptr->config.total_printers - get_available(&os_ptr->io_manager, PRINTER) + 1
						);
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;


				// Default.
				default:
					// Abort.
					printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
					return 1;
			}
	}
}


// Log metadata end operation to display.
int log_metadata_end_op_to_display(os* os_ptr, prog_metadata* metadata_ptr, double elapsed_time)
{
	// Switch on op code.
	switch (metadata_ptr->code)
	{
		// OS.
		case OS:
			// Switch on descriptor.
			switch (metadata_ptr->descriptor)
			{
				// Start or end?.
				case START:
				case END:
					return 0;

				
				// Default.
				default:
					// Abort.
					printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
					return 1;
			}


		// Application.
		case APPLICATION:
			// Switch on descriptor.
			switch (metadata_ptr->descriptor)
			{
				// Start.
				case START:
					printf("\n\n%f - %s\n\n", elapsed_time, APPLICATION_START_OP_END_MESSAGE);
					return 0;


				// End.
				case END:
					return 0;

				
				// Default.
				default:
					// Abort.
					printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
					return 1;
			}
		

		// Process.
		case PROCESS:
			// Run?
			if (metadata_ptr->descriptor == RUN)
			{
				// Log.
				printf("\n\n%f - %s\n\n", elapsed_time, PROCESS_RUN_OP_END_MESSAGE);
				return 0;
			}


			// Abort.
			printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
			return 1;
		

		// Memory.
		case MEMORY:
			// Switch on descriptor.
			switch (metadata_ptr->descriptor)
			{
				// Allocate.
				case ALLOCATE:
					printf(
						"\n\n%f - %s 0x%08x\n\n",
						elapsed_time,
						MEMORY_ALLOCATE_OP_END_MESSAGE,
						alloc_mem(&os_ptr->memory_manager)
					);
					return 0;


				// Block.
				case BLOCK:
					printf("\n\n%f - %s\n\n", elapsed_time, MEMORY_BLOCK_OP_END_MESSAGE);
					return 0;

				
				// Default.
				default:
					// Abort.
					printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
					return 1;
			}
			

		// Default.
		default:
			// Switch on descriptor.
			switch (metadata_ptr->descriptor)
			{
				// HDD.
				case HDD:
					// Switch on code.
					switch (metadata_ptr->code)
					{
						// Input.
						case INPUT:
							printf("\n\n%f - %s\n\n", elapsed_time, INPUT_HDD_OP_END_MESSAGE);
							return 0;


						// Output.
						case OUTPUT:
							printf("\n\n%f - %s\n\n", elapsed_time, OUTPUT_HDD_OP_END_MESSAGE);
							return 0;


						// Default.
						default:
							// Abort.
							printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
							return 1;
					}
				

				// Keyboard.
				case KEYBOARD:
					// Input?
					if (metadata_ptr->code == INPUT)
					{
						// Log.
						printf("\n\n%f - %s\n\n", elapsed_time, INPUT_KEYBOARD_OP_END_MESSAGE);
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;
				
				
				// Mouse.
				case MOUSE:
					// Input?
					if (metadata_ptr->code == INPUT)
					{
						// Log.
						printf("\n\n%f - %s\n\n", elapsed_time, INPUT_MOUSE_OP_END_MESSAGE);
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;
				
				
				// Monitor.
				case MONITOR:
					// Output?
					if (metadata_ptr->code == OUTPUT)
					{
						// Log.
						printf("\n\n%f - %s\n\n", elapsed_time, OUTPUT_MONITOR_OP_END_MESSAGE);
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;
				
				
				// Speaker.
				case SPEAKER:
					// Output?
					if (metadata_ptr->code == OUTPUT)
					{
						// Log.
						printf("\n\n%f - %s\n\n", elapsed_time, OUTPUT_SPEAKER_OP_END_MESSAGE);
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;


				// Printer.
				case PRINTER:
					// Output?
					if (metadata_ptr->code == OUTPUT)
					{
						// Log.
						printf("\n\n%f - %s\n\n", elapsed_time, OUTPUT_PRINTER_OP_END_MESSAGE);
						return 0;
					}


					// Abort.
					printf("\n\n%s\n\n", INVALID_CODE_RUNTIME_ERROR_MESSAGE);
					return 1;


				// Default.
				default:
					// Abort.
					printf("\n\n%s\n\n", INVALID_DESCRIPTOR_RUNTIME_ERROR_MESSAGE);
					return 1;
			}
	}
}


// Compute metadata metrics.
int compute_metadata_metrics(os* os_ptr, unsigned int* cycles_ptr)
{
	// Variables.
	unsigned int max = os_ptr->pcb.num_metadata;


	// Cycles per metadata.
	for (unsigned int i = 0; i < max; i++)
	{
		// Descriptor?
		switch (os_ptr->pcb.metadata[i].descriptor)
		{
			// Start or end?
			case START:
			case END:
				// No cycles.
				cycles_ptr[i] = 0;
				break;


			// Run?
			case RUN:
				// Processor.
				cycles_ptr[i] = os_ptr->pcb.metadata[i].cycles * os_ptr->config.processor_period_ms;
				break;


			// Allocate or block?
			case ALLOCATE:
			case BLOCK:
				// Memory.
				cycles_ptr[i] = os_ptr->pcb.metadata[i].cycles * os_ptr->config.memory_period_ms;
				break;


			// HDD?
			case HDD:
				// HDD.
				cycles_ptr[i] = os_ptr->pcb.metadata[i].cycles * os_ptr->config.hdd_period_ms;
				break;


			// Keyboard?
			case KEYBOARD:
				// Keyboard.
				cycles_ptr[i] = os_ptr->pcb.metadata[i].cycles * os_ptr->config.keyboard_period_ms;
				break;


			// Mouse?
			case MOUSE:
				// Mouse.
				cycles_ptr[i] = os_ptr->pcb.metadata[i].cycles * os_ptr->config.mouse_period_ms;
				break;
			

			// Monitor?
			case MONITOR:
				// Monitor.
				cycles_ptr[i] =  os_ptr->pcb.metadata[i].cycles * os_ptr->config.monitor_period_ms;
				break;


			// Speaker?
			case SPEAKER:
				// Speaker.
				cycles_ptr[i] = os_ptr->pcb.metadata[i].cycles * os_ptr->config.speaker_period_ms;
				break;


			// Printer?
			case PRINTER:
				// Printer.
				cycles_ptr[i] = os_ptr->pcb.metadata[i].cycles * os_ptr->config.printer_period_ms;
				break;


			// Default.
			default:
				// Abort.
				printf("\n\n\
					ERROR COMPUTING TIME FOR METATADATA %u\
					\n\n", i + 1
				);
				return 1;
		}
	}


	// Success.
	return 0;
}


// End header guard.
#endif