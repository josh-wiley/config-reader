// Header guard.
#ifndef LIB_FILE_IO_C_
#define LIB_FILE_IO_C_


// Headers.
#include "file_io.h"


// Open file.
FILE* open_file(char* file_path)
{
	// Open file.
	FILE* file_ptr = fopen(file_path, "r");


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


// Read some.
bool read_until(FILE* file_ptr, char* buffer_ptr, size_t buffer_size, char delimiter, bool should_ignore_whitespace)
{
	// Cannot read?
	if (!file_ptr || feof(file_ptr) || ferror(file_ptr))
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
			// Terminator.
			buffer_ptr[i] = '\0';


			// Done.
			return true;
		}


		// Not whitespace?
		if (!should_ignore_whitespace || unit != '\n' || unit != '\t' || unit != ' ')
		{
			// Save.
			buffer_ptr[i] = unit;
		}


		// Increment.
		i++;
	}


	// Done.
	return true;
}


// Ignore incoming whitespace.
void ignore_incoming_whitespace(FILE* file_ptr)
{
	// Cannot read?
	if (!file_ptr || ferror(file_ptr))
	{
		// Abort.
		return;
	}


	// Buffer unit.
	char unit;


	// Ignore.
	while (!feof(file_ptr))
	{
		// Get char.
		unit = fgetc(file_ptr);


		// Not whitespace?
		if (!(unit == ' ' || unit == '\n' || unit == '\t'))
		{
			// Step back.
			fseek(file_ptr, -1, SEEK_CUR);


			// Done.
			return;
		}
	}
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