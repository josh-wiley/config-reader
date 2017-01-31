// Header guard.
#ifndef LIB_FILE_IO_C_
#define LIB_FILE_IO_C_


// Headers.
#include "file_io.h"


// Open file.
bool open_file(char* file_path, FILE* file_ptr)
{
	// Open file.
	file_ptr = fopen(file_path);


	// Access unsuccessful?
	if (!file_ptr)
	{
		// Set message and exit.
		printf("\n\nFILE ACCESS FAILED: %s\n\n", file_path);
	}


	// Return.
	return file_ptr;
}


// Read line.
bool read_line(FILE* file_ptr)
{
	// Variables.
	unsigned char* buffer_ptr;


	// No data in file?
	if (file_size == 0)
	{
		// Exit (error).
		return false;
	}


	// Create buffer for file data.
	buffer_ptr = (unsigned char*) malloc(file_size);


	// Read file into memory.
	fscanf(buffer_ptr, sizeof(unsigned char), file_size, fin_ptr);


	// Done.
	return buffer_ptr;
}


// Close file.
bool close_file(FILE* file_ptr)
{
	// Close and return.
	fclose(file_ptr);
	return true;
}


// End header guard.
#endif