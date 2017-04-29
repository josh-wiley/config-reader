// Header guard.
#ifndef OS_SCHED_H_
#define OS_SCHED_H_


// Scheduler.
typedef struct
{
    pcb* os_pcb_tree;
} sched;


#endif