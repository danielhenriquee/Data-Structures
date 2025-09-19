// Daniel Henrique da Silva
// Integer Hash Table with Open Addressing (Linear Probing)

#ifndef INT_OPENADDRESSINGHASH_H
#define INT_OPENADDRESSINGHASH_H

#include <iostream>
#include <stdexcept>
using namespace std;

const int SIZE = 8; // HASH TABLE SIZE

// Node for the open addresing list
struct OA_Node {
    int key; // Stored integer
    char status; // E = empty, 'F' = filled, 'R' = removed
};

// Hash function using mod
int OA_hash(int num) {
    return num % SIZE;
}

// Initialize hash table
void OA_boot(OA_Node table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i].status = 'E';
    }
}

// Insert a new key into the hash table
void OA_insert(OA_Node table[], int num) {
    int pos = OA_hash(num); // Compute hash position
    int i = 0;

    while (i < SIZE && table[pos].status == 'F') { // Traverse while slot occupied
        pos = (pos + 1) % SIZE; // Linear probing
        i++;
    }

    if (i < SIZE) { // Found free or removed slot
        table[pos].key = num;
        table[pos].status = 'F';
    } else {
        throw runtime_error("Hash table full");
    }
}

// Search for a key, returns index or SIZE if not found
int OA_search(OA_Node table[], int num) {
    int pos = OA_hash(num);
    int i = 0;

    while (i < SIZE && table[pos].status != 'E' && table[pos].key != num) {
        pos = (pos + 1) % SIZE; // Linear probing
        i++;
    }

    if (i < SIZE && table[pos].status == 'F' && table[pos].key == num)
        return pos;

     throw runtime_error("Key not found"); // Not found
}

// Delete a key by marking as removed
void OA_delete(OA_Node table[], int num) {
    int pos = OA_search(table, num); // If not found, will throw
    table[pos].status = 'R'; // Mark removed
}

// Display the table
void OA_show(OA_Node table[]) {
    for (int i = 0; i < SIZE; i++) {
        cout << "Index " << i << ": ";
        if (table[i].status == 'F')
            cout << table[i].key << " (Filled)";
        else if (table[i].status == 'R')
            cout << "Removed";
        else
            cout << "Empty";
        cout << "\n";
    }
}

// Clear the table
void OA_clear(OA_Node table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i].status = 'E';
    }
}

#endif
