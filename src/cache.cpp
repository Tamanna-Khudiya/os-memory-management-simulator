#include "../include/cache.h"
#include <iostream>

CacheLevel::CacheLevel(int cap)
    : capacity(cap), time(0), hits(0), misses(0) {}

bool CacheLevel::access(int address) {
    time++;

    for (auto &line : lines) {
        if (line.valid && line.address == address) {
            hits++;
            line.lastUsed = time;
            return true;  // HIT
        }
    }

    misses++;

    if ((int)lines.size() < capacity) {
        lines.push_back({address, true, time});
    } else {
        // LRU eviction
        int lruIndex = 0;
        for (int i = 1; i < lines.size(); i++) {
            if (lines[i].lastUsed < lines[lruIndex].lastUsed)
                lruIndex = i;
        }
        lines[lruIndex] = {address, true, time};
    }

    return false; // MISS
}

void CacheLevel::printStats(const std::string& name) {
    std::cout << name << " Hits: " << hits
              << " Misses: " << misses << "\n";
}

MultiLevelCache::MultiLevelCache()
    : L1(4), L2(8), L3(16) {}

void MultiLevelCache::access(int address) {
    if (L1.access(address)) return;
    if (L2.access(address)) return;
    L3.access(address);
}

void MultiLevelCache::stats() {
    std::cout << "----- Cache Stats -----\n";
    L1.printStats("L1");
    L2.printStats("L2");
    L3.printStats("L3");
}
