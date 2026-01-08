# 🧠 OS Memory Management Simulator

A **C++ based Operating System Memory Management Simulator** that demonstrates how an operating system manages **physical memory allocation, deallocation, fragmentation, and basic cache behavior**.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)

---

## 🎯 Overview

Memory management is a fundamental responsibility of an operating system. It involves allocating memory efficiently, reclaiming unused memory, and minimizing fragmentation.

This simulator models a **contiguous block of physical memory** and supports dynamic allocation and deallocation using classical allocation strategies. It also includes a **two-level cache simulation** to demonstrate cache hits and misses during memory access.

The project focuses on **algorithmic correctness, clarity, and learning**, rather than hardware-level accuracy.

---

## ✨ Features

### 1. Physical Memory Simulation

- Simulated contiguous block of **physical memory** with configurable size
- Memory is dynamically divided based on allocation requests
- Internal representation uses explicit metadata to track allocated and free blocks

### 2. Allocation Strategies

The simulator supports three allocation algorithms:

| Strategy | Description | Time Complexity |
|----------|-------------|-----------------|
| **First Fit** | Allocates the first free block that is large enough | O(n) |
| **Best Fit** | Allocates the smallest free block that can satisfy the request | O(n) |
| **Worst Fit** | Allocates the largest available free block | O(n) |

### 3. Memory Coalescing

When a block is freed, adjacent free blocks are automatically merged:

```cpp
// Merge with next block if free
if (next != blocks.end() && next->free) {
    current.size += next.size;
    blocks.erase(next);
}

// Merge with previous block if free
if (prev != blocks.begin() && prev->free) {
    prev.size += current.size;
    blocks.erase(current);
}
```

### 4. Two-Level Cache System

- **L1 Cache**: Fast, small, first-level cache
- **L2 Cache**: Larger, second-level cache
- **FIFO Replacement**: First-In-First-Out eviction policy

### 5. Statistics and Metrics

The simulator tracks:
- Total, used, and free memory
- Memory utilization percentage
- External fragmentation percentage

---

## 🚀 Quick Start

### Prerequisites

- **C++17 compatible compiler** (g++, clang++, or MSVC)

### Compilation

```bash
# Windows (with g++)
g++ -std=c++17 -o memsim src/main.cpp src/memory.cpp src/allocator.cpp src/cache.cpp

# Linux/macOS
g++ -std=c++17 -o memsim src/main.cpp src/memory.cpp src/allocator.cpp src/cache.cpp
```

### Running the Simulator

```bash
# Windows
memsim.exe

# Linux/macOS
./memsim
```

---

## 📖 Usage Guide

### Basic Commands

| Command | Description |
|---------|-------------|
| `init memory <size>` | Initialize memory with specified size |
| `malloc <size>` | Allocate a memory block |
| `free <block_id>` | Free an allocated block |
| `dump` | Display memory layout |
| `stats` | Show memory statistics |
| `set allocator <strategy>` | Change allocation strategy |

### Cache Commands

| Command | Description |
|---------|-------------|
| `cache init <l1_size> <l2_size>` | Initialize two-level cache |
| `cache put <address> <value>` | Insert data into cache |
| `cache access <address>` | Access data through cache |
| `cache display` | Show cache contents |
| `cache stats` | Display cache statistics |

### Example Session

```
> init memory 1024
Memory initialized with size 1024

> malloc 100
Allocated block id=1 at address=0x0

> malloc 200
Allocated block id=2 at address=0x64

> dump
----- Memory Dump -----
[0x0 - 0x63] USED (id=1)
[0x64 - 0x10b] USED (id=2)
[0x10c - 0x3ff] FREE

> free 1
Block 1 freed

> stats
----- Memory Stats -----
Total memory: 1024
Used memory: 200
Free memory: 824
Memory utilization: 19.5312%
External fragmentation: 0%

> exit
```

---

## 🏗️ Architecture

### Core Components

```
┌─────────────────────────────────────────────────────────┐
│                    Memory Simulator                      │
├─────────────────────────────────────────────────────────┤
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────────┐  │
│  │   Memory    │  │  Allocator  │  │ TwoLevelCache   │  │
│  │             │  │             │  │                 │  │
│  │ - totalSize │  │ - First Fit │  │ - L1 Cache      │  │
│  │ - blocks    │  │ - Best Fit  │  │ - L2 Cache      │  │
│  │             │  │ - Worst Fit │  │ - FIFO Policy   │  │
│  └─────────────┘  └─────────────┘  └─────────────────┘  │
└─────────────────────────────────────────────────────────┘
```

### Data Structures

- **Memory**: `std::list<Block>` - Linked list of memory blocks
- **Cache**: `std::unordered_map<int, int>` + `std::queue<int>` - Hash map for O(1) access with FIFO ordering

### Block Structure

```cpp
struct Block {
    int start;      // Starting address of the block
    int size;       // Size of the block in bytes
    bool free;      // true if block is free, false if allocated
    int id;         // Block ID (-1 if free)
};
```

---

## 📂 Project Structure

