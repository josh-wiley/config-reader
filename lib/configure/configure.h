// Header guard.
#ifndef LIB_CONFIGURE_H_
#define LIB_CONFIGURE_H_


// Headers.
#include <stdlib.h>
#include <string.h>
#include "../bool/bool.h"
#include "../file_io/file_io.h"
#include "../os_config/os_config.h"


// Definitions.
#define CONFIG_ATTRIBUTE_DELIMITER ':'
#define CONFIG_VALUE_DELIMITER '\n'
#define METADATA_DELIMITER ';'
#define BUFFER_SIZE (size_t) 128
#define DEFAULT_CONFIG "./conf/default.conf"
#define PROCESSOR_CYCLE_TIME_ATTRIBUTE "Processor cycle time (msec)"
#define MEMORY_CYCLE_TIME_ATTRIBUTE "Memory cycle time (msec)"
#define HDD_CYCLE_TIME_ATTRIBUTE "Hard drive cycle time (msec)"
#define KEYBOARD_CYCLE_TIME_ATTRIBUTE "Keyboard cycle time (msec)"
#define MOUSE_CYCLE_TIME_ATTRIBUTE "Mouse cycle time (msec)"
#define MONITOR_DISPLAY_TIME_ATTRIBUTE "Monitor display time (msec)"
#define SPEAKER_CYCLE_TIME_ATTRIBUTE "Speaker cycle time (msec)"
#define PRINTER_CYCLE_TIME_ATTRIBUTE "Printer cycle time (msec)"
#define LOG_DESTINATION_ATTRIBUTE "Log"
#define METADATA_FILE_PATH_ATTRIBUTE "File Path"
#define LOG_FILE_PATH_ATTRIBUTE "Log File Path"
#define CONFIG_TERMINATOR_ATTRIBUTE "End Simulator Configuration File"


// Function prototypes.
bool configure_os(char*, os_config*);


// End header guard.
#endif