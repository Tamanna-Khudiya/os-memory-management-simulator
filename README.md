# 🧠 OS Memory Management Simulator

An **Operating System Memory Management Simulator** implemented in **C++**, designed to demonstrate how physical memory allocation, deallocation, and cache behavior work inside an operating system.  
This simulator is intended for **educational and academic purposes**.

---

## 📖 Project Overview

Memory management is a critical responsibility of an operating system.  
This project simulates core memory management concepts such as:

- Physical memory representation
- Dynamic memory allocation and deallocation
- Memory block visualization
- Cache memory behavior and statistics

The simulator provides a command-line interface to interact with memory and observe how memory blocks are allocated, freed, and accessed.

---

## ✨ Features Implemented

### 🔹 Physical Memory Simulation
- Initializes a fixed-size physical memory.
- Memory is divided into blocks.
- Each block stores:
  - Starting address
  - Size
  - Allocation status
  - Block ID

---

### 🔹 Dynamic Memory Allocation
- Simulates `malloc`-like behavior.
- Allocates memory blocks sequentially.
- Splits free blocks when partial allocation occurs.

---

### 🔹 Memory Deallocation
- Frees allocated memory using block ID.
- Marks blocks as free.
- Supports basic memory reuse.

---

### 🔹 Memory Dump & Visualization
- Displays the current memory layout.
- Shows:
  - Address ranges
  - Used and free blocks
  - Block IDs

---

### 🔹 Statistics & Monitoring
- Displays:
  - Total memory
  - Used memory
  - Free memory
  - Number of allocated blocks

---

### 🔹 Multilevel Cache Simulation
- Simulates cache access for memory operations.
- Tracks:
  - Cache hits
  - Cache misses
- Helps analyze cache efficiency.

---

## ❌ Optional Features (Not Implemented)

The following features are **optional and not implemented** in this project:

- Buddy Allocation System
- Virtual Memory Management
- Paging & Page Replacement Algorithms

> These features can be added as future enhancements if required.

---

## 📊 Data Flow

The following describes how commands and data move through the **OS Memory Management Simulator** during execution.

1. **User Command Input**
   - User enters a memory management command (e.g., `malloc`, `free`, `dump`, `stats`) through the CLI.
   - Input is read by `main.cpp`.

2. **Main Controller**
   - Parses the command and identifies which module should handle it.
   - Dispatches the request to either the **Memory Management Module** or the **Cache Simulation Module** as necessary.

3. **Memory Management Module**
   - On `malloc` or `free`:
     - Processes the request.
     - Updates the **Physical Memory Layer**.
     - Adjusts memory blocks accordingly.
   - On `dump` or `stats`:
     - Retrieves the current memory layout and usage statistics.

4. **Cache Simulation Module**
   - On memory access operations:
     - Simulates cache behavior.
     - Tracks **cache hits** and **cache misses**.
     - Updates cache statistics.

5. **Physical Memory Layer**
   - Stores memory block information:
     - Block start address
     - Size
     - Allocation status
     - Block ID
   - Allocates and frees blocks based on module instructions.

6. **Statistics Module**
   - Combines data from memory and cache operations.
   - Prepares a summary for display.

7. **Display Output**
   - Final results (memory layout + statistics) are output to the user.





## 📂 Project Structure




