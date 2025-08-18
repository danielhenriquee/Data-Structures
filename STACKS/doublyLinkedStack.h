#ifndef DOUBLY_LINKED_STACK_H
#define DOUBLY_LINKED_STACK_H

#include <stdexcept>

// Generic element
template <typename T>
struct DoublyLinkedS_TElement {
    T data;
    DoublyLinkedS_TElement<T> *next; // Points to next element
    DoublyLinkedS_TElement<T> *prev; // Points to previous element
};

// Points to the first element of the Generic Doubly Linked Stack
template <typename T>
struct DoublyLinkedS_TListS {
    DoublyLinkedS_TElement<T> *top;
    DoublyLinkedS_TElement<T> *bottom;
};

// Boot Generic Doubly Linked Stack
template <typename T>
bool DoublyLinkedS_boot(DoublyLinkedS_TListS<T> &list) {
    list.top = nullptr;
    list.bottom = nullptr;
    return true;
}

// Insert at the top of the stack
template <typename T>
bool DoublyLinkedS_push(DoublyLinkedS_TListS<T> &list, const T &data) {
    DoublyLinkedS_TElement<T> *e = new DoublyLinkedS_TElement<T>;
    e->data = data;
    e->next = list.top;
    e->prev = nullptr;

    if (list.top == nullptr) // If stack is empty
        list.bottom = e;
    else
        list.top->prev = e;

    list.top = e;
    return true;
}

// Remove top element of the stack
template <typename T>
T DoublyLinkedS_pop(DoublyLinkedS_TListS<T> &list) {
    if (list.top == nullptr) // Check if stack is empty
        throw std::underflow_error("Error: empty stack.");

    DoublyLinkedS_TElement<T> *temp = list.top;
    T data = list.top->data;
    
    list.top = list.top->next; // Top of the stack now is the second element
    if (list.top == nullptr) // If stack becomes empty
        list.bottom = nullptr;
    else      
        list.top->prev = nullptr;

    delete temp;
    return data;
}

// Check if stack is empty
template <typename T>
bool DoublyLinkedS_isEmpty(const DoublyLinkedS_TListS<T> &list) {
    return list.top == nullptr;
}

// Delete all elements of the stack
template <typename T>
void DoublyLinkedS_destroyStack(DoublyLinkedS_TListS<T> &list) {
    while (list.top != nullptr) {
        DoublyLinkedS_TElement<T> *temp = list.top;
        list.top = list.top->next;
        delete temp;
    }
    list.bottom = nullptr;
}

#endif // DOUBLY_LINKED_STACK_H
