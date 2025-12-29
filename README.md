# 🧠 OS Memory Management Simulator

A **user-space simulator** of core operating system memory-management techniques, focusing on physical memory allocation and multi-level cache behavior.  
This project is designed as an educational tool to help understand how an OS allocates, frees, and caches memory without requiring kernel-level access.

> Note: Features like buddy allocation and full virtual memory paging are considered **future extensions** and are not implemented yet in this project.

---

## 🎯 Overview

This simulator models how an operating system manages memory using well-defined data structures and algorithms instead of real hardware.
All addresses are treated as offsets from zero in a simulated memory space, so the simulator is completely isolated from the host system memory.

Key goals:

- Understand dynamic memory allocation strategies and fragmentation.
- Simulate allocation and deallocation at runtime using different strategies. 
- Explore multi-level CPU cache behavior and replacement policies.
- Practice systems-level design (abstractions, modularity, metrics).

---

## ✨ Implemented Features

### 1. Physical Memory Simulation

- Simulated contiguous block of **physical memory** with configurable size (e.g., 1 KB, 4 KB, etc.). 
- Memory is dynamically divided based on allocation requests rather than fixed partitions.  
- Internal representation uses explicit metadata to track allocated and free blocks. 

#### Allocation Strategies

The simulator supports a **variable-size allocator** with the following strategies: 

- **First Fit** – choose the first free block that is large enough. 
- **Best Fit** – choose the smallest free block that can satisfy the request.  
- **Worst Fit** – choose the largest free block to reduce future fragmentation. 

On each `malloc`-like operation, the simulator:

- Searches for a suitable free block based on the selected strategy. 
- Splits blocks when needed and updates metadata. 

On each `free` operation, the simulator:

- Marks the block as free. 
- **Automatically coalesces** adjacent free blocks to reduce external fragmentation.

#### Metrics and Statistics

The simulator tracks and can report: 

- Total, used, and free memory.  
- Largest free block size.  
- Internal and external fragmentation.  
- Allocation success / failure rate and memory utilization (where implemented).  

---

### 2. Command-Line Interface

The simulator exposes a simple CLI-style interface to interact with the memory model.

Typical operations (names/format may differ depending on your implementation):

- Initialize memory:
  - `memsim init <memory_size>` – set up the physical memory size (e.g., `memsim init 1024`).
- Select allocation strategy:
  - `memsim set allocator firstfit|bestfit|worstfit`.
- Allocate memory:
  - `memsim malloc <size>` – allocate a block and print its id and starting address. 
- Free memory:
  - `memsim free <block_id>` – free the block with the given id and coalesce if possible.
- Dump / inspect memory:
  - `memsim dump` – show allocated and free regions along with basic statistics.

You can adapt the exact command names here to match your actual implementation.

---

### 3. Multilevel Cache Simulation

In addition to heap-like memory allocation, the simulator models a **multi-level CPU cache hierarchy** (for example, L1 and L2).

Configurable parameters per level:

- Cache size (number of lines / bytes).  
- Block size.  
- Associativity (direct-mapped or set-associative, depending on your implementation).  
- Replacement policy: at minimum **FIFO**; optional policies such as LRU/LFU can be added later. 

For each memory access, the simulator:

- Checks cache levels in order (e.g., L1 → L2 → main memory). 
- Records hits and misses at each level. 
- Updates cache state according to the chosen replacement policy.

Reported cache statistics can include:

- Hits and misses per cache level.  
- Hit ratio / miss ratio.  
- Effective access behavior (miss penalties if modeled).  

---

## 🧩 Planned / Optional Extensions

These are **defined in the project design** but not implemented in this repository yet; they are good candidates for future work. 

- **Buddy Allocation System**  
  - Power-of-two memory sizes, free lists per block size, recursive splitting and buddy coalescing.

- **Virtual Memory and Paging**  
  - Virtual address space, page tables, page faults, and page replacement strategies (FIFO, LRU, Clock, etc.). 
  - Integration with cache: virtual address → page table → physical address → cache → memory. 

---


---

## 📚 Documentation

This repository is accompanied by a design document: **“Design and Implementation of a Memory Management Simulator”**, which explains: [file:2]

- Memory layout assumptions and data structures.  
- Allocation strategies and fragmentation handling.  
- Cache hierarchy, parameters, and replacement policies.  
- Planned virtual memory model and address translation pipeline. [file:2]

For background theory, the design references standard OS texts such as *Operating System Concepts* and *Modern Operating Systems*, as well as GATE Smashers and GeeksforGeeks resources on memory management. [file:2]

---

## 👩‍💻 Author

- **Tamanna Khudiya** – Developer of this memory management simulator.

Feel free to open issues or pull requests for bug fixes, improvements, or new features like buddy allocation and full virtual memory support.


