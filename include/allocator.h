#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "memory.h"

enum AllocatorType {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
};

class Allocator {
private:
    int nextId;
    AllocatorType currentType;

public:
    Allocator();

    void setAllocator(AllocatorType type);

    int mallocMemory(Memory &mem, int size);

    // existing
    int mallocFirstFit(Memory &mem, int size);
    int mallocBestFit(Memory &mem, int size);
    int mallocWorstFit(Memory &mem, int size);

    void freeBlock(Memory &mem, int id);
};

#endif
