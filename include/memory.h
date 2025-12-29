#ifndef MEMORY_H
#define MEMORY_H

#include <list>
#include <iostream>

struct Block {
    int start;      // starting address
    int size;       // size of block
    bool free;      // free or allocated
    int id;         // block id (-1 if free)
};

class Memory {
private:
    int totalSize;
    std::list<Block> blocks;   // linked list of blocks

public:
    Memory();

    void init(int size);
    void dump();
    int getTotalSize();
    std::list<Block>& getBlocks();
    void printStats();
};

#endif
