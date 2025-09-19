// Daniel Henrique da Silva

#ifndef STRING_OPENADDRESSINGHASH_H
#define STRING_OPENADDRESSINGHASH_H

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

const int SIZE = 8; // HASH TABLE SIZE

// Node for the open addressing table
struct OA_NodeStr {
    string key;  // Stored string
    char status; // 'E' = empty, 'F' = filled, 'R' = removed
};

// Hash function for strings (simple polynomial rolling hash)
int OA_hashStr(const string& str) {
    unsigned long hash = 0;
    for (char c : str) {
        hash = (hash * 31 + c) % SIZE; // 31 is a common base for string hashing
    }
    return static_cast<int>(hash);
}

// Initialize hash table
void OA_boot(OA_NodeStr table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i].status = 'E';
    }
}

// Insert a new key into the hash table
void OA_insert(OA_NodeStr table[], const string& str) {
    int pos = OA_hashStr(str); // Compute hash position
    int i = 0;

    while (i < SIZE && table[pos].status == 'F') { // Traverse while slot occupied
        if (table[pos].key == str) {
            throw runtime_error("Key already exists"); // Prevent duplicates
        }
        pos = (pos + 1) % SIZE; // Linear probing
        i++;
    }

    if (i < SIZE) { // Found free or removed slot
        table[pos].key = str;
        table[pos].status = 'F';
    } else {
        throw runtime_error("Hash table full");
    }
}

// Search for a key in the hash table
// Returns index if found, throws if not found
int OA_search(OA_NodeStr table[], const string& str) {
    int pos = OA_hashStr(str); // Compute hash position
    int i = 0;

    while (i < SIZE && table[pos].status != 'E' && table[pos].key != str) {
        pos = (pos + 1) % SIZE; // Linear probing
        i++;
    }

    if (i < SIZE && table[pos].status == 'F' && table[pos].key == str)
        return pos; // Found

    throw runtime_error("Key not found"); // Not found
}

// Delete a key by marking as removed
void OA_delete(OA_NodeStr table[], const string& str) {
    int pos = OA_search(table, str); // If not found, will throw
    table[pos].status = 'R';         // Mark removed
}

// Display the entire table
void OA_show(OA_NodeStr table[]) {
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

// Clear the entire hash table
void OA_clear(OA_NodeStr table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i].status = 'E';
        table[i].key.clear();
    }
}

#endif
