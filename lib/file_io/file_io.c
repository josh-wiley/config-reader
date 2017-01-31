// Header guard.
#ifndef LIB_FILE_IO_C_
#define LIB_FILE_IO_C_


// Headers.
#include "file_io.h"


// Open file.
bool open_file(char* file_path, FILE* file_ptr)
{
	// Open file.
	file_ptr = fopen(file_path, "r");


	// Access unsuccessful?
	if (!file_ptr)
	{
		// Alert and exit.
		printf("\n\nFILE ACCESS FAILED: %s\n\n", file_path);
		return false;
	}


	// Successful.
	return true;
}


// Read line.
bool read_line(FILE* file_ptr, char* buffer_ptr, size_t buffer_size, char delimiter)
{
	// End of file?
	if (feof(file_ptr) || ferror(file_ptr))
	{
		// Done.
		return false;
	}


	// Variables.
	int i = 0;
	char unit;


	// Read into buffer.
	while (i < buffer_size)
	{
		// EOF?
		if (feof(file_ptr))
		{
			// Abort.
			return false;
		}


		// Get next char.
		unit = fgetc(file_ptr);


		// Delimiter?
		if (unit == delimiter)
		{
			// Done.
			return true;
		}


		// Save.
		buffer_ptr[i] = unit;


		// Increment.
		i++;
	}


	// Done.
	return true;
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