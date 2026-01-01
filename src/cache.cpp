#include "../include/cache.h"
#include <iostream>



CacheLevel::CacheLevel(int cap) : capacity(cap) {}

bool CacheLevel::contains(int key) {
    return data.find(key) != data.end();
}

int CacheLevel::get(int key) {
    if (!contains(key))
        return -1;
    return data[key];
}

void CacheLevel::put(int key, int value) {
   
    if (contains(key)) {
        data[key] = value;
        return;
    }

    
    if ((int)data.size() == capacity) {
        int oldKey = fifo.front();
        fifo.pop();
        data.erase(oldKey);
    }

    data[key] = value;
    fifo.push(key);
}

void CacheLevel::display(const std::string& name) const {
    std::cout << name << " Cache: ";
    std::queue<int> temp = fifo;

    while (!temp.empty()) {
        int key = temp.front();
        temp.pop();
        std::cout << "[" << key << ":" << data.at(key) << "] ";
    }
    std::cout << "\n";
}



TwoLevelCache::TwoLevelCache(int l1Size, int l2Size)
    : L1(l1Size), L2(l2Size),
      l1Hits(0), l1Misses(0),
      l2Hits(0), l2Misses(0) {}

int TwoLevelCache::get(int key) {
    
    if (L1.contains(key)) {
        l1Hits++;
        return L1.get(key);
    }

    l1Misses++;

   
    if (L2.contains(key)) {
        l2Hits++;
        int value = L2.get(key);
        L1.put(key, value); 
        return value;
    }

    l2Misses++;
    return -1; 
}

void TwoLevelCache::put(int key, int value) {
    L1.put(key, value);
    L2.put(key, value);
}

void TwoLevelCache::display() const {
    L1.display("L1");
    L2.display("L2");
}

void TwoLevelCache::stats() const {
    std::cout << "----- Cache Statistics -----\n";
    std::cout << "L1 Hits: " << l1Hits << " | L1 Misses: " << l1Misses << "\n";
    std::cout << "L2 Hits: " << l2Hits << " | L2 Misses: " << l2Misses << "\n";
}
