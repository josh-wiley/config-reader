// Header guard.
#ifndef SIM_01_H_
#define SIM_01_H_


// Headers.
#include "stdio.h"
#include "../lib/file_io/file_io.h"
#include "../lib/bool/bool.h"
#include "../lib/configure/configure.h"


// Program entry.
int main(int num_args, char** args)
{
    // Variables.
    char* config_ptr;
    bool was_file_read_successful = false;


    // No config?
    if (num_args < 2)
    {
        // Use default config.
        config_ptr = read_file(DEFAULT_CONFIG, &was_file_read_successful);


        // Failure?
        if (!was_file_read_successful)
        {
            // Alert.
            printf("\nUNABLE TO READ DEFAULT CONFIG:\nDefault config file has been moved/modified\n");


            // Exit (error).
            return 1;
        }
        
    }


    // Config supplied.
    else
    {
        // Message.
        char* message;


        // Check file-type.


        // Use user-supplied config.
        config_ptr = read_file(args[1], &was_file_read_successful);


        // Failure?
        if (!was_file_read_successful)
        {
            // Alert.
            printf("\nUNABLE TO READ USER-SUPPLIED CONFIG:\nFailure reading the file located at\n{%s}\n", args[1]);


            // Exit (error).
            return 1;
        }
    }


    // Display.
    printf(config_ptr);


    // Free memory.
    free(config_ptr);
    

    // Exit (no error).
    return 0;
}


// End header guard.
#endif