// Header guard.
#ifndef OS_IO_MAN_H_
#define OS_IO_MAN_H_


// Headers.
#include <semaphore.h>
#include "../config/os_config.h"
#include "../prog_metadata/prog_metadata.h"
#include <pthread.h>


// Alias.
typedef metadata_descriptor device_code;


// I/O Manager.
typedef struct
{
    sem_t mouse_sem;
    sem_t keyboard_sem;
    sem_t hdd_sem;
    sem_t printer_sem;
    sem_t monitor_sem;
    sem_t speaker_sem;
    pthread_mutex_t mouse_mutex;
    pthread_mutex_t keyboard_mutex;
    pthread_mutex_t hdd_mutex;
    pthread_mutex_t printer_mutex;
    pthread_mutex_t monitor_mutex;
    pthread_mutex_t speaker_mutex;
} io_man;


// Function prototypes.
void init_io_man(io_man*, os_config*);
void destroy_io_man(io_man*);
unsigned int get_available(io_man*, device_code);
int set_available(io_man*, device_code, unsigned int);
int acquire(io_man*, device_code);
int release(io_man*, device_code);


// End header guard.
#endif