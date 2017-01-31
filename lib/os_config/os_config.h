// Header guard.
#ifndef LIB_OS_CONFIG_
#define LIB_OS_CONFIG_


// OS config.
typedef struct
{
	unsigned long processor_speed;
	unsigned long memory_speed;
	unsigned long hard_drive_access;
	unsigned long monitor_refresh;
	unsigned long speaker_latency;
	unsigned long printer_latency;
	unsigned long keyboard_latency;
	unsigned long mouse_latency;
	char* log_file_path;
} os_config;


// End header guard.
#endif