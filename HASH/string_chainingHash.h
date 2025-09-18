// Daniel Henrique da Silva

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

const int SIZE = 8; // HASH TABLE SIZE

// Node for the chaining linked list
struct chainingNodeStr {
    string key; // Value stored in the node
    chainingNodeStr* next;  // Pointer to the next node in the chain
};

// Hash function for strings using simple sum-of-chars modulo
int chainingHash_hashing(const string& str) {
    int sum = 0;
    for (char c : str) {
        sum += static_cast<int>(c); // Add ASCII value of each character
    }
    return sum % SIZE; // Compute hash position
}

// Initialize hash table
void chainingHash_boot(chainingNodeStr* table[]) {
    for (int i = 0; i < SIZE; i++) {
        table[i] = nullptr; // Set all indices to empty
    }
}

// Insert a new string into the hash table
void chainingHash_insert(chainingNodeStr* table[], const string& str) {
    chainingNodeStr* e = new chainingNodeStr();
    e->key = str;
    int pos = chainingHash_hashing(str); // Compute hash position
    e->next = table[pos];                
    table[pos] = e; // Update table index
}

// Delete a string from the hash table
void chainingHash_delete(chainingNodeStr* table[], const string& str) {
    int pos = chainingHash_hashing(str);
    chainingNodeStr* aux;
    
    if (table[pos] != nullptr) { // Check if chain is not empty
        if (table[pos]->key == str) { // First node matches key
            aux = table[pos];
            table[pos] = table[pos]->next; // Remove from chain
            delete aux;
        } else {
            aux = table[pos]->next; // Start from second node
            chainingNodeStr* ant = table[pos];
            while (aux != nullptr && aux->key != str) { // Traverse chain
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
void chainingHash_showChain(chainingNodeStr* table[]) {
    for (int i = 0; i < SIZE; i++) {
        cout << "\nIndex " << i << ": ";
        chainingNodeStr* aux = table[i];
        while (aux != nullptr) { // Traverse each node in chain
            cout << aux->key << " --> ";
            aux = aux->next;
        }
        cout << "nullptr"; // End of chain
    }
}

// Search for a string in the hash table
int chainingHash_search(chainingNodeStr* table[], const string& str) {
    int pos = chainingHash_hashing(str); // Compute hash position
    chainingNodeStr* aux = table[pos];
    while (aux != nullptr) { // Traverse chain
        if (aux->key == str) { // Key found
            return pos; // Return index
        }
        aux = aux->next;
    }
    throw runtime_error("Key not found"); // Key not found
}

// Clear the entire hash table, freeing all memory
void chainingHash_clear(chainingNodeStr* table[]) {
    for (int i = 0; i < SIZE; i++) { // For each index
        chainingNodeStr* aux = table[i];
        while (aux != nullptr) { // Delete all nodes in chain
            chainingNodeStr* tmp = aux;
            aux = aux->next;
            delete tmp;
        }
        table[i] = nullptr; // Reset index to empty
    }
}
