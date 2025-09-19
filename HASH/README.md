# Hash Tables

Hash Table implementations created at Data Structures – 2024/2

This folder contains multiple implementations of integer and string hash tables.
Exploring two classic collision-handling strategies: Chaining (linked lists) and Open Addressing (linear probing).
The main goal is to serve as educational material for understanding hashing techniques, as well as a reusable base for academic projects requiring fast insertion, deletion, and search operations.

**Contents**

'int_chainingHash.h' – Integer Hash Table with Chaining

'string_chainingHash.h' – String Hash Table with Chaining

'int_openAddressingHash.h' – Integer Hash Table with Open Addressing (Linear Probing)

'string_openAddressingHash.h' – String Hash Table with Open Addressing (Linear Probing)

'main.cpp' – Example program to test all implementations

**Features**
- Two collision handling strategies:
- Chaining: Each table index holds a linked list of colliding elements
- Open Addressing: Linear probing used to resolve collisions in the same array
- Integer and String versions available

**Hash functions**
- Integer: key % SIZE
- String: sum of character codes mod SIZE

**Basic operations**
- insert – add new element
- search – find element (throws exception if not found)
- delete – remove element (chaining removes from list, open addressing marks as removed)
- show – display the table contents
- clear – reset or free all entries

**Usage**
- Include the desired header file in your C++ project and create a table of type chainingNode* table[] (for chaining) or OA_Node table[] (for open addressing).
- You can then call the provided functions to manage elements in the hash table.
- The main.cpp file provides a menu system where you can choose which implementation to test (integer/string, chaining/open addressing).
- Each test demonstrates insertion, search, deletion, and display of table contents.

**Notes**
- Open addressing uses status flags: 'E' = empty, 'F' = filled, 'R' = removed
- All search functions throw exceptions if the element is not found (instead of returning sentinel values)
- Chaining dynamically allocates memory for linked list nodes; remember to call clear to free memory
- Implementations prioritize clarity and didactic value over optimization, making them suitable for learning purposes
- String hash functions are simple (sum of characters) for readability; in practice, stronger hash functions are recommended
