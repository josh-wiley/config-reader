# OS Simulator for CS 446

The OS data structures and functions are found in the `os` directory
- `os.h` contains the data structure for the OS, currently only consisting of a single PCB (uniprogramming), configuration structure, and a memory management unit.
- `pcb/pcb.h` defines the process control block data structure, which contains an array of metadata to simulate program code.
- `prog_exec/prog_exec.h` is the program executuion simulator where PCB state is set, I/O threads are dispatched, thread synchronization is handled, and wait times are calculated and enforced.
- `io_man/io_man.h` defines the I/O manager, which contains semaphores and mutexes for each device pool. If a program wishes to acquire an I/O device, it must do so through the I/O manager which is in charge of process synchronization.

Contents of the `utils` folder are for convenience, consisting mostly of I/O helper utilities.
