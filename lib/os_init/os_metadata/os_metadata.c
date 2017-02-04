// Header guard.
#ifndef LIB_OS_METADATA_C_
#define LIB_OS_METADATA_C_


// Get code.
char get_code(os_metadata* metadata_ptr)
{
	// Which code?
	switch (metadata_ptr->code)
	{
		// OS?
		case OS:
			return OS_CODE;
		

		// Application?
		case APPLICATION:
			return APPLICATION_CODE;
		

		// Process?
		case PROCESS:
			return PROCESS_CODE;
		

		// Input?
		case INPUT:
			return INPUT_CODE;

		
		// Output?
		case OUTPUT:
			return OUTPUT_CODE;
		

		// Memory?
		case MEMORY:
			return MEMORY_CODE;
		

		// Default?
		default:
			printf("\n\nERROR: COULD NOT RETRIEVE METADATA CODE\n\n");
			return 0;
	}
}


// Get descriptor.
char* get_descriptor(os_metadata* metadata_ptr)
{
	// Start?
}


// End header guard.
#endif