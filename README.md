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

| Strategy | Description | Best For |
|----------|-------------|----------|
| **First Fit** | Allocates the first free block large enough | Fast allocation |
| **Best Fit** | Allocates the smallest sufficient block | Minimizing wasted space |
| **Worst Fit** | Allocates the largest available block | Reducing fragmentation patterns |

### 3. Two-Level Cache System
- **L1 Cache**: Fast, small, first-level cache
- **L2 Cache**: Larger, second-level cache
- **FIFO Replacement**: First-In-First-Out eviction policy
- **Hit/Miss Statistics**: Track cache performance

### 4. Memory Coalescing
- Automatically merges adjacent free blocks when memory is freed
- Reduces external fragmentation

### 5. Real-Time Statistics
- Total, used, and free memory
- Memory utilization percentage
- Cache hit/miss ratios

---

## 🚀 Quick Start

### Prerequisites
- **C++17 compatible compiler** (g++, clang++, or MSVC)
- **GNU Make** (optional but recommended)

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
Memory initialized with size 1024 bytes

> malloc 100
Allocated block id=1 at address=0x0000

> malloc 200
Allocated block id=2 at address=0x0064

> dump
[0x0000 - 0x0063] USED (id=1)
[0x0064 - 0x012B] USED (id=2)
[0x012C - 0x03FF] FREE

> free 1
Block 1 freed

> stats
Total Memory: 1024 bytes
Used Memory: 200 bytes
Free Memory: 824 bytes
Memory Utilization: 19.5%

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
└── tests/                       # Test files (if any)
```

---

## 🔍 Key Algorithms

### Allocation Strategies

All strategies operate in **O(n)** time where n is the number of memory blocks.

```cpp
// First Fit - find first suitable block
for (auto& block : blocks) {
    if (block.free && block.size >= requested_size) {
        allocate(block);
        break;
    }
}

// Best Fit - find smallest suitable block
auto best = blocks.end();
for (auto it = blocks.begin(); it != blocks.end(); ++it) {
    if (it->free && it->size >= requested_size) {
        if (best == blocks.end() || it->size < best->size)
            best = it;
    }
}

// Worst Fit - find largest suitable block
auto worst = blocks.end();
for (auto it = blocks.begin(); it != blocks.end(); ++it) {
    if (it->free && it->size >= requested_size) {
        if (worst == blocks.end() || it->size > worst->size)
            worst = it;
    }
}
```

### Memory Coalescing

When freeing a block, adjacent free blocks are automatically merged:

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

### Cache FIFO Replacement

```cpp
void put(int key, int value) {
    if (data.size() >= capacity) {
        // Evict oldest entry
        int oldestKey = fifo.front();
        fifo.pop();
        data.erase(oldestKey);
    }
    data[key] = value;
    fifo.push(key);
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
