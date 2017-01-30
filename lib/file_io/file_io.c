// Header guard.
#ifndef LIB_FILE_IO_C_
#define LIB_FILE_IO_C_


// Headers.
#include "file_io.h"


// Read file into memory.
unsigned char* read_file(unsigned char* file_name, bool* is_successful_ptr)
{
	// Variables.
	FILE* fin_ptr = fopen(file_name, "r");
	unsigned char* buffer_ptr;
	size_t file_size;


	// File access failed?
	if (fin_ptr == NULL)
	{
		printf("\nFILE ACCESS FAILED: %s\n", file_name); // TODO: REMOVE
		// Exit (error).
		*is_successful_ptr = false;
		return NULL;
	}


	// Get size of file.
	fseek(SEEK_END, 0, fin_ptr);
	file_size = ftell(fin_ptr);


	// No data in file?
	if (file_size == 0) {
		printf("\nEMPTY FILE\n"); // TODO: REMOVE
		// Exit (error).
		*is_successful_ptr = false;
		return NULL;
	}


	// Create buffer for file data.
	buffer_ptr = (unsigned char*) malloc(file_size);


	// Reset the file pointer.
	rewind(fin_ptr);


	// Read file into memory.
	fscanf(buffer_ptr, sizeof(unsigned char), file_size, fin_ptr);


	// Close file.
	fclose(fin_ptr);


	// Done.
	*is_successful_ptr = true;
	return buffer_ptr;
}


// End header guard.
#endif