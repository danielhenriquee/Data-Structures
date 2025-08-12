#ifndef doublyLinkedQueue_H_INCLUDED
#define doublyLinkedQueue_H_INCLUDED

// Generic element
template <typename T>
struct TElementQ {
    T data;
    TElementQ<T> *next; // Points to next element
    TElementQ<T> *prev; // Points to previous element
};

// Points to the first and last element of the Generic Doubly Linked Queue
template <typename T>
struct TListQ {
    TElementQ<T> *first;
    TElementQ<T> *last;
};

// Boot Generic Doubly Linked Queue
template <typename T>
bool bootDoublyLinkedQueue(TListQ<T> &list) {
    list.first = nullptr;
    list.last = nullptr;
    return true;
}

// Insert at the end of the queue
template <typename T>
bool queue(TListQ<T> &list, T &data) {
    TElementQ<T> *e = new TElementQ<T>;
    e->data = data;
    e->next = nullptr;
    e->prev = nullptr;
  
    if (list.first == nullptr) { // Check if list is empty
        list.first = e;
        list.last = e;
    } else {
        list.last->next = e; // Last element of the queue points to new element
        e->prev = list.last; // New element's prev points to last element of the queue
        list.last = e; // New element became the last element of the queue
    }
    return true;
}

// Remove first element in the queue
template <typename T>
T dequeue(TListQ<T> &list) {
  if (list.first == nullptr) // Check if list is empty
    return false;
  
  T data = list.first->data; // Save data of the first element
  list.first = list.first->next; // First element of the queue now is the second element
  list.first->prev = nullptr;
  if (list.first->next == nullptr) // If left only one element in the queue
      list.last = list.first; // First element of the queue became also end of the queue
  return data; // Return data from first element
}

// Check if queue is empty
template <typename T>
bool isEmpty(const TListQ<T> &list) {
    return list.first == nullptr;
}
#endif // doublyLinkedQueue_H_INCLUDED
