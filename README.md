# Data Structures
Data Structures developed for educational purposes - 2024/1

This repository contains generic (template-based) implementations of fundamental data structures.
The main goal is to serve as educational material and a base library for academic projects, facilitating practical study and application of ADT concepts.

**Contents**
- staticList.h
- linkedList.h
- doublyLinkedList.h
- staticQueue.h
- linkedQueue.h
- doublyLinkedQueue.h
- staticStack.h
- linkedStack.h
- doublyLinkedStack.h
- avlTree.h
  
**Features**
- Generic implementations for different data types
- Exception handling for error control (e.g., underflow, overflow)
- Static structures with fixed size and dynamic ones with dynamic memory allocation
- Standard methods: insertion, removal, state checks (empty, full), destruction
- Sorting algorithms (bubble sort and quicksort) implemented for static and dynamic lists
- Clean, modular, and well-organized code for easy understanding and reuse

**Usage**

These header files can be directly included in C++ projects requiring generic data structures, with support for custom data types. The functions are implemented to offer robustness and efficiency in academic scenarios.

**Notes**
- Static structures use fixed-size arrays; for high-demand use cases, consider dynamic versions
- Static queues and stacks could be optimized further using circular buffers or index tracking for performance gains
- Dynamic implementations are designed primarily for learning purposes and can be adapted for more complex cases
