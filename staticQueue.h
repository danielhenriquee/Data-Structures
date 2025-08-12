#ifndef STATIC_QUEUE_H
#define STATIC_QUEUE_H

#include <stdexcept>

// Generic element
template <typename T>
struct StaticQ_TElement {
    T data;
};

// Generic Static Queue
template <typename T, int MAX>
struct StaticQ_TList {
    StaticQ_TElement<T> elements[MAX];
    int size; // Counter of elements' number
};

// Boot Generic Static Queue
template <typename T, int MAX>
void StaticQ_boot(StaticQ_TList<T, MAX> &list) {
    list.size = 0;
}

// Insert at the end of the queue
template <typename T, int MAX>
bool StaticQ_enqueue(StaticQ_TList<T, MAX> &list, const T &data) {
    if (list.size >= MAX) // Check if list is full
        throw std::underflow_error("Error: queue is full.");
    
    StaticQ_TElement<T> e;
    e.data = data;
    list.elements[list.size] = e; // Insert element at last position
    list.size++; // Increase queue size
    return true;
}

// Remove first element in the queue
template <typename T, int MAX>
T StaticQ_dequeue(StaticQ_TList<T, MAX> &list) {
    if (list.size == 0) // Check if queue is empty
        throw std::underflow_error("Error: empty queue.");
  
    T data = list.elements[0].data; // Save data of the first element
    for (int i = 0; i < list.size - 1; i++)
        list.elements[i] = list.elements[i + 1];
    list.size--;
    return data; // Return data from first element
}

template <typename T, int MAX>
bool StaticQ_isEmpty(const StaticQ_TList<T, MAX> &list) {
    return list.size == 0;
}

template <typename T, int MAX>
bool StaticQ_isFull(const StaticQ_TList<T, MAX> &list) {
    return list.size == MAX;
}

template <typename T, int MAX>
void StaticQ_destroyQueue(StaticQ_TList<T, MAX> &list) {
    list.size = 0;
}
#endif // STATIC_QUEUE_H
