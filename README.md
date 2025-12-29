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


## 📊 System Architecture Diagram

The following diagram represents the high-level architecture of the **OS Memory Management Simulator** and shows how different components interact with each other.

```mermaid
flowchart TD
    A[User / CLI Input] --> B[Main Controller]

    B --> C[Memory Management Module]
    B --> D[Cache Simulation Module]

    C --> C1[Physical Memory]
    C --> C2[Memory Blocks]
    C --> C3[Allocation Logic]
    C --> C4[Deallocation Logic]

    D --> D1[Cache Access Handler]
    D --> D2[Cache Hit Counter]
    D --> D3[Cache Miss Counter]

    C --> E[Statistics Module]
    D --> E

    E --> F[Output / Reports]


## 📂 Project Structure




