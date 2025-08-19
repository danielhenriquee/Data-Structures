# LISTS

Generic list implementations developed for educational purposes — 2024/1

This folder contains template-based Abstract Data Types (ADTs) for different kinds of lists, implemented in C++ for academic and practical use.

**Contents**
- Static List (staticList.h)
  - Fixed-size array implementation
  - Pros: simple, fast indexing
  - Cons: limited capacity

- Linked List (linkedList.h)
  - Dynamically allocated nodes connected with pointers
  - Pros: no fixed limit, flexible insertions/removals
  - Cons: sequential access only

- Doubly Linked List (doublyLinkedList.h)
  - Nodes connected in both directions
  - Pros: efficient traversals and removals in both directions
  - Cons: higher memory overhead

**Features**
- Generic implementation with C++ templates
- Operations: insertion, removal, search, state checks (empty/full)
- Sorting methods: Bubble Sort and Quick Sort
- Modular and reusable code

**Notes***
- Static list has a fixed capacity; linked versions grow dynamically.
- Sorting is available for both static and dynamic lists.
- Designed for academic study and as a base library for projects.
