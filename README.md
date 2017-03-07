# OS Simulator for CS 446

The OS data structures and functions are found in `lib/os`
- `os.h` contains the data structure for the OS, currently only consisting of a single PCB (uniprogramming) and config.
- `pcb/pcb.h` defines the process control block data structure, which contains an array of metadata to simulate program code.
- `prog_exec/prog_exec.h` is the program simulator where PCB state is set, I/O threads are dispatched, and wait times are calculated and executed.

All other contents of the `lib` folder are convenience and helper utilities.
