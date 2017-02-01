// Header guard.
#ifndef LIB_OS_CONFIG_
#define LIB_OS_CONFIG_


// Log destination.
typedef enum { TO_BOTH, TO_FILE, TO_DISPLAY } destination;


// OS config.
typedef struct
{
	float version;
	char* metadata_file_path;
	char* log_file_path;
	destination log_dest;
	unsigned int processor_period_ms;
	unsigned int memory_period_ms;
	unsigned int hard_drive_period_ms;
	unsigned int monitor_period_ms;
	unsigned int speaker_period_ms;
	unsigned int printer_period_ms;
	unsigned int keyboard_period_ms;
	unsigned int mouse_period_ms;
} os_config;


// End header guard.
#endif