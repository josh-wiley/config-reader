# Variables.
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c11
LFLAGS = -Wall $(DEBUG)
OFLAGS = -o Sim06
TFLAGS = -pthread


# Executable.
Sim06: Sim06.o os.o os_config.o file_io.o logger.o prog_exec.o prog_metadata.o pcb.o mem_man.o io_man.o
	$(CC) $(LFLAGS) Sim06.o os.o os_config.o file_io.o logger.o prog_metadata.o prog_exec.o pcb.o mem_man.o io_man.o $(OFLAGS) $(TFLAGS) && rm -rf *.o


# Main.
Sim06.o:
	$(CC) $(CFLAGS) Sim06.c


# OS.
os.o:
	$(CC) $(CFLAGS) os/os.c


# OS config.
os_config.o:
	$(CC) $(CFLAGS) os/config/os_config.c


# File reader library.
file_io.o:
	$(CC) $(CFLAGS) utils/file_io/file_io.c


# Logger.
logger.o:
	$(CC) $(CFLAGS) utils/logger/logger.c


# OS metadata.
prog_metadata.o:
	$(CC) $(CFLAGS) os/prog_metadata/prog_metadata.c


# Process control block.
pcb.o:
	$(CC) $(CFLAGS) os/pcb/pcb.c


# Program simulator.
prog_exec.o:
	$(CC) $(CFLAGS) os/prog_exec/prog_exec.c


# Memory manager.
mem_man.o:
	$(CC) $(CFLAGS) os/mem_man/mem_man.c


# I/O manager.
io_man.o:
	$(CC) $(CFLAGS) os/io_man/io_man.c


# Clean.
clean:
	rm -rf *.o Sim06
