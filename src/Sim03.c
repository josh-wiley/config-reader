// Header guard.
#ifndef SIM_03_C_
#define SIM_03_C_


// Headers.
#include <stdio.h>
#include <stdlib.h>
#include "../lib/bool/bool.h"
#include "../lib/os/os.h"
#include "../lib/os/prog_exec/prog_exec.h"


// Program entry.
int main(int num_args, char** args)
{
    // OS.
    os os;


    // User-supplied or default config?
    char* file_path = num_args > 1 ? args[1] : DEFAULT_CONFIG;


    // Configure OS.
    if (!configure(&os, file_path))
    {
        // Abort.
        return 1;
    }


    // Execute program.
    if (!exec(&os))
    {
        // Abort.
        return 1;
    }
    

    // Exit (no error).
    return 0;
}


// End header guard.
#endif