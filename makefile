# Variables.
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c11
LFLAGS = -Wall $(DEBUG)
OFLAGS = -o Sim01


# Executable.
Sim01: Sim01.o file_io.o configure.o logger.o os_metadata.o program_sim.o pcb.o mem_alloc.o
	$(CC) $(LFLAGS) Sim01.o file_io.o configure.o logger.o os_metadata.o program_sim.o pcb.o mem_alloc.o $(OFLAGS) && rm -rf *.o


# Main.
Sim01.o:
	$(CC) $(CFLAGS) src/Sim01.c


# File reader library.
file_io.o:
	$(CC) $(CFLAGS) lib/file_io/file_io.c


# OS configuration.
configure.o:
	$(CC) $(CFLAGS) lib/configure/configure.c


# OS metadata.
os_metadata.o:
	$(CC) $(CFLAGS) lib/os/os_metadata/os_metadata.c


# Process control block.
pcb.o:
	$(CC) $(CFLAGS) lib/os/pcb/pcb.c


# Program simulator.
program_sim.o:
	$(CC) $(CFLAGS) lib/os/os_program_sim/program_sim.c

# Memory allocator.
mem_alloc.o:
	$(CC) $(CFLAGS) lib/os/mem_alloc/mem_alloc.c


# Logger.
logger.o:
	$(CC) $(CFLAGS) lib/logger/logger.c


# Clean.
clean:
	rm -rf *.o Sim01
