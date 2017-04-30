// Header guard.
#ifndef OS_SCHED_C_
#define OS_SCHED_C_


// Header.
#include "sched.h"


// Function declarations.
static inline int round_robin_sched(pcb*, const unsigned int, const os_config*);
static inline int exec_with_quantum(pcb*, const os_config*);
static inline unsigned int get_op_time(os_config*, op*);
static inline void* ms_sleep(void*);
static inline void set_remaining_cycles(op*, unsigned int);


// Start scheduler.
int start_sched(pcb* pcb_tree_ptr, const unsigned int pcb_count, const os_config* config_ptr)
{
    // Not RR? (Only scheduling algorithm implemented.)
    if (config_ptr->cpu_scheduling != RR)
    {
        // Alert.
        printf("\n\nUnsupported scheduling algorithm selected.\n\n");


        // Abort.
        return 1;
    }


    // Quantum not specified?
    if (config_ptr->cpu_quantum == 0)
    {
        // Alert.
        printf("\n\nNo quantum specified for round-robin scheduling.\n\n");


        // Abort.
        return 1;
    }


    // Round-robing.
    round_robin_sched(pcb_tree_ptr, pcb_count, config_ptr);


    // Done.
    return 0;
}


// Round-robin scheduling.
int round_robin_sched(pcb* pcb_tree_ptr, const unsigned int total_pcb_count, const os_config* config_ptr)
{
    // Current PCB index.
	unsigned int current_pcb_index = 0;


	// Total terminated PCBs encountered consecutively.
	unsigned int total_terminated_pcb_count = 0;


	// Circle the PCB tree.
	while (1)
	{
		// PCB at current index not ready for execution?
		while (!(
			pcb_tree_ptr[current_pcb_index % total_pcb_count].state == READY ||
			pcb_tree_ptr[current_pcb_index % total_pcb_count].state == CREATED
		))
		{
			// Terminated?
			if (pcb_tree_ptr[current_pcb_index % total_pcb_count].state == TERMINATED)
			{
				// Increment total terminated.
				total_terminated_pcb_count++;


				// All PCBs terminated?
				if (total_terminated_pcb_count == total_pcb_count)
				{
					// Done.
					return 0;
				}
			}


			// Next PCB.
			current_pcb_index++;
		}


		// Reset total terminated count.
		total_terminated_pcb_count = 0;


		// Execute.
		exec_with_quantum(&pcb_tree_ptr[current_pcb_index], config_ptr);


		// Increment index.
		current_pcb_index++;
	}

    
    // Done.
    return 0;
}


// Execute program.
int exec_with_quantum(pcb* pcb_ptr, const os_config* config_ptr)
{
	// Time to wait (microseconds) and start clock.
	unsigned int op_time_ms = 0;
	unsigned int remaining_time_ms = config_ptr->cpu_quantum * 1000;
	//clock_t start_clock = clock();


	// Thread ID and status.
	pthread_t thread_id = 0;
	//void* thread_status_ptr;


	// Execute operations.
	for (unsigned int i = pcb_ptr->current_op_index; i < pcb_ptr->num_operations; i++)
	{
		// Set PCB state.
		set_state(pcb_ptr, READY);


		/*
		// Log begin operation.
		log_metadata_begin_op(
			os_ptr,
			&metadata_ptr[i],
			(double) (clock() - start_clock) * 1000 / CLOCKS_PER_SEC // Elapsed time.
		);
		*/


		// Get current operation.
		op current_operation = pcb_ptr->operations[pcb_ptr->current_op_index];


		// Calculate operation time and maximum time.
		op_time_ms = get_op_time(config_ptr, &current_operation);


		// Set PCB state.
		set_state(pcb_ptr, RUNNING);


		// I/O?
		if (current_operation.type == OP_INPUT || current_operation.type == OP_OUTPUT)
		{
			// Acquire device from appropriate pool.
			//acquire(&os_ptr->io_manager, metadata_ptr->descriptor);

			
			// Set PCB state.
			set_state(pcb_ptr, WAITING);


			// Thread.
			pthread_create(&thread_id, NULL, ms_sleep, (void*) &op_time_ms);
			//pthread_join(thread_id, &thread_status_ptr);


			// Release control.
			return 0;


			// Release.
			//release(&os_ptr->io_manager, metadata_ptr->descriptor);
		}


		// Sleep time (ms).
		unsigned int sleep_time_ms = op_time_ms;


		// Operation time greater than time remaining?
		if (op_time_ms > remaining_time_ms)
		{
			// Use the remaining time for operation time.
			sleep_time_ms = remaining_time_ms;


			// Save remaining cycles back to operation.
			set_remaining_cycles(&pcb_ptr->operations[pcb_ptr->current_op_index], op_time_ms - remaining_time_ms);
		}


		// CPU?
		else if (sleep_time_ms > 0) {
			// Sleep.
			ms_sleep((void*) &sleep_time_ms);
		}


		// Update remaining time.
		remaining_time_ms = sleep_time_ms;


		// No more remaining time?
		if (remaining_time_ms == 0)
		{
			// Release control.
			return 0;
		}


		/*
		// Log end operation.
		log_metadata_end_op(
			os_ptr,
			&metadata_ptr[i],
			(double) (clock() - start_clock) * 1000 / CLOCKS_PER_SEC // Elapsed time.
		);
		*/
	}


	// Terminate PCB.
	terminate_pcb(pcb_ptr);


	// Success.
	return 0;
}


// Get time (ms) to complete operation.
unsigned int get_op_time(os_config* config_ptr, op* op_ptr)
{
	// Save number of cycles.
	unsigned int num_cycles = op_ptr->cycles_left;


	// Switch on code.
	switch (op_ptr->type)
	{
		// CPU?
		case OP_CPU:
			return config_ptr->processor_period_ms * num_cycles;


		// Memory?
		case OP_MEMORY:
			return config_ptr->memory_period_ms * num_cycles;
		

		// I/O?
		case OP_INPUT:
		case OP_OUTPUT:
			// Depends on device.
			switch (op_ptr->device)
			{
				// HDD?
				case OP_HDD:
					return config_ptr->hdd_period_ms * num_cycles;


				// Keyboard?
				case OP_KEYBOARD:
					return config_ptr->keyboard_period_ms * num_cycles;


				// Mouse?
				case OP_MOUSE:
					return config_ptr->mouse_period_ms * num_cycles;


				// Monitor?
				case OP_MONITOR:
					return config_ptr->monitor_period_ms * num_cycles;


				// Speaker?
				case OP_SPEAKER:
					return config_ptr->speaker_period_ms * num_cycles;


				// Printer?
				case OP_PRINTER:
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


// Set remaining cycles for operation given remaining time.
void set_remaining_cycles(op* op_ptr, unsigned int remaining_time_ms)
{
	// TODO: Implement.
}


// End header guard.
#endif