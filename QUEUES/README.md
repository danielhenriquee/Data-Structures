# QUEUES

Generic queue implementations developed for educational purposes — 2024/1

This folder contains template-based Abstract Data Types (ADTs) for different kinds of queues, implemented in C++ for academic and practical use.

**Contents**
- Static Queue (staticQueue.h)
  - Fixed-size array implementation
  - Pros: simple, fast indexing
  - Cons: limited capacity, costly removals (shift operation)
- Linked Queue (linkedQueue.h)
  - Dynamically allocated nodes connected with pointers
  - Pros: no fixed limit, flexible growth
  - Cons: sequential traversal required
- Doubly Linked Queue (doublyLinkedQueue.h)
  - Nodes connected in both directions (front and back)
  - Pros: efficient dequeues and better navigation
  - Cons: higher memory usage due to extra pointers

**Features**
- Generic implementation with C++ templates
- Operations: enqueue, dequeue, state checks (empty/full), destruction
- Exception handling for error cases (underflow, overflow)
- Modular and reusable code

**Notes**
- Static queue uses shifting for removals; performance can be optimized with a circular buffer.
- Linked queues grow dynamically with heap allocation.
- Doubly linked version allows efficient removal from both ends if extended.
- Designed for academic study and as a base library for projects.
