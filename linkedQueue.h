#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

// Generic element
template <typename T>
struct TElementQ {
    T data;
    TElementQ<T> *next; // Points to next element
};

// Points to the first element of the Generic Linked Queue
template <typename T>
struct TListQ {
    TElementQ<T> *first;
};

// Boot Generic Linked Queue
template <typename T>
bool bootLinkedQueue(TListQ<T> &list) {
    list.first = nullptr;
    return true;
}

// Insert at the end of the queue
template <typename T>
bool queueL(TListQ<T> &list, T &data) {
    TElementQ<T> *e = new TElementQ<T>;
    e->data = data;
    e->next = nullptr;
  
    if (list.first == nullptr) { // If queue is empty
        list.first = e; // Insert as first (and last) position
        return true;
    }
      
    TElementQ<T> *nav = list.first; // Create auxiliary pointer to navigate the queue
    while (nav->next != nullptr)
        nav = nav->next; // Navigate to the last element in the queue
    nav->next = e; // Insert element at the end of the queue
    return true;
}

// Remove first element in the queue
template <typename T>
T dequeueL(TListQ<T> &list) {
  if (list.first == nullptr) // Check if queue is empty
      return false;
  
  T data = list.first->data; // Save data of the first element
  list.first = list.first->next; // list.first points to second element
  return data; // Return data from first element
}

template <typename T>
bool isEmptyL(const TListQ<T> &list) {
    return list.first == nullptr;
}

#endif // LINKED_QUEUE_H
