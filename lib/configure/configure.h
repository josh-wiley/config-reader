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
#define VERSION_PHASE_ATTRIBUTE "Version/Phase"
#define PROCESSOR_PERIOD_ATTRIBUTE "Processor cycle time (msec)"
#define MEMORY_PERIOD_ATTRIBUTE "Memory cycle time (msec)"
#define HDD_PERIOD_ATTRIBUTE "Hard drive cycle time (msec)"
#define KEYBOARD_PERIOD_ATTRIBUTE "Keyboard cycle time (msec)"
#define MOUSE_PERIOD_ATTRIBUTE "Mouse cycle time (msec)"
#define MONITOR_DISPLAY_TIME_ATTRIBUTE "Monitor display time (msec)"
#define SPEAKER_PERIOD_ATTRIBUTE "Speaker cycle time (msec)"
#define PRINTER_PERIOD_ATTRIBUTE "Printer cycle time (msec)"
#define LOG_DESTINATION_ATTRIBUTE "Log"
#define METADATA_FILE_PATH_ATTRIBUTE "File Path"
#define LOG_FILE_PATH_ATTRIBUTE "Log File Path"
#define CONFIG_TERMINATOR_ATTRIBUTE "End Simulator Configuration File"
#define LOG_TO_BOTH_VALUE "Log to Both"
#define LOG_TO_FILE_VALUE "Log to File"
#define LOG_TO_DISPLAY_VALUE "Log to Display"


// Function prototypes.
bool configure_os(char*, os_config*);


// End header guard.
#endif