// Header guard.
#ifndef OS_IO_MAN_C_
#define OS_IO_MAN_C_


// Header.
#include "io_man.h"


// Function prototypes.
inline sem_t* get_sem(io_man*, device_code);
inline pthread_mutex_t* get_mutex(io_man*, device_code);


// Init.
void init_io_man(io_man* this, os_config* config_ptr)
{
    // Initialize semaphores.
    sem_init(&this->mouse_sem, 0, config_ptr->total_mice);
    sem_init(&this->keyboard_sem, 0, config_ptr->total_keyboards);
    sem_init(&this->hdd_sem, 0, config_ptr->total_hdds);
    sem_init(&this->printer_sem, 0, config_ptr->total_printers);
    sem_init(&this->monitor_sem, 0, config_ptr->total_monitors);
    sem_init(&this->speaker_sem, 0, config_ptr->total_speakers);


    // Initialize mutexes.
    pthread_mutex_init(&this->mouse_mutex, NULL);
    pthread_mutex_init(&this->keyboard_mutex, NULL);
    pthread_mutex_init(&this->hdd_mutex, NULL);
    pthread_mutex_init(&this->printer_mutex, NULL);
    pthread_mutex_init(&this->monitor_mutex, NULL);
    pthread_mutex_init(&this->speaker_mutex, NULL);
}


// Destroy.
void destroy_io_man(io_man* this)
{
    // Destroy semaphores.
    sem_destroy(&this->mouse_sem);
    sem_destroy(&this->keyboard_sem);
    sem_destroy(&this->hdd_sem);
    sem_destroy(&this->printer_sem);
    sem_destroy(&this->monitor_sem);
    sem_destroy(&this->speaker_sem);


    // Destroy mutexes.
    pthread_mutex_destroy(&this->mouse_mutex);
    pthread_mutex_destroy(&this->keyboard_mutex);
    pthread_mutex_destroy(&this->hdd_mutex);
    pthread_mutex_destroy(&this->printer_mutex);
    pthread_mutex_destroy(&this->monitor_mutex);
    pthread_mutex_destroy(&this->speaker_mutex);
}


// Get available.
unsigned int get_available(io_man* this, device_code device)
{
    // Available.
    int available;


    // Get value.
    sem_getvalue(get_sem(this, device), &available);


    // Return.
    return (unsigned int) available;
}


// Set available.
int set_available(io_man* this, device_code device, unsigned int available)
{
    // Re-initialize appropriate semaphore.
    return sem_init(get_sem(this, device), 0, available);
}


// Acquire device.
int acquire(io_man* this, device_code device)
{
    // Get device from pool.
    return sem_wait(get_sem(this, device)) && pthread_mutex_lock(get_mutex(this, device));
}


// Release device.
int release(io_man* this, device_code device)
{
    // Post to semaphore.
    return sem_post(get_sem(this, device)) && pthread_mutex_unlock(get_mutex(this, device));
}


// Get semaphore associated with device pool.
sem_t* get_sem(io_man* this, device_code device)
{
    // Switch on device code.
    switch (device)
    {
        // Mouse.
        case MOUSE: return &this->mouse_sem;
        

        // Keyboard.
        case KEYBOARD: return &this->keyboard_sem;

        
        // HDD.
        case HDD: return &this->hdd_sem;


        // Printer.
        case PRINTER: return &this->printer_sem;


        // Speaker.
        case SPEAKER: return &this->speaker_sem;


        // By default, return the monitor.
        default: return &this->monitor_sem;
    }
}


// Get mutex associated with device pool.
pthread_mutex_t* get_mutex(io_man* this, device_code device)
{
    // Switch on device code.
    switch (device)
    {
        // Mouse.
        case MOUSE: return &this->mouse_mutex;
        

        // Keyboard.
        case KEYBOARD: return &this->keyboard_mutex;

        
        // HDD.
        case HDD: return &this->hdd_mutex;


        // Printer.
        case PRINTER: return &this->printer_mutex;


        // Speaker.
        case SPEAKER: return &this->speaker_mutex;


        // By default, return the monitor.
        default: return &this->monitor_mutex;
    }
}


// End header guard.
#endif