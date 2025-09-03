#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include <stdexcept>

// Generic element
template <typename T>
struct LinkedQ_TElement {
    T data;
    LinkedQ_TElement<T> *next; // Points to next element
};

// Points to the first element of the Generic Linked Queue
template <typename T>
struct LinkedQ_TList {
    LinkedQ_TElement<T> *first;
    int size;
};

// Boot Generic Linked Queue
template <typename T>
bool LinkedQ_boot(LinkedQ_TList<T> &list) {
    list.first = nullptr;
    list.size = 0;
    return true;
}

// Insert at the end of the queue
template <typename T>
bool LinkedQ_enqueue(LinkedQ_TList<T> &list, const T &data) {
    LinkedQ_TElement<T> *e = new LinkedQ_TElement<T>;
    e->data = data;
    e->next = nullptr;
    list.size++;

    if (list.first == nullptr) { // If queue is empty
        list.first = e; // Insert as first (and last) position
        return true;
    }
      
    LinkedQ_TElement<T> *nav = list.first; // Create auxiliary pointer to navigate the queue
    while (nav->next != nullptr)
        nav = nav->next; // Navigate to the last element in the queue
    nav->next = e; // Insert element at the end of the queue
    return true;
}

// Remove first element in the queue
template <typename T>
T LinkedQ_dequeue(LinkedQ_TList<T> &list) {
    if (list.first == nullptr) // Check if queue is empty
        throw std::underflow_error("Error: empty queue.");

    LinkedQ_TElement<T> *temp = list.first;
    T data = list.first->data; // Save data of the first element
    list.first = list.first->next; // list.first points to second element
    delete temp;
    list.size--;
    return data; // Return data from first element
}

template <typename T>
bool LinkedQ_isEmpty(const LinkedQ_TList<T> &list) {
    return list.first == nullptr;
}

// Delete all elements of the queue
template <typename T>
void LinkedQ_destroyQueue(LinkedQ_TList<T> &list) {
    while (list.first != nullptr) {
        LinkedQ_TElement<T> *temp = list.first;
        list.first = list.first->next;
        delete temp;
    }
    list.size = 0;
    list.first = nullptr; // Safety reset
}

#endif // LINKED_QUEUE_H
