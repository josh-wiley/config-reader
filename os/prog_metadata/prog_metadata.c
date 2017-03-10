// Header guard.
#ifndef LIB_OS_PROG_METADATA_C_
#define LIB_OS_PROG_METADATA_C_


// Header.
#include "prog_metadata.h"


// Get code.
char get_code(prog_metadata* metadata_ptr)
{
	// Which code?
	switch (metadata_ptr->code)
	{
		// OS.
		case OS: return OS_CODE;
		

		// Application.
		case APPLICATION: return APPLICATION_CODE;
		

		// Process.
		case PROCESS: return PROCESS_CODE;
		

		// Input.
		case INPUT: return INPUT_CODE;

		
		// Output.
		case OUTPUT: return OUTPUT_CODE;
		

		// Memory.
		case MEMORY: return MEMORY_CODE;
		

		// Default.
		default:
			printf("\n\nERROR: COULD NOT RETRIEVE METADATA CODE\n\n");
			return 0;
	}
}


// Get descriptor.
char* get_descriptor(prog_metadata* metadata_ptr)
{
	// Which descriptor?
	switch (metadata_ptr->descriptor)
	{
		// Start.
		case START: return START_DESCRIPTOR;
		

		// End.
		case END: return END_DESCRIPTOR;
		

		// Run.
		case RUN: return RUN_DESCRIPTOR;
			

		// HDD.
		case HDD: return HDD_DESCRIPTOR;


		// Keyboard.
		case KEYBOARD: return KEYBOARD_DESCRIPTOR;
		

		// Mouse.
		case MOUSE: return MOUSE_DESCRIPTOR;


		// Monitor.
		case MONITOR: return MONITOR_DESCRIPTOR;


		// Speaker.
		case SPEAKER: return SPEAKER_DESCRIPTOR;


		// Printer.
		case PRINTER: return PRINTER_DESCRIPTOR;
		

		// Block.
		case BLOCK: return BLOCK_DESCRIPTOR;


		// Allocate.
		case ALLOCATE: return ALLOCATE_DESCRIPTOR;
		
		
		// Default?
		default:
			printf("\n\nERROR: COULD NOT RETRIEVE METADATA DESCRIPTOR\n\n");
			return NULL;
	}
}


// End header guard.
#endif