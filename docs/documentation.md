# OS Memory Management Simulator - Documentation

**Version:** 1.0  
**Author:** Tamanna Khudiya  
**Repository:** https://github.com/Tamanna-Khudiya/os-memory-management-simulator

---

## Table of Contents

1. [Overview](#overview)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage Guide](#usage-guide)
5. [Architecture](#architecture)
6. [Algorithms](#algorithms)
7. [Examples](#examples)
8. [File Structure](#file-structure)

---

## Overview

The **OS Memory Management Simulator** is a C++ based educational tool that simulates core memory management techniques of an operating system. It demonstrates dynamic memory allocation, deallocation, fragmentation handling, and cache behavior in a controlled, simulated environment.

### Purpose

- **Educational Tool**: Learn how operating systems manage memory
- **Algorithm Visualization**: See how different allocation strategies work
- **Performance Analysis**: Understand fragmentation and memory utilization
- **Cache Simulation**: Observe cache hits, misses, and replacement policies

### Key Concepts Demonstrated

- **Contiguous Memory Allocation**: Managing a single block of memory
- **Dynamic Partitioning**: Allocating variable-sized memory blocks
- **Fragmentation**: Internal and external fragmentation analysis
- **Memory Coalescing**: Merging adjacent free blocks
- **Cache Hierarchy**: Two-level cache with FIFO replacement

---

## Features

### 1. Physical Memory Simulation

- Simulates contiguous memory with configurable size
- Tracks allocated and free memory regions
- Maintains metadata for each memory block
- Provides real-time statistics and diagnostics

### 2. Allocation Strategies

| Strategy | Description | Use Case |
|----------|-------------|----------|
| **First Fit** | Allocates first available block large enough | Fast allocation, moderate fragmentation |
| **Best Fit** | Allocates smallest sufficient block | Minimizes wasted space |
| **Worst Fit** | Allocates largest available block | Reduces fragmentation in specific patterns |

### 3. Two-Level Cache System

- **L1 Cache**: Fast, small, first-level cache
- **L2 Cache**: Larger, slower, second-level cache
- **FIFO Replacement**: First-In-First-Out eviction policy
- **Hit/Miss Tracking**: Records cache performance statistics

### 4. Memory Statistics

- Total, used, and free memory
- Number of allocated blocks
- Memory utilization percentage
- Cache hit/miss ratios

---

## Installation

### Prerequisites

- **C++ Compiler**: GCC, Clang, or MSVC with C++17 support
- **Build Tools**: Make or CMake (optional)
- **Operating System**: Windows, Linux, or macOS

### Compilation (Windows with g++)

```bash
# Navigate to project directory
cd memory-simulator

# Compile all source files
g++ -std=c++17 -o memsim src/main.cpp src/memory.cpp src/allocator.cpp src/cache.cpp

# Run the simulator
memsim.exe
```

### Compilation (Linux/macOS)

```bash
# Navigate to project directory
cd memory-simulator

# Compile all source files
g++ -std=c++17 -o memsim src/main.cpp src/memory.cpp src/allocator.cpp src/cache.cpp

# Run the simulator
./memsim
```

---

## Usage Guide

### Command Reference

#### Memory Initialization

```bash
init memory <size>
```

Initializes the simulated memory with the specified size (in bytes).

**Example:**
```bash
init memory 1024
# Output: Memory initialized with size 1024 bytes
```

#### Memory Allocation

```bash
malloc <size>
```

Allocates a memory block of the specified size.

**Example:**
```bash
malloc 100
# Output: Allocated block id=1 at address=0x0000 (size=100)
```

#### Memory Deallocation

```bash
free <block_id>
```

Frees the allocated block with the specified ID.

**Example:**
```bash
free 1
# Output: Block 1 freed
```

#### Memory Dump

```bash
dump
```

Displays the current memory layout showing all allocated and free blocks.

**Example Output:**
```
[0x0000 - 0x0063] USED (id=1)
[0x0064 - 0x012B] USED (id=2)
[0x012C - 0x03FF] FREE
```

#### Statistics

```bash
stats
```

Displays memory statistics including total size, used memory, free memory, and utilization.

**Example Output:**
```
Total Memory: 1024 bytes
Used Memory: 300 bytes
Free Memory: 724 bytes
Memory Utilization: 29.3%
```

#### Set Allocation Strategy

```bash
set allocator <strategy>
```

Changes the allocation strategy.

**Available Strategies:**
- `first_fit` - First Fit algorithm
- `best_fit` - Best Fit algorithm
- `worst_fit` - Worst Fit algorithm

**Example:**
```bash
set allocator best_fit
# Output: Allocator changed
```

#### Cache Operations

```bash
cache init <l1_size> <l2_size>
```

Initializes the two-level cache with specified L1 and L2 sizes.

**Example:**
```bash
cache init 5 10
# Output: Cache initialized (L1=5, L2=10)
```

```bash
cache access <address>
```

Accesses data at the specified memory address through the cache hierarchy.

**Example:**
```bash
cache access 100
# Output: L1 MISS -> L2 MISS -> MEMORY ACCESS
```

```bash
cache put <address> <value>
```

Inserts data into the cache.

**Example:**
```bash
cache put 100 42
# Output: Inserted address 100 with value 42
```

```bash
cache display
```

Displays the current cache contents.

```bash
cache stats
```

Displays cache statistics including hits, misses, and hit ratios.

#### Exit Simulator

```bash
exit
```

Exits the memory management simulator.

---

## Architecture

### Class Diagram

```
Memory Management Simulator
├── Memory
│   ├── totalSize: int
│   └── blocks: std::list<Block>
│   ├── init(size)
│   ├── dump()
│   ├── getBlocks()
│   └── printStats()
│
├── Allocator
│   ├── nextId: int
│   ├── currentType: AllocatorType
│   ├── setAllocator(type)
│   ├── mallocMemory(mem, size)
│   ├── mallocFirstFit(mem, size)
│   ├── mallocBestFit(mem, size)
│   ├── mallocWorstFit(mem, size)
│   └── freeBlock(mem, id)
│
├── CacheLevel
│   ├── capacity: int
│   ├── data: std::unordered_map<int, int>
│   ├── fifo: std::queue<int>
│   ├── contains(key)
│   ├── get(key)
│   ├── put(key, value)
│   └── display(name)
│
└── TwoLevelCache
    ├── L1: CacheLevel
    ├── L2: CacheLevel
    ├── l1Hits, l1Misses: int
    ├── l2Hits, l2Misses: int
    ├── memoryAccesses: int
    ├── get(key)
    ├── put(key, value)
    ├── display()
    └── stats()
```

### Data Structures

#### Block Structure

```cpp
struct Block {
    int start;      // Starting address of the block
    int size;       // Size of the block in bytes
    bool free;      // true if block is free, false if allocated
    int id;         // Block ID (-1 if free)
};
```

#### Memory List

Memory is stored as a doubly-linked list of blocks using `std::list<Block>`.

#### Cache Storage

Cache uses:
- `std::unordered_map<int, int>` for O(1) key-value lookup
- `std::queue<int>` for FIFO replacement order

---

## Algorithms

### First Fit Algorithm

The First Fit algorithm searches for the first available block large enough to satisfy the allocation request.

```
for each block in memory:
    if block is free AND block.size >= requested_size:
        allocate from this block
        break
```

**Characteristics:**
- Time Complexity: O(n)
- Fast allocation (finds first suitable block)
- May lead to more external fragmentation

### Best Fit Algorithm

The Best Fit algorithm searches for the smallest free block that can satisfy the request.

```
best = null
for each block in memory:
    if block is free AND block.size >= requested_size:
        if best == null OR block.size < best.size:
            best = block

if best != null:
    allocate from best
```

**Characteristics:**
- Time Complexity: O(n)
- Minimizes wasted space
- Can lead to more small fragments

### Worst Fit Algorithm

The Worst Fit algorithm searches for the largest available block.

```
worst = null
for each block in memory:
    if block is free AND block.size >= requested_size:
        if worst == null OR block.size > worst.size:
            worst = block

if worst != null:
    allocate from worst
```

**Characteristics:**
- Time Complexity: O(n)
- Leaves larger blocks available
- Can work well for certain access patterns

### FIFO Cache Replacement

When the cache is full and a new block must be inserted, the oldest cache entry is evicted.

```
if cache is full:
    evict oldest entry (from front of queue)
    remove from hash map
insert new entry at back of queue
add to hash map
```

**Characteristics:**
- Simple implementation
- No consideration of access frequency
- Can suffer from Belady's anomaly

### Memory Coalescing

When a block is freed, adjacent free blocks are merged to reduce fragmentation.

```
mark current block as free
if next block is free:
    merge with next block
if previous block is free:
    merge with previous block
```

---

## Examples

### Example 1: Basic Memory Operations

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

> dump
[0x0000 - 0x0063] FREE
[0x0064 - 0x012B] USED (id=2)
[0x012C - 0x03FF] FREE
```

### Example 2: Changing Allocation Strategy

```
> init memory 1024
> set allocator best_fit
Allocator changed

> malloc 100
Allocated (Best Fit) id=1 at address=0x0000

> malloc 200
Allocated (Best Fit) id=2 at address=0x0064
```

### Example 3: Cache Operations

```
> cache init 5 10
Cache initialized (L1=5, L2=10)

> cache put 100 42
Inserted address 100 with value 42

> cache access 100
Cache HIT, value = 42

> cache access 200
L1 MISS -> L2 MISS -> MEMORY ACCESS

> cache stats
L1 Hits: 1, Misses: 1
L2 Hits: 0, Misses: 2
Memory Accesses: 1
```

### Example 4: Fragmentation Analysis

```
> init memory 2048
> malloc 500
Allocated block id=1 at address=0x0000
> malloc 500
Allocated block id=2 at address=0x01F4
> malloc 500
Allocated block id=3 at address=0x03E8
> free 2
Block 2 freed
> dump
[0x0000 - 0x01F3] USED (id=1)
[0x01F4 - 0x03E7] FREE
[0x03E8 - 0x05DB] USED (id=3)
[0x05DC - 0x07FF] FREE

> stats
Total Memory: 2048 bytes
Used Memory: 1000 bytes
Free Memory: 1048 bytes
Memory Utilization: 48.8%
```

---

## File Structure

```
memory-simulator/
├── .gitignore
├── LICENSE
├── README.md
├── docs/
│   ├── design.md              # Design document
│   └── documentation.md       # This file
├── include/
│   ├── allocator.h            # Memory allocation strategies
│   ├── cache.h                # Two-level cache implementation
│   └── memory.h               # Memory management class
├── src/
│   ├── allocator.cpp          # Allocator implementation
│   ├── cache.cpp              # Cache implementation
│   ├── memory.cpp             # Memory management implementation
│   └── main.cpp               # CLI interface
└── tests/                      # Test files (if any)
```

---

## Contributing

Contributions are welcome! Please feel free to submit issues and pull requests.

### Suggested Improvements

- Add more cache replacement policies (LRU, LFU, Clock)
- Implement buddy allocation system
- Add virtual memory and paging simulation
- Create automated test suite
- Add visualization capabilities

---

## Learning Resources

- **Operating System Concepts** - Silberschatz, Galvin, and Gagne
- **Modern Operating Systems** - Andrew S. Tanenbaum
- **GeeksForGeeks - Operating Systems**: https://www.geeksforgeeks.org/operating-systems/
- **Gate Smashers (YouTube)**: https://www.youtube.com/playlist?list=PLxCzCOWd7aiGz9donHRrE9I3Mwn6XdP8p

---

## License

This project is licensed under the MIT License. See the LICENSE file for details.

---

## Acknowledgments

- Course instructors for guidance on operating systems concepts
- Academic textbooks and online learning platforms
- Open-source OS simulation projects
- GitHub community for best practices
