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

The cache subsystem uses a **First-In First-Out (FIFO)** replacement policy.
When the cache is full and a new block must be inserted, the **oldest cache entry**
(the one that entered first) is evicted.

FIFO is simple to implement and helps demonstrate basic cache behavior,
though it does not consider access frequency or recency.



#### Cache Read Operation — **O(1)**

```text
if address exists in cache:
    record cache hit
    return cached data
else:
    record cache miss
    if cache is full:
        evict oldest cache entry (FIFO)
    load data from memory
    insert data into cache
    return data
```

#### Cache Write Operation — **O(1)**

```text
write data to memory
if address exists in cache:
    update cache entry
else:
    if cache is full:
        evict oldest cache entry (FIFO)
    insert updated data into cache

```


## 🧪 Testing and Validation

This section describes how the memory management simulator was tested for
correctness, consistency, and expected behavior based on controlled input
patterns and output verification.



### Physical Memory Allocator Tests

The memory allocator component was tested using multiple allocation and
deallocation scenarios to ensure correct memory behavior.

#### Test Scenarios
- **Sequential allocations** of varying sizes
- **Randomized allocations and deallocations**
- **Deallocation patterns** (free in different orders)
- **Boundary conditions** (full memory use, no free space)
- **Reuse of freed blocks** to verify coalescing

#### Validation Criteria
- Memory is allocated only when free space is sufficient
- Freed blocks are correctly marked and reused
- Adjacent free blocks are coalesced to reduce fragmentation
- Allocated blocks never overlap
- Total memory size remains consistent



### Fragmentation Metrics Verification

After each allocation and deallocation operation, fragmentation
measurements were verified for correctness.

#### Checks Performed
- Internal fragmentation is tracked after allocation
- External fragmentation reflects the distribution of free blocks
- Coalescing reduces external fragmentation as expected
- Memory utilization statistics update correctly



### Cache-Related Tests (if implemented)

If the cache subsystem is enabled (via `cache.h` / `cache.cpp`), simple tests
were performed to validate basic cache behavior.

#### Test Scenarios
- Repeated access to the **same address** to generate cache hits
- Accessing **new addresses** to trigger cache misses
- Mixed access patterns to verify hit/miss count

#### Validation Criteria
- Cache hits and misses are recorded accurately
- Cache hit ratio is computed correctly
- Cache data does not corrupt memory state




### Integration Tests

The integration between allocator, memory, and statistics components was
validated through combined operations.

#### Checks Performed
- Allocator and memory manager remain consistent under long command sequences
- Statistics reflect the combined effects of multiple operations
- No memory corruption occurs during interdependent operations



### Manual Testing

Since there is no automated test suite in this version, manual testing was
used extensively:

- Commands like `malloc` and `free` were used in multiple sequences
- Output of `dump memory` was visually inspected
- Statistics output was compared with expected values
- Repeated tests produced deterministic results



### Known Limitations

- No automated test framework is currently integrated
- Performance benchmarking is not included
- Detailed stress testing is not present

Overall, the test cases provide confidence in the correctness of the
simulator for typical memory management scenarios.


## 🧾 Example Test Commands and Expected Output

The following examples demonstrate typical test cases used to validate
memory allocation, deallocation, fragmentation handling, and statistics
reporting.

---

### Test Case 1: Initialize Memory and Allocate Blocks

**Commands**
```text
init memory 1024
set allocator first_fit
malloc 100
malloc 200
```

**Expected Output**
```text
Memory initialized with size 1024 bytes
Allocator set to First Fit

Allocated block id=1 at address=0x0000 (size=100)
Allocated block id=2 at address=0x0064 (size=200)
```

### Test Case 2: Free a Block and Verify Coalescing

**Commands**
```text
free 1
dump memory
```

**Expected Output**
```text
Block id=1 freed successfully

[0x0000 - 0x0063] FREE
[0x0064 - 0x012B] USED (id=2)
[0x012C - 0x03FF] FREE
```

### Test Case 3: Reuse Freed Memory
**Commands**
```text
malloc 50
dump memory
```

**Expected Output**
```text
Allocated block id=3 at address=0x0000 (size=50)

[0x0000 - 0x0031] USED (id=3)
[0x0032 - 0x0063] FREE
[0x0064 - 0x012B] USED (id=2)
[0x012C - 0x03FF] FREE
```

### Test Case 4: Fragmentation and Statistics
**Commands**
```text
stats
```

**Expected Output**
```text
Total Memory: 1024 bytes
Used Memory: 250 bytes
Free Memory: 774 bytes

Internal Fragmentation: 0 bytes
External Fragmentation: <calculated percentage>
Memory Utilization: <calculated percentage>
```



