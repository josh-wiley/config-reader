// Guard.
#ifndef LIB_FILE_IO_C_
#define LIB_FILE_IO_C_


// Headers.
#include "file_io.h"


// Read file into memory.
char* read_file(char* file_name, bool* is_successful_ptr)
{
	// Variables.
	FILE* fin_ptr = fopen(file_name, 'r');
	char* mem_buff_ptr;


	// File access failed?
	if (fin_ptr == NULL)
	{
		// Exit (error).
		*is_successful_ptr = false;
		return NULL;
	}


	// Get size of file.
	fseek(SEEK_END, 0, fin_ptr);
	mem_buff_ptr = (char*) malloc(ftell(fin_ptr));
	rewind(fin_ptr);


	// Read file into memory.
	fscanf(fin_ptr, mem_buff_ptr)


	// Done.
	fclose(fin_ptr);
	*is_successful_ptr = true;
	return mem_buff_ptr;
}


// End guard.
#endif