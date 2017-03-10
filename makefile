# Variables.
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c11
LFLAGS = -Wall $(DEBUG)
OFLAGS = -o Sim03
TFLAGS = -pthread


# Executable.
Sim03: Sim03.o os.o os_config.o file_io.o logger.o prog_exec.o prog_metadata.o pcb.o mem_man.o
	$(CC) $(LFLAGS) Sim03.o os.o os_config.o file_io.o logger.o prog_metadata.o prog_exec.o pcb.o mem_man.o $(OFLAGS) $(TFLAGS) && rm -rf *.o


# Main.
Sim03.o:
	$(CC) $(CFLAGS) src/Sim03.c


# OS.
os.o:
	$(CC) $(CFLAGS) lib/os/os.c


# OS config.
os_config.o:
	$(CC) $(CFLAGS) lib/os/config/os_config.c


# File reader library.
file_io.o:
	$(CC) $(CFLAGS) lib/file_io/file_io.c


# Logger.
logger.o:
	$(CC) $(CFLAGS) lib/logger/logger.c


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
mem_man.o:
	$(CC) $(CFLAGS) lib/os/mem_man/mem_man.c


# Clean.
clean:
	rm -rf *.o Sim03
