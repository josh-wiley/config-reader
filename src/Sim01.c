// Header guard.
#ifndef SIM_01_H_
#define SIM_01_H_


// Headers.
#include <stdio.h>
#include <stdlib.h>
#include "../lib/bool/bool.h"
#include "../lib/os_config/os_config.h"
#include "../lib/configure/configure.h"


// Program entry.
int main(int num_args, char** args)
{
    // OS config.
    os_config config;


    // User-supplied or default config?
    char* file_path = num_args > 1 ? args[1] : DEFAULT_CONFIG;


    // Configure OS and consume metadata.
    if (!configure_os(file_path, &config) && !consume_metadata(&config))
    {
        // Abort.
        return 1;
    }
    

    // Exit (no error).
    return 0;
}


// End header guard.
#endif