# 🧠 OS Memory Management Simulator

A **C++ based Operating System Memory Management Simulator** that demonstrates how memory allocation, deallocation, and cache behavior work inside an operating system.  
This project is designed for **educational and academic purposes** to understand core OS memory concepts through simulation.

---

## 📌 Features Implemented

### ✅ Physical Memory Simulation
- Initializes a fixed-size physical memory.
- Represents memory as a list of blocks.
- Each block contains:
  - Start address
  - Size
  - Allocation status (free / used)
  - Block ID

---

### ✅ Dynamic Memory Allocation
- Supports dynamic allocation similar to `malloc`.
- Allocates memory blocks sequentially.
- Automatically splits free blocks when partial allocation is required.

---

### ✅ Memory Deallocation
- Supports freeing allocated memory using block ID.
- Marks blocks as free after deallocation.
- Handles basic block merging logic.

---

### ✅ Memory Dump / Visualization
- Displays current memory layout.
- Clearly shows:
  - Used blocks
  - Free blocks
  - Address ranges
  - Block IDs

---

### ✅ Allocation Statistics
- Tracks:
  - Total memory
  - Used memory
  - Free memory
  - Number of allocated blocks

---

### ✅ Multilevel Cache Simulation
- Simulates cache access for memory operations.
- Tracks:
  - Cache hits
  - Cache misses
- Helps visualize how cache improves memory access performance.

---

## ❌ Features Not Implemented (Yet)

- Buddy Allocation System  
- Virtual Memory Simulation (Paging / Segmentation)

> These features are optional extensions and can be added later.

---

## 📁 Project Structure



### 1. Compile
```bash
g++ src/*.cpp -I include -o memsim


