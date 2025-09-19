// Daniel Henrique da Silva

#ifndef INT_CHAININGHHASH_H
#define INT_CHAININGHHASH_H

#include <iostream>
#include <stdexcept>
using namespace std;

const int SIZE = 8; // HASH TABLE SIZE

// Node for the chaining linked list
struct chainingNode {
    int key; // Stored integer
    chainingNode* next; // Pointer to the next node in the chain
};


// Hash function using mod
int chainingHash_hashing(int num) {
    return num % SIZE;
}

// Initialize hash table
void chainingHash_boot(chainingNode* table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i] = nullptr;
    }
}


// Insert a new key into the hash table
void chainingHash_insert(chainingNode* table[], int num) {
    chainingNode* e = new chainingNode();
    e->key = num;
    int pos = chainingHash_hashing(num); // Compute hash position
    e->next = table[pos];
    table[pos] = e; // Update table index
}

// Delete a key from the hash table
void chainingHash_delete(chainingNode* table[], int num) {
    int pos = chainingHash_hashing(num);
    chainingNode* aux;
    if (table[pos] != nullptr) { // Check if chain is not empty
        if (table[pos]->key == num) { // First node matches key
            aux = table[pos];
            table[pos] = table[pos]->next; // Remove from chain
            delete aux;
        } else {
            aux = table[pos]->next; // Start from second node
            chainingNode* ant = table[pos];
            while (aux != nullptr && aux->key != num) { // Traverse chain
                ant = aux;
                aux = aux->next;
            }
            if (aux != nullptr) { // Key found
                ant->next = aux->next;
                delete aux;
            } else { // Key not found
                throw runtime_error("Key not found");
            }
        }
    } else {
       throw runtime_error("Key not found"); // Chain empty
    }
}

// Display all chains in the hash table
void chainingHash_showChain(chainingNode* table[]) {
    for (int i = 0; i < SIZE; i++) {
        cout << "\nIndex " << i << ": ";
        chainingNode* aux = table[i];
        while (aux != nullptr) { // Traverse each node in chain
            cout << aux->key << " --> ";
            aux = aux->next;
        }
        cout << "nullptr"; // End of chain
    }
}

// Search for a key in the hash table
int chainingHash_search(chainingNode* table[], int num) {
    int pos = chainingHash_hashing(num); // Compute hash position
    chainingNode* aux = table[pos]; 
    while (aux != nullptr) { // Traverse chain
        if (aux->key == num) { // Key found
            return pos; // Return index
        }
        aux = aux->next;
    }
    throw runtime_error("Key not found"); // Key not found
}

// Clear the entire hash table, freeing all memory
void chainingHash_clear(chainingNode* table[]) {
    for (int i = 0; i < SIZE; i++) { // For each index
        chainingNode* aux = table[i];
        while (aux != nullptr) { // Delete all nodes in chain
            chainingNode* tmp = aux;
            aux = aux->next;
            delete tmp;
        }
        table[i] = nullptr; // Reset index to empty
    }
}

#endif
