#ifndef DOUBLY_LINKED_QUEUE_H
#define DOUBLY_LINKED_QUEUE_H

#include <stdexcept>

// Generic element
template <typename T>
struct DoublyLinkedQ_TElement {
    T data;
    DoublyLinkedQ_TElement<T> *next; // Points to next element
    DoublyLinkedQ_TElement<T> *prev; // Points to previous element
};

// Points to the first and last element of the Generic Doubly Linked DoublyLinkedQ_queue
template <typename T>
struct DoublyLinkedQ_TList {
    DoublyLinkedQ_TElement<T> *first;
    DoublyLinkedQ_TElement<T> *last;
};

// Boot Generic Doubly Linked DoublyLinkedQ_queue
template <typename T>
bool DoublyLinkedQ_boot(DoublyLinkedQ_TList<T> &list) {
    list.first = nullptr;
    list.last = nullptr;
    return true;
}

// Insert at the end of the DoublyLinkedQ_queue
template <typename T>
bool DoublyLinkedQ_enqueue(DoublyLinkedQ_TList<T> &list, const T &data) {
    DoublyLinkedQ_TElement<T> *e = new DoublyLinkedQ_TElement<T>;
    e->data = data;
    e->next = nullptr;
    e->prev = nullptr;
  
    if (list.first == nullptr) { // Check if list is empty
        list.first = e;
        list.last = e;
    } else {
        list.last->next = e; // Last element of the DoublyLinkedQ_queue points to new element
        e->prev = list.last; // New element's prev points to last element of the DoublyLinkedQ_queue
        list.last = e; // New element became the last element of the DoublyLinkedQ_queue
    }
    return true;
}

// Remove first element in the DoublyLinkedQ_queue
template <typename T>
T DoublyLinkedQ_dequeue(DoublyLinkedQ_TList<T> &list) {
  if (list.first == nullptr) // Check if list is empty
     throw std::underflow_error("Error: empty queue.");
    
  DoublyLinkedQ_TElement<T> *temp = list.first;
  T data = list.first->data; // Save data of the first element
  list.first = list.first->next; // First element of the DoublyLinkedQ_queue now is the second element

  if (list.first != nullptr)
      list.first->prev = nullptr;
  else // If queue is becomes empty
      list.last = nullptr;

  delete temp;
  return data; // Return data from first element

}

// Check if DoublyLinkedQ_queue is empty
template <typename T>
bool DoublyLinkedQ_isEmpty(const DoublyLinkedQ_TList<T> &list) {
    return list.first == nullptr;
}

// Delete all elements of the queue
template <typename T>
void DoublyLinkedQ_destroyQueue(DoublyLinkedQ_TList<T> &list) {
    DoublyLinkedQ_TElement<T> *nav = list.first;
    while (nav != nullptr) {
        DoublyLinkedQ_TElement<T> *next = nav->next;
        delete nav;
        nav = next;
    }
    list.first = nullptr;
    list.last = nullptr;
}

#endif // DOUBLY_LINKED_QUEUE_H
