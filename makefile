# Variables.
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c11
LFLAGS = -Wall $(DEBUG)
OFLAGS = -o Sim01
TFLAGS = -pthread


# Executable.
Sim01: Sim01.o os.o file_io.o logger.o configure.o prog_exec.o prog_metadata.o pcb.o mem_alloc.o
	$(CC) $(LFLAGS) Sim01.o os.o file_io.o logger.o configure.o prog_metadata.o prog_exec.o pcb.o mem_alloc.o $(OFLAGS) $(TFLAGS) && rm -rf *.o


# Main.
Sim01.o:
	$(CC) $(CFLAGS) src/Sim01.c


# OS.
os.o:
	$(CC) $(CFLAGS) lib/os/os.c


# File reader library.
file_io.o:
	$(CC) $(CFLAGS) lib/file_io/file_io.c


# Logger.
logger.o:
	$(CC) $(CFLAGS) lib/logger/logger.c


# OS configuration.
configure.o:
	$(CC) $(CFLAGS) lib/configure/configure.c


# OS metadata.
prog_metadata.o:
	$(CC) $(CFLAGS) lib/os/prog_metadata/prog_metadata.c


# Process control block.
pcb.o:
	$(CC) $(CFLAGS) lib/os/pcb/pcb.c


# Program simulator.
prog_exec.o:
	$(CC) $(CFLAGS) lib/os/prog_exec/prog_exec.c


# Memory allocator.
mem_alloc.o:
	$(CC) $(CFLAGS) lib/os/mem_alloc/mem_alloc.c


# Clean.
clean:
	rm -rf *.o Sim01
