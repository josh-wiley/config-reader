// Header guard.
#ifndef LIB_OS_PROG_EXEC_C_
#define LIB_OS_PROG_EXEC_C_


// Header.
#include "prog_exec.h"


// Function prototypes.
unsigned int get_op_time(os_config*, prog_metadata*);


// Execute program.
bool exec(os* os_ptr)
{
	// PCB pointer, log path, and metadata pointer.
	pcb* pcb_ptr = &os_ptr->pcb;
	char* log_path = os_ptr->config.log_file_path;
	prog_metadata* metadata_ptr = pcb_ptr->metadata;


	// PCB not yet created?
	if (pcb_ptr->num_metadata == 0)
	{
		// Buffer.
		char* buffer_ptr = malloc(BUFFER_SIZE);
		memset(buffer_ptr, '\0', BUFFER_SIZE);


		// Get relative metadata file path.
		strcat(buffer_ptr, METADATA_FOLDER_PATH);
		strcat(buffer_ptr, config_ptr->metadata_file_path);


		// Create.
		init(pcb_ptr, buffer_ptr);


		// Free.
		free(buffer_ptr);
	}


	// Time to wait (microseconds) and start clock.
	usec u_wait_time = 0;
	clock_t start_clock = clock();


	// Thread ID and status.
	int thread_id, thread_status;


	// Calculate all metadata.
	for (unsigned int i = 0; i < config_ptr->num_metadata; i++)
	{
		// Set PCB state.
		set_state(pcb_ptr, READY);


		// Log begin operation.
		log_metadata_begin_op(
			log_path,
			&metadata_ptr[i],
			(double) (clock() - start_clock) * 1000 / CLOCKS_PER_SEC // Elapsed time.
		);


		// Calculate total time.
		u_wait_time = get_op_time(config_ptr, &metadata_ptr[i]);


		// Set PCB state.
		set_state(pcb_ptr, RUNNING);


		// I/O?
		if (metadata_ptr->code == INPUT || metadata_ptr->code == OUTPUT)
		{
			// Set PCB state.
			set_state(pcb_ptr, WAITING);


			// Thread / sync.
			pthread_create(&thread_id, NULL, usleep, u_wait_time)
			pthread_join(thread_id, &thread_status)
		}


		// CPU.
		else {
			// Sleep.
			usleep(u_wait_time);
		}


		// Log end operation.
		log_metadata_end_op(
			log_path,
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
unsigned int get_op_multiplier(os_config*, prog_metadata*)
{}


// End header guard.
#endif