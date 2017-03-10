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
		printf("\n\nFailed to access file at %s\n\n", file_path);
		return NULL;
	}


	// Successful.
	return file_ptr;
}


// Read until.
int read_until(FILE* file_ptr, char* buffer_ptr, size_t buffer_size, char delimiter)
{
	// Cannot read?
	if (!file_ptr || feof(file_ptr) || ferror(file_ptr))
	{
		// Alert.
		printf("\n\nCannot read from file provided...\n\n");


		// Done.
		return 1;
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
			// Alert.
			printf("\n\nReached EOF before delimiter was reached...\n\n");


			// Abort.
			return 1;
		}


		// Get next.
		unit = fgetc(file_ptr);
	}


	// Read into buffer.
	while (i < buffer_size)
	{
		// Delimiter?
		if (unit == delimiter)
		{
			// Terminate buffer.
			buffer_ptr[i] = '\0';


			// Done.
			return 0;
		}


		// Save, then increment.
		buffer_ptr[i++] = unit;


		// Get next char.
		unit = fgetc(file_ptr);


		// EOF?
		if (feof(file_ptr))
		{
			// Alert.
			printf("\n\nReached EOF before delimiter was reached...\n\n");


			// Abort.
			return 1;
		}
	}


	// Done.
	return 0;
}


// Close file.
void close_file(FILE* file_ptr)
{
	// Close.
	fclose(file_ptr);


	// Return.
	return;
}


// End header guard.
#endif