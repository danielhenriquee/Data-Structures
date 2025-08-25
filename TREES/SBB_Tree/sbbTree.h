// Daniel Henrique da Silva

#ifndef SBBTREE_H
#define SBBTREE_H

#include <iostream>

// Generic element
const char VERTICAL = 'v';
const char HORIZONTAL = 'h';

template<typename T>
struct SBB_TBinaryNode {
    int key;
    T data;
    SBB_TBinaryNode<T> *left;
    char L;
    SBB_TBinaryNode<T> *right;
    char R;
};

// Points to the root of the Generic SBB Tree
template <typename T>
struct SBB_TBinaryTree {
    SBB_TBinaryNode<T> *root;
};

// Boot Generic Tree
template <typename T>
void SBB_boot(SBB_TBinaryTree<T> &tree) {
    tree.root = nullptr;
}

// Balance case: Left-Left
template <typename T>
void LL(SBB_TBinaryNode<T> *&ap) {
    SBB_TBinaryNode<T> *ap1 = ap->left;
    ap->left = ap1->right;
    ap1->right = ap;
    ap1->L = VERTICAL;
    ap->L = VERTICAL;
    ap = ap1;
}

// Balance case: Right-Right
template <typename T>
void RR(SBB_TBinaryNode<T> *&ap) {
    SBB_TBinaryNode<T> *ap1 = ap->right;
    ap->right = ap1->left;
    ap1->left = ap;
    ap1->R = VERTICAL;
    ap->R = VERTICAL;
    ap = ap1;
}

// Balance case: Left-Right
template <typename T>
void LR (SBB_TBinaryNode<T> *&ap) {
    SBB_TBinaryNode<T> *ap1 = ap->left;
    SBB_TBinaryNode<T> *ap2 = ap1->right;
    ap1->R = VERTICAL;
    ap->L = VERTICAL;
    ap1->right = ap2->left;
    ap2->left = ap1;
    ap->left = ap2->right;
    ap2->right = ap;
    ap = ap2;
}

// Balance case: Right-Left
template <typename T>
void RL (SBB_TBinaryNode<T> *&ap) {
    SBB_TBinaryNode<T> *ap1 = ap->right;
    SBB_TBinaryNode<T> *ap2 = ap1->left;
    ap1->L = VERTICAL;
    ap->R = VERTICAL;
    ap1->left = ap2->right;
    ap2->right = ap1;
    ap->right = ap2->left;
    ap2->left = ap;
    ap = ap2;
}

// Insert into SBB tree
template<typename T>
int SBB_insert (SBB_TBinaryNode<T> *&node, int key, T data) {
    if (node == nullptr) {
        node = new SBB_TBinaryNode<T>;
        node->key = key;
        node->data = data;
        node->left = nullptr;
        node->right = nullptr;
        node->L = VERTICAL;
        node->R = VERTICAL;
        return 1;
    } else {
        if (key > node->key) {
            int n = SBB_insert(node->right, key, data);
            if (n == 1) {
                node->R = HORIZONTAL;
                n++;
            } else {
                if (n == 2 && node->R == HORIZONTAL) {
                    n = 1;
                    if (node->right->R == HORIZONTAL)
                        RR(node);
                    else
                        RL(node);
                } else {
                    n = 0;
                }
            }
            return n;
        } else if (key < node->key) {
            int n = SBB_insert(node->left, key, data);
            if (n == 1) {
                node->L = HORIZONTAL;
                n++;
            } else {
                if (n == 2 && node->L == HORIZONTAL) {
                    n = 1;
                    if (node->left->L == HORIZONTAL)
                        LL(node);
                    else
                        LR(node);
                } else {
                    n = 0;
                }
            }
            return n;
        } else {
            // Duplicate keys ignored
            return 0;
        }
    }
}

// Search by key
template<typename T>
T* SBB_searchData(SBB_TBinaryNode<T>* node, int key) {
    if (!node) return nullptr;
    if (key == node->key) return &node->data;
    if (key < node->key) return SBB_searchData(node->left, key);
    else return SBB_searchData(node->right, key);
}

// Size of tree
template<typename T>
int SBB_size(SBB_TBinaryNode<T>* node) {
    if (!node) return 0;
    return 1 + SBB_size(node->left) + SBB_size(node->right);
}

// Destroy tree
template<typename T>
void SBB_destroy(SBB_TBinaryNode<T>*& node) {
    if (!node) return;
    SBB_destroy(node->left);
    SBB_destroy(node->right);
    delete node;
    node = nullptr;
}

// Helper: find min node
template<typename T>
SBB_TBinaryNode<T>* SBB_findMin(SBB_TBinaryNode<T>* node) {
    while (node && node->left) node = node->left;
    return node;
}

// Remove by key (simplified, without full rebalance)
template<typename T>
SBB_TBinaryNode<T>* SBB_remove(SBB_TBinaryNode<T>* node, int key) {
    if (!node) return nullptr;

    if (key < node->key) {
        node->left = SBB_remove(node->left, key);
    } else if (key > node->key) {
        node->right = SBB_remove(node->right, key);
    } else {
        // Node found
        if (!node->left) {
            SBB_TBinaryNode<T>* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            SBB_TBinaryNode<T>* temp = node->left;
            delete node;
            return temp;
        }
        // Two children: replace by inorder successor
        SBB_TBinaryNode<T>* temp = SBB_findMin(node->right);
        node->key = temp->key;
        node->data = temp->data;
        node->right = SBB_remove(node->right, temp->key);
    }
    return node;
}

#endif // SBBTREE_H