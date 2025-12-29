# 🧠 OS Memory Management Simulator

A **user-space simulator** of core operating system memory-management techniques, focusing on physical memory allocation and multi-level cache behavior.  
This project is designed as an educational tool to help understand how an OS allocates, frees, and caches memory without requiring kernel-level access. [file:2]

> Note: Features like buddy allocation and full virtual memory paging are considered **future extensions** and are not implemented yet in this project. [file:2]

---

## 🎯 Overview

This simulator models how an operating system manages memory using well-defined data structures and algorithms instead of real hardware. [file:2]  
All addresses are treated as offsets from zero in a simulated memory space, so the simulator is completely isolated from the host system memory. [file:2]

Key goals:

- Understand dynamic memory allocation strategies and fragmentation. [file:2]  
- Simulate allocation and deallocation at runtime using different strategies. [file:2]  
- Explore multi-level CPU cache behavior and replacement policies. [file:2]  
- Practice systems-level design (abstractions, modularity, metrics). [file:2]

---

## ✨ Implemented Features

### 1. Physical Memory Simulation

- Simulated contiguous block of **physical memory** with configurable size (e.g., 1 KB, 4 KB, etc.). [file:2]  
- Memory is dynamically divided based on allocation requests rather than fixed partitions. [file:2]  
- Internal representation uses explicit metadata to track allocated and free blocks. [file:2]

#### Allocation Strategies

The simulator supports a **variable-size allocator** with the following strategies: [file:2]

- **First Fit** – choose the first free block that is large enough. [file:2]  
- **Best Fit** – choose the smallest free block that can satisfy the request. [file:2]  
- **Worst Fit** – choose the largest free block to reduce future fragmentation. [file:2]

On each `malloc`-like operation, the simulator:

- Searches for a suitable free block based on the selected strategy. [file:2]  
- Splits blocks when needed and updates metadata. [file:2]

On each `free` operation, the simulator:

- Marks the block as free. [file:2]  
- **Automatically coalesces** adjacent free blocks to reduce external fragmentation. [file:2]

#### Metrics and Statistics

The simulator tracks and can report: [file:2]

- Total, used, and free memory.  
- Largest free block size.  
- Internal and external fragmentation.  
- Allocation success / failure rate and memory utilization (where implemented).  

---

### 2. Command-Line Interface

The simulator exposes a simple CLI-style interface to interact with the memory model. [file:2]

Typical operations (names/format may differ depending on your implementation):

- Initialize memory:
  - `memsim init <memory_size>` – set up the physical memory size (e.g., `memsim init 1024`). [file:2]
- Select allocation strategy:
  - `memsim set allocator firstfit|bestfit|worstfit`. [file:2]
- Allocate memory:
  - `memsim malloc <size>` – allocate a block and print its id and starting address. [file:2]
- Free memory:
  - `memsim free <block_id>` – free the block with the given id and coalesce if possible. [file:2]
- Dump / inspect memory:
  - `memsim dump` – show allocated and free regions along with basic statistics. [file:2]

You can adapt the exact command names here to match your actual implementation.

---

### 3. Multilevel Cache Simulation

In addition to heap-like memory allocation, the simulator models a **multi-level CPU cache hierarchy** (for example, L1 and L2). [file:2]

Configurable parameters per level: [file:2]

- Cache size (number of lines / bytes).  
- Block size.  
- Associativity (direct-mapped or set-associative, depending on your implementation).  
- Replacement policy: at minimum **FIFO**; optional policies such as LRU/LFU can be added later. [file:2]

For each memory access, the simulator:

- Checks cache levels in order (e.g., L1 → L2 → main memory). [file:2]  
- Records hits and misses at each level. [file:2]  
- Updates cache state according to the chosen replacement policy. [file:2]

Reported cache statistics can include: [file:2]

- Hits and misses per cache level.  
- Hit ratio / miss ratio.  
- Effective access behavior (miss penalties if modeled).  

---

## 🧩 Planned / Optional Extensions

These are **defined in the project design** but not implemented in this repository yet; they are good candidates for future work. [file:2]

- **Buddy Allocation System**  
  - Power-of-two memory sizes, free lists per block size, recursive splitting and buddy coalescing. [file:2]

- **Virtual Memory and Paging**  
  - Virtual address space, page tables, page faults, and page replacement strategies (FIFO, LRU, Clock, etc.). [file:2]  
  - Integration with cache: virtual address → page table → physical address → cache → memory. [file:2]

---

## 🛠️ Project Structure

A recommended (and roughly followed) layout for the codebase is: [file:2]

