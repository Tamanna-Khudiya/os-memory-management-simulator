#ifndef CACHE_H
#define CACHE_H

#include <unordered_map>
#include <queue>
#include <string>


class CacheLevel {
private:
    int capacity;
    std::unordered_map<int, int> data;
    std::queue<int> fifo;

public:
    CacheLevel(int cap);

    bool contains(int key);
    int get(int key);
    void put(int key, int value);
    void display(const std::string& name) const;
};


class TwoLevelCache {
private:
    CacheLevel L1;
    CacheLevel L2;

    int l1Hits;
    int l1Misses;
    int l2Hits;
    int l2Misses;

public:
    TwoLevelCache(int l1Size, int l2Size);

    int get(int key);
    void put(int key, int value);
    void display() const;
    void stats() const;
};

#endif
