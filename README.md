# Data Structures
Data Structures developed for educational purposes - 2024/1

This repository contains generic (template-based) implementations of fundamental data structures in C++.
Each type of data structure is organized into its own folder.
The main goal is to serve as educational material and a base library for academic projects, facilitating practical study and application of ADT concepts.

**Contents**
- Lists
  - staticList.h
  - linkedList.h
  - doublyLinkedList.h
- Queues
  - staticQueue.h
  - linkedQueue.h
  - doublyLinkedQueue.h
- Stacks
  - staticStack.h
  - linkedStack.h
  - doublyLinkedStack.h
- Trees
  - avlTree.h
  
**Features**
- Generic implementations with templates (support for different data types)
- Exception handling for error control (underflow, overflow, invalid access)
- Static (fixed-size) and dynamic (pointer-based) versions
- Standard operations: insertion, removal, state checks (empty, full), destruction
- Sorting algorithms (bubble sort and quicksort) implemented for static and dynamic lists
- Clean, modular, and well-organized code for easy understanding and reuse

**Usage**

These header files can be directly included in C++ projects requiring generic data structures, with support for custom data types. The functions are implemented to offer robustness and efficiency in academic scenarios.

**Notes**
- Static structures use fixed-size arrays; for high-demand use cases, consider dynamic versions
- Static queues and stacks could be optimized further using circular buffers or index tracking for performance gains
- Dynamic implementations are designed primarily for learning purposes and can be adapted for more complex cases
