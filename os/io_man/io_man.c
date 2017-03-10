// Header guard.
#ifndef OS_IO_MAN_C_
#define OS_IO_MAN_C_


// Header.
#include "io_man.h"


// Init.
void init_io_man(io_man* this)
{
    // Default initialize semaphores.
    sem_init(&this->mouse_sem, 0, 1);
    sem_init(&this->keyboard_sem, 0, 1);
    sem_init(&this->hdd_sem, 0, 1);
    sem_init(&this->printer_sem, 0, 1);
    sem_init(&this->monitor_sem, 0, 1);
    sem_init(&this->speaker_sem, 0, 1);
}


// Set available.
int set_available(io_man* this, device_code device, unsigned int available)
{
    // Switch on device code.
    switch (device)
    {
        // Mouse.
        case MOUSE:
            // Set.
            sem_init(&this->mouse_sem, 0, available);


            // Done.
            return 0;
        

        // Keyboard.
        case KEYBOARD:
            // Set.
            sem_init(&this->keyboard_sem, 0, available);


            // Done.
            return 0;

        
        // HDD.
        case HDD:
            // Set.
            sem_init(&this->hdd_sem, 0, available);


            // Done.
            return 0;


        // Printer.
        case PRINTER:
            // Set.
            sem_init(&this->printer_sem, 0, available);


            // Done.
            return 0;


        // Monitor.
        case MONITOR:
            // Set.
            sem_init(&this->monitor_sem, 0, available);


            // Done.
            return 0;


        // Speaker.
        case SPEAKER:
            // Set.
            sem_init(&this->speaker_sem, 0, available);


            // Done.
            return 0;


        default:
            // Alert.
            printf("\n\nInvalid device code used to set available devices.\n\n");


            // Abort.
            return 1;
    }
}


// Acquire device.
int acquire(io_man* this, device_code device)
{
    // Switch on device code.
    switch (device)
    {
        // Mouse.
        case MOUSE:
            // Get.
            sem_wait(&this->mouse_sem);


            // Done.
            return 0;
        

        // Keyboard.
        case KEYBOARD:
            // Get.
            sem_wait(&this->keyboard_sem);


            // Done.
            return 0;

        
        // HDD.
        case HDD:
            // Get.
            sem_wait(&this->hdd_sem);


            // Done.
            return 0;


        // Printer.
        case PRINTER:
            // Get.
            sem_wait(&this->printer_sem);


            // Done.
            return 0;


        // Monitor.
        case MONITOR:
            // Get.
            sem_wait(&this->monitor_sem);


            // Done.
            return 0;


        // Speaker.
        case SPEAKER:
            // Get.
            sem_wait(&this->speaker_sem);


            // Done.
            return 0;


        default:
            // Alert.
            printf("\n\nInvalid device code used to set available devices.\n\n");


            // Abort.
            return 1;
    }
}


// Release device.
int release(io_man* this, device_code device)
{
    // Switch on device code.
    switch (device)
    {
        // Mouse.
        case MOUSE:
            // Release.
            sem_post(&this->mouse_sem);


            // Done.
            return 0;
        

        // Keyboard.
        case KEYBOARD:
            // Release.
            sem_post(&this->keyboard_sem);


            // Done.
            return 0;

        
        // HDD.
        case HDD:
            // Release.
            sem_post(&this->hdd_sem);


            // Done.
            return 0;


        // Printer.
        case PRINTER:
            // Release.
            sem_post(&this->printer_sem);


            // Done.
            return 0;


        // Monitor.
        case MONITOR:
            // Release.
            sem_post(&this->monitor_sem);


            // Done.
            return 0;


        // Speaker.
        case SPEAKER:
            // Release.
            sem_post(&this->speaker_sem);


            // Done.
            return 0;


        default:
            // Alert.
            printf("\n\nInvalid device code used to set available devices.\n\n");


            // Abort.
            return 1;
    }
}


// End header guard.
#endif