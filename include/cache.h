#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <string>

struct CacheLine {
    int address;
    bool valid;
    int lastUsed;
};

class CacheLevel {
private:
    int capacity;
    int time;
    int hits;
    int misses;
    std::vector<CacheLine> lines;

public:
    CacheLevel(int cap);
    bool access(int address);
    void printStats(const std::string& name);
};

class MultiLevelCache {
private:
    CacheLevel L1;
    CacheLevel L2;
    CacheLevel L3;

public:
    MultiLevelCache();
    void access(int address);
    void stats();
};

#endif
