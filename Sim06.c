// Header guard.
#ifndef SIM_06_C_
#define SIM_06_C_


// Headers.
#include <stdio.h>
#include <stdlib.h>
#include "os/os.h"


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

    
    // Start OS.
    if (init_os(&os))
    {
        // Alert.
        printf("\n\nOS failure.\n\n");


        // Abort.
        return 1;
    }


    // Destroy the OS.
    destroy_os(&os);
    

    // Exit.
    return 0;
}


// End header guard.
#endif