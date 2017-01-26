# Variables.
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
OFLAGS = -o Sim01


# Executable.
Sim01: src/Sim01.o lib/file_io/file_io.o
	    $(CC) $(LFLAGS) src/Sim01.o lib/file_io/file_io.o $(OFLAGS)


# Main.
Sim01.o: src/Sim01.c lib/file_io/file_io.h
	    $(CC) $(CFLAGS) src/Sim01.c


# File reader library.
file_reader.o: lib/file_io/file_io.h lib/file_reader/file_io.c
	    $(CC) $(CFLAGS) lib/file_io/file_io.c


# Clean.
clean:
	    rm -rf *.o Sim01
