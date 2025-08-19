# STACKS

Generic stack implementations developed for educational purposes — 2024/1

This folder contains template-based Abstract Data Types (ADTs) for different kinds of stacks, implemented in C++ for academic and practical use.

**Contents**
- Static Stack (staticStack.h)
  - Fixed-size array implementation
  - Pros: simple, fast access to top element
  - Cons: limited capacity

- Linked Stack (linkedStack.h)
  - Dynamically allocated nodes connected with pointers
  - Pros: no fixed limit, flexible growth
  - Cons: sequential memory allocation overhead
- Doubly Linked Stack (doublyLinkedStack.h)
  - Nodes connected in both directions (previous and next)
  - Pros: efficient bidirectional traversal if extended, easy access to both top and bottom
  - Cons: higher memory usage due to extra pointers

**Features**
- Generic implementation with C++ templates
- Operations: push, pop, state checks (empty/full), destruction
- Exception handling for error cases (underflow, overflow)
- Modular and reusable code

**Notes**
- Static stack has a fixed capacity defined at compile time.
- Linked versions grow dynamically with heap allocation.
- Doubly linked stack can be extended to allow access/removal from both ends.
- Designed for academic study and as a base library for projects.
