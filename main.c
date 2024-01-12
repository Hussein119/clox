#include "headers/common.h"
#include "headers/chunk.h"
#include "headers/debug.h"
#include "headers/vm.h"

int main(int argc, const char *argv[])
{
    initVM();
    Chunk chunk;
    initChunk(&chunk);

    /*
    The addition goes first. The instruction for the left constant, 1.2, is already
        there, so we add another for 3.4. Then we add those two using OP_ADD, leaving
        it on the stack. That covers the left side of the division. Next we push the 5.6,
        and divide the result of the addition by it. Finally, we negate the result of that.
    */

    int constant = addConstant(&chunk, 1.2); // returns the index of the constant in the array
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    constant = addConstant(&chunk, 3.4);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_ADD, 123);

    constant = addConstant(&chunk, 5.6);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_DIVIDE, 123);

    writeChunk(&chunk, OP_NEGATE, 123);

    writeChunk(&chunk, OP_RETURN, 123);
    // to disassemble all of the instructions in the entire chunk.
    disassembleChunk(&chunk, "test chunk");
    // This function is the main entrypoint into the VM.
    interpret(&chunk);
    freeVM();
    freeChunk(&chunk);

    return 0;
}