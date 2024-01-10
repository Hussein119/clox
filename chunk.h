#ifndef clox_chunk_h
#define clox_chunk_h
#include "common.h"
#include "value.h"

/*
In our bytecode format, each instruction has a one-byte operation code
    (universally shortened to opcode).
That number controls what kind of instruction we’re dealing with—add,
    subtract, look up variable, etc.
*/
typedef enum
{
    OP_CONSTANT, // 2 bytes (opcode , constant index)
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_RETURN, // 1 byte  (opcode)
} OpCode;

/*
Bytecode is a series of instructions. Eventually, we’ll store some other data along
with the instructions, so let’s go ahead and create a struct to hold it all.
*/
typedef struct
{
    /*
    In addition to the array itself, we keep two numbers:
        the number of elements in the array we have allocated (“capacity”)
        and how many of those allocated entries are actually in use (“count”).
    Dynamic arrays:
        Dynamic arrays provide:
            Cache-friendly, dense storage
            Constant-time indexed element lookup
            Constant-time appending to the end of the array
        Copying the existing elements when you grow the array makes it seem like
            appending an element is O(n), not O(1) like I said above.
        However, you need to do this copy step only on some of the appends.
        Most of the time, there is already extra capacity, so you don’t need to copy.
    */
    int count;
    int capacity;
    uint8_t *code;
    int *lines;
    ValueArray constants;
} Chunk;

// A function to initialize a new chunk.
void initChunk(Chunk *chunk);

void freeChunk(Chunk *chunk);

// append a byte to the end of the chunk
void writeChunk(Chunk *chunk, uint8_t byte, int line);

// method to add a new constant to the chunk
int addConstant(Chunk *chunk, Value value);

#endif