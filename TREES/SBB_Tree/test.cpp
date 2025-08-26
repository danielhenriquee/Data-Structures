#include <iostream>
#include "sbbTree.h"

using namespace std;

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif


int main() {
    bool menu = true;
    int resp, conteudo, codigo_chave;
    SBB_TBinaryTree<int> tree;

    SBB_boot(tree);

    while (menu) {
        system(CLEAR);

        cout << "\n============ SBB Tree ==========" << endl;
        cout << "=== 1 -     Insert Node      ===" << endl;
        cout << "=== 2 -     Remove Node      ===" << endl;
        cout << "=== 3 -     Search Node      ===" << endl;
        cout << "=== 4 - Print Tree In-Order  ===" << endl;
        cout << "=== 5 - Print Tree Structure ===" << endl;
        cout << "=== 6 -      Tree Size       ===" << endl;
        cout << "=== 7 - Check if Key Exists  ===" << endl;
        cout << "=== 8 -      Reset Tree      ===" << endl;
        cout << "=== 9 -         Quit         ===" << endl;
        cout << "================================" << endl;

        int key, value, choice;
        cin >> choice;
        try {
            switch(choice) {
                case 1: // Insert
                    cout << "Enter a key: ";
                    cin >> key;
                    cout << "Enter a value: ";
                    cin >> value;
                    SBB_insert(tree.root, key, value);
                    break;
                case 2: // Remove
                    cout << "Enter a key to remove: ";
                    cin >> key;
                    SBB_remove(tree.root, key);
                    break;
                case 3: // Search
                    cout << "Enter a key to search: ";
                    cin >> key;
                    value = SBB_searchData(tree.root, key);
                    cout << "Value found: " << value << endl;
                    cout << "Type any character to return to the menu...";
                    cin.ignore();
                    cin.get();
                    break;
                case 4: // Print in-order
                    cout << "Tree in-order: ";
                    SBB_printTree(tree.root);
                    cout << endl;
                    cout << "Type any character to return to the menu...";
                    cin.ignore();
                    cin.get();
                    break;
                case 5: // Show tree sideways
                    cout << "SBB Tree structure:\n";
                    SBB_showTree(tree.root, 0);
                    cout << "Type any character to return to the menu...";
                    cin.ignore();
                    cin.get();
                    break;
                case 6: // Tree size
                    cout << "Tree size: " << SBB_size(tree.root) << endl;
                    cout << "Type any character to return to the menu...";
                    cin.ignore();
                    cin.get();
                    break;
                case 7: // Check key
                    cout << "Enter a key to check: ";
                    cin >> key;
                    if (SBB_contains(tree.root, key))
                        cout << "Key exists in the tree." << endl;
                    else
                        cout << "Key does not exist." << endl;
                    cout << "Type any character to return to the menu...";
                    cin.ignore();
                    cin.get();
                    break;
                case 8: // Reset tree
                    SBB_destroyTree(tree.root);
                    SBB_boot(tree);
                    break;
                case 9: // Quit
                    menu = false;
                    break;
                default:
                    cout << "Invalid choice!\n";
                    cout << "Type any character to return to the menu...";
                    cin.ignore();
                    cin.get();
                    break;
            }
        }   catch (const exception& e) {
            cout << "\nError: " << e.what() << endl;
            cout << "Press any key to return to the menu...";
            cin.ignore();
            cin.get();
        }
    }

    SBB_destroyTree(tree.root);
    return 0;
}
