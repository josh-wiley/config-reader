# OS Simulator for CS 446

The OS data structures and functions are found in the `os` directory
- `os.h` contains the data structure for the OS, currently only consisting of a single PCB (uniprogramming), configuration structure, and a memory management unit.
- `pcb/pcb.h` defines the process control block data structure, which contains an array of metadata to simulate program code.
- `io_man/io_man.h` defines the I/O manager, which contains semaphores and mutexes for each device pool. If a program wishes to acquire an I/O device, it must do so through the I/O manager which is in charge of process synchronization.
- `sched/sched.h` is the OS scheduler simulation. Currently, round-robin is the only algorithm implemented and preempts processes by keeping track of the elapsed time during execution.

Contents of the `utils` folder are for convenience, consisting mostly of I/O helper utilities.

### Disclaimer
To enable multiprogramming, substantial refactoring was required which required a rewrite of the `logger` library. Due to time constraints, the logger was left unchanged and commented out of the program/build. As a result, there is very limited logging during program execution.
Also, round-robin and preemptive execution are not fully implemented.
