// Header guard.
#ifndef OS_OP_H_
#define OS_OP_H_


// Headers.
#include "../prog_metadata/prog_metadata.h"


// Operation type.
typedef enum { OP_INPUT, OP_OUTPUT, OP_CPU, OP_MEMORY } op_type;


// Operation device.
typedef enum { OP_HDD, OP_PRINTER, OP_KEYBOARD, OP_MOUSE, OP_MONITOR, OP_SPEAKER } io_device;


// Operation.
typedef struct
{
    op_type type;
    unsigned int cycles;
    io_device device;
} op;


// Function declarations.
int create_op(op* this, const prog_metadata* metadata_ptr);


// End header guard.
#endif