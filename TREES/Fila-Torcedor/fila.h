#include <iostream>
using namespace std;
#include <cstddef>

template <typename T>
struct TElementQ {
  T data;
  TElementQ<T> *next;
};

template <typename T>
struct TListQ {
  TElementQ<T> *first;
  float size;
};

// Boot list
template <typename T> 
bool bootLinkedQueue(TListQ<T> &list) {
  list.first = NULL;
  list.size = 0;
  return true;
}

// Insert at the end of the queue
template <typename T> 
bool queue(TListQ<T> &list, T &data) {
  TElementQ<T> *newElement = new TElementQ<T>; // Create new element
  newElement->data = data;
  newElement->next = NULL;

  if (list.first == NULL) // Check if queue is empty
    list.first = newElement; // Insert as first (and last) position
  else {
    TElementQ<T> *nav = list.first; // Create auxiliar pointer to navigate the queue
    while (nav->next != NULL)
      nav = nav->next; // Navigate to the last element in the queue
    nav->next = newElement; // Insert element at the end of the queue
  }
  list.size++; // Increment list size
  return true;
}

// Remove first element of the queue
template <typename T>
T dequeue(TListQ<T> &list) {
  if (list.first != NULL) { // Check if list is not empty
    T data = list.first->data; // Save data of the first element
    list.first = list.first->next; // list.first points to second element
    list.size--; // Decrement list size;
    return data; // Return data from first element
  }
  return list.first->data;
}

// Return first element of the queue
template <typename T>
TElementQ<T> firstElement(TListQ<T> list) {
  if (list.first != NULL) // Check if list is not empty
    return list.first;
  return false; // If list is empty
}