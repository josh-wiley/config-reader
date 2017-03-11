// Header guard.
#ifndef SIM_03_C_
#define SIM_03_C_


// Headers.
#include <stdio.h>
#include <stdlib.h>
#include "os/os.h"
#include "os/prog_exec/prog_exec.h"


// Program entry.
int main(int num_args, char** args)
{
    // OS.
    os os;


    // User-supplied or default config?
    char* file_path = num_args > 1 ? args[1] : DEFAULT_CONFIG;


    // Configure OS.
    if (configure_os(&os, file_path))
    {
        // Alert.
        printf("\n\nOS configuration failed.\n\n");


        // Abort.
        return 1;
    }

    
    // Execute program.
    if (exec(&os))
    {
        // Alert.
        printf("\n\nProgram execution failed.\n\n");


        // Abort.
        return 1;
    }


    // Destroy OS.
    destroy_os(&os);
    

    // Exit.
    return 0;
}


// End header guard.
#endif