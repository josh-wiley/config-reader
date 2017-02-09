// Header guard.
#ifndef LIB_FILE_IO_C_
#define LIB_FILE_IO_C_


// Headers.
#include "file_io.h"


// Open file.
FILE* open_file(char* file_path, char* mode)
{
	// Open file.
	FILE* file_ptr = fopen(file_path, mode);


	// Access unsuccessful?
	if (!file_ptr)
	{
		// Alert and exit.
		printf("\n\nFILE ACCESS FAILED: %s\n\n", file_path);
		return NULL;
	}


	// Successful.
	return file_ptr;
}


// Read until.
bool read_until(FILE* file_ptr, char* buffer_ptr, size_t buffer_size, char delimiter)
{
	// Cannot read?
	if (!file_ptr || feof(file_ptr) || ferror(file_ptr))
	{
		// Done.
		return false;
	}


	// Variables.
	int i = 0;
	char unit = fgetc(file_ptr);


	// Discard leading whitespace.
	while (unit == ' ' || unit == '\t' || unit == '\n')
	{
		// EOF?
		if (feof(file_ptr))
		{
			// Abort.
			return false;
		}


		// Get next.
		unit = fgetc(file_ptr);
	}


	// Delimiter?
	if (unit == delimiter)
	{
		// Terminator.
		buffer_ptr[i] = '\0';


		// Done.
		return true;
	}


	// Save first character to buffer, then increment.
	buffer_ptr[i++] = unit;


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
			// Terminator.
			buffer_ptr[i] = '\0';


			// Done.
			return true;
		}


		// Save, then increment.
		buffer_ptr[i++] = unit;
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