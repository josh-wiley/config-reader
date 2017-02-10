// Header guard.
#ifndef LIB_LOGGER_C_
#define LIB_LOGGER_C_


// Headers.
#include "logger.h"


// Function prototypes.
bool log_to_file(os_config*, unsigned int*);
bool log_to_display(os_config*, unsigned int*);
bool compute_metadata_metrics(os_config*, int*);


// Log OS config.
bool log_config(os_config* config_ptr)
{
	// Variables.
	bool was_successful = false;
	unsigned int* cycles_per_metadata_ptr = NULL;


	// Get the log destination.
	switch (config_ptr->log_dest)
	{
		// Both?
		case TO_BOTH:
			// Cycles per metadata item.
			cycles_per_metadata_ptr = malloc(config_ptr->num_metadata * sizeof(unsigned int));


			// Compute metrics and log, store result.
			was_successful = compute_metadata_metrics(config_ptr, cycles_per_metadata_ptr) && log_to_file(config_ptr, cycles_per_metadata_ptr) && log_to_display(config_ptr, cycles_per_metadata_ptr);
			
			
			// Done.
			break;
		

		// Log to file.
		case TO_FILE:
			// Cycles per metadata item.
			cycles_per_metadata_ptr = malloc(config_ptr->num_metadata * sizeof(unsigned int));


			// Compute metrics and log, store result.
			was_successful = compute_metadata_metrics(config_ptr, cycles_per_metadata_ptr) && log_to_file(config_ptr, cycles_per_metadata_ptr);
			
			
			// Done.
			break;
		

		// Log to display.
		case TO_DISPLAY:
			// Cycles per metadata item.
			cycles_per_metadata_ptr = malloc(config_ptr->num_metadata);
			memset(cycles_per_metadata_ptr, 0, config_ptr->num_metadata);


			// Compute metrics and log, store result.
			was_successful = compute_metadata_metrics(config_ptr, cycles_per_metadata_ptr) && log_to_display(config_ptr, cycles_per_metadata_ptr);
			
			
			// Done.
			break;
		

		// Default.
		default:
			was_successful = false;
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


// Log to file.
bool log_to_file(os_config* config_ptr, unsigned int* cycles_ptr)
{
	// Get stream.
	FILE* file_ptr = open_file(config_ptr->log_file_path, "w");

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
	unsigned int total = config_ptr->num_metadata;
	os_metadata metadata;

	
	// Log metadata metrics.
	for (unsigned int i = 0; i < total; i++) 
	{
		// Save.
		metadata = config_ptr->metadata[i];


		// Display.
		fprintf(
			file_ptr,
			"\n%c(%s)%u - %u %s",
			get_code(&metadata), get_descriptor(&metadata), metadata.cycles,
			cycles_ptr[i], METADATA_CYCLE_UNITS
		);
	}


	// Success.
	return true;
}


// Log to display.
bool log_to_display(os_config* config_ptr, unsigned int* cycles_ptr)
{
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
	unsigned int total = config_ptr->num_metadata;
	os_metadata metadata;

	
	// Log metadata metrics.
	for (unsigned int i = 0; i < total; i++) 
	{
		// Save.
		metadata = config_ptr->metadata[i];


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
	return true;
}


// Compute metadata metrics.
bool compute_metadata_metrics(os_config* config_ptr, unsigned int* cycles_ptr)
{
	// Variables.
	unsigned int max = config_ptr->num_metadata;


	// Cycles per metadata.
	for (unsigned int i = 0; i < max-1; i++)
	{
		// Descriptor?
		switch (config_ptr->metadata[i].descriptor)
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
				cycles_ptr[i] = config_ptr->metadata[i].cycles * config_ptr->processor_period_ms;
				break;


			// Allocate or block?
			case ALLOCATE:
			case BLOCK:
				// Memory.
				cycles_ptr[i] = config_ptr->metadata[i].cycles * config_ptr->memory_period_ms;
				break;


			// HDD?
			case HDD:
				// HDD.
				cycles_ptr[i] = config_ptr->metadata[i].cycles * config_ptr->hdd_period_ms;
				break;


			// Keyboard?
			case KEYBOARD:
				// Keyboard.
				cycles_ptr[i] = config_ptr->metadata[i].cycles * config_ptr->keyboard_period_ms;
				break;


			// Mouse?
			case MOUSE:
				// Mouse.
				cycles_ptr[i] = config_ptr->metadata[i].cycles * config_ptr->mouse_period_ms;
				break;
			

			// Monitor?
			case MONITOR:
				// Monitor.
				cycles_ptr[i] =  config_ptr->metadata[i].cycles * config_ptr->monitor_period_ms;
				break;


			// Speaker?
			case SPEAKER:
				// Speaker.
				cycles_ptr[i] = config_ptr->metadata[i].cycles * config_ptr->speaker_period_ms;
				break;


			// Printer?
			case PRINTER:
				// Printer.
				cycles_ptr[i] = config_ptr->metadata[i].cycles * config_ptr->printer_period_ms;
				break;


			// Default.
			default:
				// Abort.
				printf("\n\n\
					ERROR COMPUTING TIME FOR METATADATA %u\
					\n\n", i + 1
				);
				return false;
		}
	}


	// Success.
	return true;
}


// End header guard.
#endif