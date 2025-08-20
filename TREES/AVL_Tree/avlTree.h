// Daniel Henrique da Silva

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <stdexcept>

using namespace std;

// Generic element
template <typename T>
struct AVL_TBinaryNode {
    T data;
    int key;
    int height;
    AVL_TBinaryNode<T> *right; // Points to right child
    AVL_TBinaryNode<T> *left; // Points to left child
};

// Points to the root of the Generic Binary Tree
template <typename T>
struct AVL_TBinaryTree {
    AVL_TBinaryNode<T> *root;
};

// Boot Generic AVL Tree
template <typename T>
void AVL_boot(AVL_TBinaryTree<T> &tree) {
    tree.root = nullptr;
};

// Returns AVL tree height
template <typename T>
int AVL_height(AVL_TBinaryNode<T> *node) {
    if (node == nullptr) {
        return 0;
    } else {
        return node->height;
    }

}

// Returns balance factor
template <typename T>
int AVL_getBalance(AVL_TBinaryNode<T> *node) {
    if (!node) 
        return 0;
    return AVL_height(node->left) - AVL_height(node->right);
}

// Update node height
template <typename T>
void AVL_updateHeight(AVL_TBinaryNode<T> *node) {
    if (node)
        node->height = 1 + max(AVL_height(node->left), AVL_height(node->right));
}

// Create new node with default attributes
template <typename T>
AVL_TBinaryNode<T>* AVL_newNode(int key, T data) {
    AVL_TBinaryNode<T>* node = new AVL_TBinaryNode<T>;
    node->key = key;
    node->data = data;
    node->height = 1;
    node->left = node->right = nullptr;
    return node;
}

// Balance case: Left-Left
template <typename T>
void LL (AVL_TBinaryNode<T> *&r) {
    AVL_TBinaryNode<T>* A = r->left; // A becomes left side of sub-tree's root
    r->left = A->right; // Root->left points to A->right
    A->right = r; // A->right points to root
    r = A;

    AVL_updateHeight(r->right);
    AVL_updateHeight(r);
}

// Balance case: Right-Right
template <typename T>
void RR (AVL_TBinaryNode<T> *&r) {
    AVL_TBinaryNode<T>* A = r->right; // A becomes right side of sub-tree's root
    r->right = A->left; // Root->right points to A->left
    A->left = r; // A->left points to root
    r = A;

    AVL_updateHeight(r->left);
    AVL_updateHeight(r);
}

// Balance case: Left-Right
template <typename T>
void LR (AVL_TBinaryNode<T> *&r) {
    RR(r->left);
    LL(r);
}

// Balance case: Right-Left
template <typename T>
void RL (AVL_TBinaryNode<T> *&r) {
    LL(r->right);
    RR(r);
}

// Rebalance node after insert ou remove
template <typename T>
void AVL_balance(AVL_TBinaryNode<T> *&node) {
    if (!node) // If nullptr
        return; 

    AVL_updateHeight(node); // Firstly update height
     int balance = AVL_getBalance(node);

    if (balance > 1) { // If tree is left heavy (balance > 1)
        if (AVL_getBalance(node->left) >= 0) // LL case
            LL(node);
        else // LR case
            LR(node);
    } 
    else if (balance < -1) { // If tree is right heavy (balance < -1)
        if (AVL_getBalance(node->right) <= 0) // RR case
            RR(node);
        else // RL case
            RL(node);
    } else {
        AVL_updateHeight(node);
    }
}

// AVL_insert (with balancing)
template <typename T>
bool AVL_insert(AVL_TBinaryNode<T> *&node, int key, T data) {
    if (node == nullptr) {
        node = AVL_newNode(key, data);
        return true;
    }  
    
    // Navigate to correct position
    if (key < node->key) {
        if (!AVL_insert(node->left, key, data)) 
            return false;
    } else if (key > node->key) {
        if (!AVL_insert(node->right, key, data)) 
            return false;
    } else {
        return false; // Duplicate key is not inserted
    }

    // After insertion, rebalance current node
    AVL_balance(node);
    return true;
}

// Search to return data
template <typename T>
T AVL_searchData(AVL_TBinaryNode<T> *node, int key) {
    if (!node)
        throw std::out_of_range("Error: key not found.");
    if (key == node->key)
        return node->data;
    if (key < node->key)
        return AVL_searchData(node->left, key);
    else
        return AVL_searchData(node->right, key);
}

// AVL_remove node
template <typename T>
void AVL_remove(AVL_TBinaryNode<T>* &node, int key) {
    if (!node) // Empty subtree
        return; 

    if (key < node->key) { // Remove from left subtree
        AVL_remove(node->left, key);
    } else if (key > node->key) { // Remove from right subtree
        AVL_remove(node->right, key);
    } else { // Node found
        if (!node->left) { // No left child, replace with right child
            AVL_TBinaryNode<T>* temp = node;
            node = node->right;
            delete temp;
        } else if (!node->right) { // No right child, replace with left child
            AVL_TBinaryNode<T>* temp = node;
            node = node->left;
            delete temp;
        } else { // Node has two children: find the largest in left subtree
            AVL_TBinaryNode<T>* pred = AVL_max(node->left);
            node->key = pred->key;
            node->data = pred->data;
            AVL_remove(node->left, pred->key);
        }
    }

    if (node) // Rebalance subtree
        AVL_balance(node);
}

// Print tree (ascending by key)
template <typename T>
void AVL_printTree(AVL_TBinaryNode<T> *node) {
    if (node != nullptr) {
        AVL_printTree (node->left); // Navigate to the lowest element (most left)
        cout << node->key<<" "; // Print element
        AVL_printTree (node->right);
    }
}

// Print node with indentation
template <typename T>
void AVL_printNode(T k, int b) {
    for (int i = 0; i < b; i++)
        cout << "   ";
    cout << k << endl;
}

// Print tree (sideways visualization)
template <typename T>
void AVL_showTree(AVL_TBinaryNode<T> *node, int b) {
    if (node == nullptr) {
        AVL_printNode(0, b);
        return;
    }
    AVL_showTree(node->right, b+2);
    AVL_printNode(node->key, b);
    AVL_showTree(node->left, b+2);
}

// Delete tree
template <typename T>
void AVL_destroyTree(AVL_TBinaryNode<T> *&node) {
    if (!node)
        return;
    AVL_destroyTree(node->left);
    AVL_destroyTree(node->right);
    delete node;
    node = nullptr;
}

// Min node
template <typename T>
AVL_TBinaryNode<T>* AVL_min(AVL_TBinaryNode<T> *node) {
    if (!node) 
        return nullptr;
    while (node->left)
        node = node->left;
    return node;
}

// Max node
template <typename T>
AVL_TBinaryNode<T>* AVL_max(AVL_TBinaryNode<T> *node) {
    while (node && node->right)
        node = node->right;
    return node;
}

// Check if tree contains key
template <typename T>
bool AVL_contains(AVL_TBinaryNode<T> *node, int key) {
    if (!node) 
        return false;
    if (key == node->key) 
        return true;
    if (key < node->key) 
        return AVL_contains(node->left, key);
    return AVL_contains(node->right, key);
}

// Return tree size
template <typename T>
int AVL_size(AVL_TBinaryNode<T> *node) {
    if (!node) 
        return 0;
    return 1 + AVL_size(node->left) + AVL_size(node->right);
}

#endif // AVL_TREE_H