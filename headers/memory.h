#ifndef clox_memory_h
#define clox_memory_h
#include "common.h"

// This macro calculates a new capacity based on a given current capacity.
#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

/*
This reallocate() function is the single function we’ll use for all dynamic
memory management in clox—allocating memory, freeing it, and changing the
size of an existing allocation.
*/
#define GROW_ARRAY(type, pointer, oldCount, newCount)      \
    (type *)reallocate(pointer, sizeof(type) * (oldCount), \
                       sizeof(type) * (newCount))

// This one frees the memory by passing in zero for the new size.
#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

void *reallocate(void *pointer, size_t oldSize, size_t newSize);

#endif