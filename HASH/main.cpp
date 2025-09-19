#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// Choose ONE library to test
// #include "int_chainingHash.h"
// #include "string_chainingHash.h"
// #include "int_openAddressingHash.h"
// #include "string_openAddressingHash.h"

int main() {
    cout << "Available options:" << endl;
    cout << "1. Integer Chaining Hash" << endl;
    cout << "2. String Chaining Hash" << endl;
    cout << "3. Integer Open Addressing Hash" << endl;
    cout << "4. String Open Addressing Hash" << endl << endl;

    // ========================================================================================================
    /* Integer Chaining Hash
    chainingNode* table[SIZE];
    chainingHash_boot(table);

    chainingHash_insert(table, 15);
    chainingHash_insert(table, 23);
    chainingHash_insert(table, 7);

    cout << "\n--- Integer Chaining Hash Table ---" << endl;
    chainingHash_display(table);

    cout << "Searching 23 -> " << (chainingHash_search(table, 23) ? "Found" : "Not Found") << endl;

    chainingHash_delete(table, 23);
    cout << "After deleting 23:" << endl;
    chainingHash_display(table);
    */

    // ========================================================================================================
    /* String Chaining Hash
    chainingNode* table[SIZE];
    chainingHash_boot(table);

    chainingHash_insert(table, "cat");
    chainingHash_insert(table, "dog");
    chainingHash_insert(table, "bird");

    cout << "\n--- String Chaining Hash Table ---" << endl;
    chainingHash_display(table);

    cout << "Searching 'cat' -> " << (chainingHash_search(table, "cat") ? "Found" : "Not Found") << endl;

    chainingHash_delete(table, "cat");
    cout << "After deleting 'cat':" << endl;
    chainingHash_display(table);
    */

    // ========================================================================================================
    /* Integer Open Addressing Hash
    intOpenAddressingHash table;
    table.boot(SIZE);

    table.insert(15);
    table.insert(23);
    table.insert(7);

    cout << "\n--- Integer Open Addressing Hash Table ---" << endl;
    table.display();

    try {
        int idx = table.search(23);
        cout << "Searching 23 -> Found at index " << idx << endl;
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }

    table.remove(23);
    cout << "After deleting 23:" << endl;
    table.display();
    */

    // ========================================================================================================
    /* String Open Addressing Hash
    stringOpenAddressingHash table;
    table.boot(SIZE);

    table.insert("cat");
    table.insert("dog");
    table.insert("bird");

    cout << "\n--- String Open Addressing Hash Table ---" << endl;
    table.display();

    try {
        int idx = table.search("cat");
        cout << "Searching 'cat' -> Found at index " << idx << endl;
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }

    table.remove("cat");
    cout << "After deleting 'cat':" << endl;
    table.display();
    */

    return 0;
}
