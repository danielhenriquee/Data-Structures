# SBB Tree

SBB Tree implementation created at Data Structures – 2024/1

This folder contains a generic (template-based) implementation of an SBB Tree (Strictly Binary Balanced Tree) — a self-balancing binary search tree that maintains balance through the use of horizontal and vertical links.
Its main goal is to serve as educational material for studying balanced tree structures, as well as a reusable base for academic projects that require efficient insertion and search operations.

**Contents**
- sbbTree.h – SBB Tree definition and implementation
- main.cpp – testing program with interactive menu

**Features**
- Generic (template) support for storing data of any type
- Balancing maintained through link orientations (VERTICAL / HORIZONTAL)
- Support for key–value association (key used for ordering, data for storage)
- Rotation cases: LL, RR, LR, RL
- Search operations (SBB_searchData, SBB_contains)
- Traversal and printing methods (SBB_printTree, SBB_showTree)
- Utility functions: SBB_size, SBB_destroyTree
- Simplified removal operation (SBB_remove) – implemented without full rebalancing, for educational purposes

**Usage**
- Include the header file in your C++ project and create an SBB_TBinaryTree<T> object with your desired type T.
- You can then use the provided functions to insert, search, and display tree contents while ensuring automatic balancing.

**Notes**
- Keys (int key) define the ordering; duplicate keys are not inserted
- Removal is implemented in a simplified way (without full rebalancing), which is sufficient for academic contexts
- The implementation prioritizes clarity over extreme optimization, making it suitable for learning and academic use
- Printing methods are intended for debugging and visualization rather than structured output formatting
