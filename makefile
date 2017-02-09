# Variables.
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c99
LFLAGS = -Wall $(DEBUG)
OFLAGS = -o Sim01


# Executable.
Sim01: Sim01.o file_io.o configure.o logger.o os_metadata.o
	$(CC) $(LFLAGS) Sim01.o file_io.o configure.o logger.o os_metadata.o $(OFLAGS)


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
	$(CC) $(CFLAGS) lib/os_init/os_metadata/os_metadata.c


# Logger.
logger.o:
	$(CC) $(CFLAGS) lib/logger/logger.c


# Clean.
clean:
	rm -rf *.o Sim01
