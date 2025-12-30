# 🧠 OS Memory Management Simulator

A **C++ based Operating System Memory Management Simulator** that models how an OS manages physical memory allocation and deallocation using classical allocation strategies.
This project focuses on algorithmic correctness, fragmentation analysis, and system-level design, without implementing a real kernel. 



## 🎯 Overview

Memory management is one of the most fundamental responsibilities of an operating system. This project simulates the core behavior of physical memory management in a controlled user-space environment.
The simulator maintains a contiguous block of physical memory, processes dynamic allocation requests using different allocation strategies, and tracks fragmentation and utilization metrics.
Key goals:

- Understand dynamic memory allocation strategies and fragmentation.
- Simulate allocation and deallocation at runtime using different strategies. 
- Explore multi-level CPU cache behavior and replacement policies.
- Practice systems-level design (abstractions, modularity, metrics).



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



## 🧩 Planned / Optional Extensions

These are **defined in the project design** but not implemented in this repository yet; they are good candidates for future work. 

- **Buddy Allocation System**  
  - Power-of-two memory sizes, free lists per block size, recursive splitting and buddy coalescing.

- **Virtual Memory and Paging**  
  - Virtual address space, page tables, page faults, and page replacement strategies (FIFO, LRU, Clock, etc.). 
  - Integration with cache: virtual address → page table → physical address → cache → memory. 



## 🧩 Core Subsystems

### 1️⃣ Physical Memory Manager
- Simulates a contiguous region of physical memory
- Maintains a list of memory blocks
- Tracks allocated and free regions
- Ensures memory blocks never overlap



### 2️⃣ Allocation Engine
- Implements First Fit, Best Fit, and Worst Fit algorithms
- Searches free blocks based on selected strategy
- Splits blocks when allocating smaller portions
- Merges adjacent free blocks after deallocation



### 3️⃣ Fragmentation & Statistics Module
- Computes internal fragmentation
- Computes external fragmentation
- Tracks:
  - Total memory
  - Used memory
  - Free memory
  - Memory utilization
  - Allocation success and failure



### 4️⃣ Command-Line Interface (CLI)
- Accepts user commands interactively
- Displays allocation results and memory layout
- Provides real-time statistics and diagnostics



<h2> 🔄 Data Flow </h2>
The following sequence describes how a memory request is handled:

<pre>
  User Command
   ↓
Command Validation
   ↓
Allocation / Deallocation Request
   ↓
Allocator Strategy Selection
   ↓
Free Block Search
   ↓
Block Split / Merge
   ↓
Memory State Update
   ↓
Statistics Update
   ↓
Output to User

</pre>



## ⚙️ Installation

### Prerequisites
- C++17 compatible compiler (g++)
- GNU Make (optional but recommended)




<h2>📂 Project Structure</h2>

```text
os-memory-management-simulator/
├── docs/
│   └── Design_and_Implementation_of_a_Memory_Management_Simulator.pdf
├── include/
│   ├── allocator.h        # Memory allocation algorithms
│   ├── cache.h            # Cache-related structures (basic simulation)
│   ├── memory.h           # Physical memory representation
│   └── stats.h            # Statistics and fragmentation tracking
├── src/
│   ├── allocator.cpp      # Allocation and deallocation logic
│   ├── cache.cpp          # Cache simulation implementation
│   ├── memory.cpp         # Physical memory management
│   ├── stats.cpp          # Statistics computation
│   └── main.cpp           # Application entry point
├── tests/                 # Test cases and validation files
├── .gitignore
├── LICENSE
├── memsim.exe             # Compiled executable (Windows)
└── README.md              # Project documentation

```




## 🎨 Design Principles

### Core Assumptions

1. **Simulated Memory**  
   All memory is simulated in user space. No real memory pointers are returned to the user.

2. **Zero-Based Addressing**  
   All memory addresses are treated as offsets starting from `0`.

3. **External Metadata**  
   Allocation metadata (block size, status, IDs) is stored separately from the simulated memory.

4. **Deterministic Behavior**  
   Given the same sequence of commands, the simulator always produces the same results.

5. **Behavioral Model**  
   This project is a **memory management simulator**, not an actual operating system kernel.



### Invariants

- **Memory Conservation**  
  Total memory size remains constant throughout execution.

- **No Overlaps**  
  Allocated and free memory blocks never overlap.

- **Complete Coverage**  
  The sum of all block sizes always equals the total memory size.

- **Consistent State**  
  Internal data structures remain valid after every operation.

- **Unique Block IDs**  
  Every allocated memory block has a unique identifier.



### Development Approach

- **Incremental Implementation**  
  Features were added step-by-step and tested individually.

- **Correctness First**  
  Algorithmic correctness was prioritized over performance optimizations.

- **Modular Design**  
  Clear separation between allocation logica, memory representation, cache handling, and statistics.

- **Test-Driven Validation**  
  Allocation and deallocation behavior was tested using multiple scenarios.

- **Readable & Maintainable Code**  
  Emphasis on clarity and simplicity for educational understanding.


## 📦 Dependencies

### Build Dependencies

- **CMake 3.10+**
- **C++17 compliant compiler** (GCC / Clang / MSVC)



### Runtime Dependencies

- **C++ Standard Library (STL)**  
  - `<vector>` — Dynamic arrays for memory block storage  
  - `<list>` — Linked list representation of memory blocks  
  - `<unordered_map>` — Tracking allocated blocks by ID  
  - `<cstddef>, <cstdint>` — Standard data types  
  - `<iostream>` — Input/output and logging  
  - `<cmath>` — Mathematical utilities (e.g., size calculations)


No external third-party libraries are required.



## 🔍 Key Algorithms

### Physical Memory Allocation

The simulator implements classical **dynamic memory allocation strategies**.
All strategies operate on a list of memory blocks and run in **O(n)** time,
where *n* is the number of memory blocks.



#### First Fit — **O(n)**
Allocates the **first free block** that is large enough to satisfy the request.

```text
for each block:
    if block is free and block.size >= requested_size:
        allocate from this block
        break
```

#### Best Fit — **O(n)**
Allocates the **smallest free block** that can satisfy the request.

```text
best = null
for each block:
    if block is free and block.size >= requested_size:
        if best is null or block.size < best.size:
            best = block

```

#### Worst Fit — **O(n)**
Allocates the **largest available free block**.

```text
worst = null
for each block:
    if block is free and block.size >= requested_size:
        if worst is null or block.size > worst.size:
            worst = block

```

### Cache Access

The simulator includes a **basic cache access model** to demonstrate how memory accesses
interact with a cache layer before reaching physical memory.

The cache is modeled as a simple structure that tracks whether a requested memory
address is already cached (**cache hit**) or must be fetched from memory (**cache miss**).

---

#### Cache Read Operation — **O(1)**

```text
if address exists in cache:
    record cache hit
    return cached data
else:
    record cache miss
    load data from memory
    insert data into cache
    return data
```

