// Header guard.
#ifndef LIB_OS_PROG_EXEC_C_
#define LIB_OS_PROG_EXEC_C_


// Header.
#include "prog_exec.h"


// Function prototypes.
unsigned int get_op_time(os_config*, prog_metadata*);
void* ms_sleep(void*);


// Execute program.
bool exec(os* os_ptr)
{
	// PCB pointer, log path, and metadata pointer.
	pcb* pcb_ptr = &os_ptr->pcb;
	os_config* config_ptr = &os_ptr->config;
	prog_metadata* metadata_ptr = pcb_ptr->metadata;


	// PCB not yet created?
	if (pcb_ptr->num_metadata == 0)
	{
		// Buffer.
		char* buffer_ptr = malloc(FILE_PATH_BUFFER_SIZE);
		memset(buffer_ptr, '\0', FILE_PATH_BUFFER_SIZE);


		// Get relative metadata file path.
		strcat(buffer_ptr, METADATA_FOLDER_PATH);
		strcat(buffer_ptr, config_ptr->metadata_file_path);


		// Create.
		init(pcb_ptr, buffer_ptr);


		// Free.
		free(buffer_ptr);
	}


	// Time to wait (microseconds) and start clock.
	unsigned int wait_time_ms = 0;
	clock_t start_clock = clock();


	// Thread ID and status.
	pthread_t thread_id = 0;
	void* thread_status_ptr;


	// Calculate all metadata.
	for (unsigned int i = 0; i < pcb_ptr->num_metadata; i++)
	{
		// Set PCB state.
		set_state(pcb_ptr, READY);

		// Log begin operation.
		log_metadata_begin_op(
			config_ptr,
			&metadata_ptr[i],
			(double) (clock() - start_clock) * 1000 / CLOCKS_PER_SEC // Elapsed time.
		);


		// Calculate total time.
		wait_time_ms = get_op_time(&os_ptr->config, &metadata_ptr[i]);


		// Set PCB state.
		set_state(pcb_ptr, RUNNING);


		// I/O?
		if (metadata_ptr->code == INPUT || metadata_ptr->code == OUTPUT)
		{
			// Set PCB state.
			set_state(pcb_ptr, WAITING);


			// Thread / sync.
			pthread_create(&thread_id, NULL, ms_sleep, (void*) &wait_time_ms);
			pthread_join(thread_id, &thread_status_ptr);
		}


		// CPU?
		else if (wait_time_ms > 0) {
			// Sleep.
			ms_sleep((void*) &wait_time_ms);
		}

		// Log end operation.
		log_metadata_end_op(
			config_ptr,
			&metadata_ptr[i],
			(double) (clock() - start_clock) * 1000 / CLOCKS_PER_SEC // Elapsed time.
		);
	}


	// Terminate PCB.
	terminate(pcb_ptr);


	// Success.
	return true;
}


// Get time (ms) to complete operation.
unsigned int get_op_time(os_config* config_ptr, prog_metadata* metadata_ptr)
{
	// Save number of cycles.
	unsigned int num_cycles = metadata_ptr->cycles;


	// Switch on code.
	switch (metadata_ptr->code)
	{
		// Application or process?
		case APPLICATION:
		case PROCESS:
			return config_ptr->processor_period_ms * num_cycles;


		// Memory?
		case MEMORY:
			return config_ptr->memory_period_ms * num_cycles;
		

		// I/O?
		case INPUT:
		case OUTPUT:
			// Depends on device.
			switch (metadata_ptr->descriptor)
			{
				// HDD?
				case HDD:
					return config_ptr->hdd_period_ms * num_cycles;


				// Keyboard?
				case KEYBOARD:
					return config_ptr->keyboard_period_ms * num_cycles;


				// Mouse?
				case MOUSE:
					return config_ptr->mouse_period_ms * num_cycles;


				// Monitor?
				case MONITOR:
					return config_ptr->monitor_period_ms * num_cycles;


				// Speaker?
				case SPEAKER:
					return config_ptr->speaker_period_ms * num_cycles;


				// Printer?
				case PRINTER:
					return config_ptr->printer_period_ms * num_cycles;


				// Default.
				default:
					return num_cycles;
			}


		// Default.
		default:
			return num_cycles;
	}
}


// Sleep for ms.
void* ms_sleep(void* arg_ptr)
{
	// Unwrap.
	unsigned int* ms_ptr = (unsigned int*) arg_ptr;


	// Sleep.
	usleep(*ms_ptr);


	// Done.
	return NULL;
}


// End header guard.
#endif