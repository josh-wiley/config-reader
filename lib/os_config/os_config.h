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
	unsigned long processor_period_ms;
	unsigned long memory_period_ms;
	unsigned long hard_drive_period_ms;
	unsigned long monitor_period_ms;
	unsigned long speaker_period_ms;
	unsigned long printer_period_ms;
	unsigned long keyboard_period_ms;
	unsigned long mouse_period_ms;
} os_config;


// End header guard.
#endif