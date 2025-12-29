#include "../include/memory.h"

Memory::Memory() {
    totalSize = 0;
}

void Memory::init(int size) {
    totalSize = size;
    blocks.clear();

    Block initial;
    initial.start = 0;
    initial.size = size;
    initial.free = true;
    initial.id = -1;

    blocks.push_back(initial);

    std::cout << "Memory initialized with size " << size << "\n";
}

void Memory::dump() {
    std::cout << "----- Memory Dump -----\n";
    for (auto &b : blocks) {
        std::cout << "[0x"
                  << std::hex << b.start
                  << " - 0x"
                  << (b.start + b.size - 1)
                  << std::dec << "] ";

        if (b.free) {
            std::cout << "FREE\n";
        } else {
            std::cout << "USED (id=" << b.id << ")\n";
        }
    }
}

int Memory::getTotalSize() {
    return totalSize;
}

std::list<Block>& Memory::getBlocks() {
    return blocks;
}

void Memory::printStats() {
    int usedMemory = 0;
    int freeMemory = 0;
    int largestFree = 0;

    for (auto &b : blocks) {
        if (b.free) {
            freeMemory += b.size;
            if (b.size > largestFree) largestFree = b.size;
        } else {
            usedMemory += b.size;
        }
    }

    int total = totalSize;

    double externalFrag = 0.0;
    if (freeMemory > 0)
        externalFrag = 100.0 * (1.0 - (double)largestFree / freeMemory);

    double utilization = 100.0 * ((double)usedMemory / total);

    std::cout << "----- Memory Stats -----\n";
    std::cout << "Total memory: " << total << "\n";
    std::cout << "Used memory: " << usedMemory << "\n";
    std::cout << "Free memory: " << freeMemory << "\n";
    std::cout << "Memory utilization: " << utilization << "%\n";
    std::cout << "External fragmentation: " << externalFrag << "%\n";
}