```
memory-simulator/
├── .gitignore
├── LICENSE
├── README.md                    # This file
├── docs/
│   ├── design.md               # Design document
│   └── documentation.md        # Full documentation
├── include/
│   ├── allocator.h             # Memory allocation strategies
│   ├── cache.h                 # Two-level cache implementation
│   └── memory.h                # Memory management class
├── src/
│   ├── allocator.cpp           # Allocator implementation
│   ├── cache.cpp               # Cache implementation
│   ├── memory.cpp              # Memory management implementation
│   └── main.cpp                # CLI interface
└── tests/
    ├── test_cases.txt          # Test cases
    ├── expected_output.txt     # Expected outputs
    └── test_runner.cpp         # Test runner
```

---

## 🔍 Key Algorithms

### First Fit Algorithm — O(n)

Allocates the **first free block** that is large enough to satisfy the request.

```cpp
for (auto it = blocks.begin(); it != blocks.end(); ++it) {
    if (it->free && it->size >= size) {
        // Allocate from this block
        it->start += size;
        it->size -= size;
        return allocated.id;
    }
}
```

### Best Fit Algorithm — O(n)

Allocates the **smallest free block** that can satisfy the request.

```cpp
auto best = blocks.end();
for (auto it = blocks.begin(); it != blocks.end(); ++it) {
    if (it->free && it->size >= size) {
        if (best == blocks.end() || it->size < best->size) {
            best = it;
        }
    }
}
```

### Worst Fit Algorithm — O(n)

Allocates the **largest available free block**.

```cpp
auto worst = blocks.end();
for (auto it = blocks.begin(); it != blocks.end(); ++it) {
    if (it->free && it->size >= size) {
        if (worst == blocks.end() || it->size > worst->size) {
            worst = it;
        }
    }
}
```

### Memory Coalescing

When a block is freed, adjacent free blocks are automatically merged to reduce fragmentation.

```cpp
void freeBlock(Memory &mem, int id) {
    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (!it->free && it->id == id) {
            it->free = true;
            it->id = -1;

            // Merge with next block
            auto next = it;
            ++next;
            if (next != blocks.end() && next->free) {
                it->size += next->size;
                blocks.erase(next);
            }

            // Merge with previous block
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
}
```

### Cache FIFO Replacement

When the cache is full, the oldest entry is evicted.

```cpp
void put(int key, int value) {
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
```

### Two-Level Cache Access

```cpp
int get(int key) {
    // Check L1 first
    if (L1.contains(key)) {
        l1Hits++;
        return L1.get(key);
    }

    l1Misses++;

    // Check L2
    if (L2.contains(key)) {
        l2Hits++;
        int value = L2.get(key);
        L1.put(key, value);  // Promote to L1
        return value;
    }

    l2Misses++;
    memoryAccesses++;
    int value = key;  // Simulate memory access
    L2.put(key, value);
    L1.put(key, value);
    return value;
}
```

---

## 🧪 Testing

The simulator has been tested with:

- ✅ Sequential allocations of varying sizes
- ✅ Random allocations and deallocations
- ✅ Memory coalescing verification
- ✅ Fragmentation analysis
- ✅ Cache hit/miss behavior
- ✅ Allocation failure handling
- ✅ Invalid free requests

### Running Tests

```bash
# Compile test runner
g++ -std=c++17 -o test_runner tests/test_runner.cpp

# Run tests
./test_runner

# Or test manually
g++ -std=c++17 -o memsim src/main.cpp src/memory.cpp src/allocator.cpp src/cache.cpp
./memsim < tests/test_cases.txt
```

---

## 📚 Learning Resources

- [Operating System Concepts - Silberschatz, Galvin, and Gagne](https://www.amazon.com/Operating-System-Concepts-Abraham-Silberschatz/dp/1118063333)
- [Modern Operating Systems - Andrew S. Tanenbaum](https://www.amazon.com/Modern-Operating-Systems-Andrew-Tanenbaum/dp/013359162X)
- [GeeksForGeeks - Operating Systems](https://www.geeksforgeeks.org/operating-systems/)
- [Gate Smashers - OS Playlist (YouTube)](https://www.youtube.com/playlist?list=PLxCzCOWd7aiGz9donHRrE9I3Mwn6XdP8p)

---

## 🤝 Contributing

Contributions are welcome! Feel free to:

- Report bugs
- Suggest new features
- Submit pull requests
- Improve documentation

### Suggested Improvements

- Add more cache replacement policies (LRU, LFU, Clock)
- Implement buddy allocation system
- Add virtual memory and paging simulation
- Create automated test suite
- Add visualization capabilities

---

## 📜 License

This project is licensed under the **MIT License**.

You are free to:
- Use the code for educational purposes
- Modify and distribute the project
- Build upon the project for academic or personal use

See the `LICENSE` file for full details.

---

## 🙏 Acknowledgments

- Course instructors for guidance on operating systems concepts
- Academic textbooks and online learning platforms for reference material
- Open-source OS simulation projects that inspired project structure
- GitHub community for documentation and best practices

---

## 📧 Contact

**Author:** Tamanna Khudiya  
**Repository:** https://github.com/Tamanna-Khudiya/os-memory-management-simulator

---

⭐ **Star this repository if you found it helpful!**

## Demo Vedio
<img width="1888" height="838" alt="image" src="https://github.com/user-attachments/assets/d49219fc-00cb-4e64-97be-a59c0c3e61ea" />


