#ifndef STATIC_STACK_H
#define STATIC_STACK_H

#include <stdexcept>

// Generic element
template <typename T>
struct StaticS_TElement {
    T data;
};

// Generic Static Stack
template <typename T, int MAX>
struct StaticS_TList {
    StaticS_TElement<T> elements[MAX];
    int size; // Counter of elements' number
};

// Boot Generic Static Stack
template <typename T, int MAX>
void StaticS_boot(StaticS_TList<T, MAX> &list) {
    list.size = 0;
}

// Insert at the top of the stack
template <typename T, int MAX>
bool StaticS_push(StaticS_TList<T, MAX> &list, const T &data) {
    if (list.size >= MAX) // Check if stack is full
        throw std::overflow_error("Error: stack if full.");

    list.elements[list.size].data = data; // Insert at the top
    list.size++; // Increase stack size
    return true;
}

// Remove top element in the stack
template <typename T, int MAX>
T StaticS_pop(StaticS_TList<T, MAX> &list) {
    if (list.size <= 0) // Check if list is empty
        throw std::underflow_error("Error: empty stack.");
  
    list.size--; // Decrease size
    return list.elements[list.size].data; // Return top element
}

// Check if the stack is empty
template <typename T, int MAX>
bool StaticS_isEmpty(const StaticS_TList<T, MAX> &list) {
    return list.size == 0;
}

// Check if the stack is full
template <typename T, int MAX>
bool StaticS_isFull(const StaticS_TList<T, MAX> &list) {
    return list.size == MAX;
}

// Clear the stack
template <typename T, int MAX>
void StaticS_destroyStack(StaticS_TList<T, MAX> &list) {
    list.size = 0;
}

#endif // STATIC_STACK_H
