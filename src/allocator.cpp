#include "../include/allocator.h"
#include <iostream>

Allocator::Allocator() {
    nextId = 1;
    currentType = FIRST_FIT;
}

void Allocator::setAllocator(AllocatorType type) {
    currentType = type;
    //std::cout << "Allocator switched\n";
}

int Allocator::mallocMemory(Memory &mem, int size) {
    if (currentType == FIRST_FIT)
        return mallocFirstFit(mem, size);
    else if (currentType == BEST_FIT)
        return mallocBestFit(mem, size);
    else
        return mallocWorstFit(mem, size);
}

int Allocator::mallocFirstFit(Memory &mem, int size) {
    auto &blocks = mem.getBlocks();

    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (it->free && it->size >= size) {

            // Create allocated block
            Block allocated;
            allocated.start = it->start;
            allocated.size = size;
            allocated.free = false;
            allocated.id = nextId++;

            // Modify current free block
            it->start += size;
            it->size -= size;

            // Insert allocated block before free block
            blocks.insert(it, allocated);

            // If free block becomes size 0, remove it
            if (it->size == 0) {
                blocks.erase(it);
            }

            std::cout << "Allocated block id=" << allocated.id
                      << " at address=0x"
                      << std::hex << allocated.start << std::dec << "\n";

            return allocated.id;
        }
    }

    std::cout << "Allocation failed: Not enough memory\n";
    return -1;
}

int Allocator::mallocBestFit(Memory &mem, int size) {
    auto &blocks = mem.getBlocks();
    auto best = blocks.end();

    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (it->free && it->size >= size) {
            if (best == blocks.end() || it->size < best->size) {
                best = it;
            }
        }
    }

    if (best == blocks.end()) {
        std::cout << "Allocation failed\n";
        return -1;
    }

    Block allocated;
    allocated.start = best->start;
    allocated.size = size;
    allocated.free = false;
    allocated.id = nextId++;

    best->start += size;
    best->size -= size;

    blocks.insert(best, allocated);
    if (best->size == 0)
        blocks.erase(best);

    std::cout << "Allocated (Best Fit) id=" << allocated.id
              << " at address=0x"
              << std::hex << allocated.start << std::dec << "\n";

    return allocated.id;
}

int Allocator::mallocWorstFit(Memory &mem, int size) {
    auto &blocks = mem.getBlocks();
    auto worst = blocks.end();

    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (it->free && it->size >= size) {
            if (worst == blocks.end() || it->size > worst->size) {
                worst = it;
            }
        }
    }

    if (worst == blocks.end()) {
        std::cout << "Allocation failed\n";
        return -1;
    }

    Block allocated;
    allocated.start = worst->start;
    allocated.size = size;
    allocated.free = false;
    allocated.id = nextId++;

    worst->start += size;
    worst->size -= size;

    blocks.insert(worst, allocated);
    if (worst->size == 0)
        blocks.erase(worst);

    std::cout << "Allocated (Worst Fit) id=" << allocated.id
              << " at address=0x"
              << std::hex << allocated.start << std::dec << "\n";

    return allocated.id;
}

void Allocator::freeBlock(Memory &mem, int id) {
    auto &blocks = mem.getBlocks();

    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (!it->free && it->id == id) {

            // Mark block as free
            it->free = true;
            it->id = -1;

            std::cout << "Block " << id << " freed\n";

            // Merge with next block if free
            auto next = it;
            ++next;
            if (next != blocks.end() && next->free) {
                it->size += next->size;
                blocks.erase(next);
            }

            // Merge with previous block if free
            if (it != blocks.begin()) {
                auto prev = it;
                --prev;
                if (prev->free) {
                    prev->size += it->size;
                    blocks.erase(it);
                }
            }

            return;
        }
    }

    std::cout << "Invalid free request: block id not found\n";
}
