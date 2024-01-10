#include <stdio.h>
#include "common.h"
#include "vm.h"
#include "debug.h"

VM vm;

static void resetStack()
{
    // set stackTop to point to the beginning of the array
    // to indicate that the stack is empty.
    vm.stackTop = vm.stack;
}

void initVM()
{
    resetStack();
}

void freeVM()
{
}

void push(Value value)
{
    /*
    Remember, stackTop points just past the last used element, at the next
        available one. This stores the value in that slot. Then we increment the pointer
        itself to point to the next unused slot in the array now that the previous slot is
        occupied.
    */
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop()
{
    /*
    First, we move the stack pointer back to get to the most recent used slot in the
        array. Then we look up the value at that index and return it. We don’t need to
        explicitly “remove” it from the array—moving stackTop down is enough to
        mark that slot as no longer in use.
    */
    vm.stackTop--;
    return *vm.stackTop;
}

static InterpretResult run()
{
    // The READ_BYTE macro reads the byte currently pointed at by ip
    // and then advances the instruction pointer.
    // The first byte of any instruction is the opcode.
#define READ_BYTE() (*vm.ip++)

    // READ_CONSTANT() reads the next byte from the bytecode, treats the resulting
    // number as an index, and looks up the corresponding Value in the chunk’s
    // constant table.
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

#define BINARY_OP(op)     \
    do                    \
    {                     \
        double b = pop(); \
        double a = pop(); \
        push(a op b);     \
    } while (false)

    for (;;)
    {
/*
Since disassembleInstruction() takes an integer byte offset and we store
the current instruction reference as a direct pointer, we first do a little pointer
math to convert ip back to a relative offset from the beginning of the bytecode.
Then we disassemble the instruction that begins at that byte.
*/
#ifdef DEBUG_TRACE_EXECUTION
        printf(" ");
        for (Value *slot = vm.stack; slot < vm.stackTop; slot++)
        {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
        disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE())
        {
        case OP_CONSTANT:
        {
            Value constant = READ_CONSTANT();
            // printValue(constant);
            // printf("\n");
            push(constant);
            break;
        }
        case OP_ADD:
            BINARY_OP(+);
            break;
        case OP_SUBTRACT:
            BINARY_OP(-);
            break;
        case OP_MULTIPLY:
            BINARY_OP(*);
            break;
        case OP_DIVIDE:
            BINARY_OP(/);
            break;
        case OP_NEGATE:
            push(-pop());
            break;
        case OP_RETURN:
        {
            printValue(pop());
            printf("\n");
            return INTERPRET_OK;
        }
        }
    }

// used to undefine macros
#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

InterpretResult interpret(Chunk *chunk)
{
    vm.chunk = chunk;
    // As the VM works its way through the bytecode, it (vm.ip) keeps track of where it is—
    // the location of the instruction currently being executed.
    vm.ip = vm.chunk->code;
    return run();
}