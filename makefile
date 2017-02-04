# Variables.
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
OFLAGS = -o Sim01


# Executable.
Sim01: src/Sim01.o lib/file_io/file_io.o lib/configure/configure.o lib/logger/logger.o
	$(CC) $(LFLAGS) src/Sim01.o lib/file_io/file_io.o lib/configure/configure.o $(OFLAGS)


# Main.
Sim01.o:
	$(CC) $(CFLAGS) src/Sim01.c


# File reader library.
file_io.o:
	$(CC) $(CFLAGS) lib/file_io/file_io.c


# OS configuration.
configure.o:
	$(CC) $(CFLAGS) lib/configure/configure.c


# Logger.
logger.o:
	$(CC) $(CFLAGS) lib/logger/logger.c


# Clean.
clean:
	rm -rf *.o Sim01
