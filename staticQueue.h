#ifndef STATIC_QUEUE_H
#define STATIC_QUEUE_H

// Generic element
template <typename T>
struct TElementQ {
    T data;
};

// Generic Static Queue
template <typename T, int MAX>
struct TListQ {
    TElementQ<T> elements[MAX];
    int size; // Counter of elements' number
};

// Boot Generic Static Queue
template <typename T, int MAX>
void bootStaticQueue(TListQ<T, MAX> &list) {
    list.size = 0;
}

// Insert at the end of the queue
template <typename T, int MAX>
bool queueS(TListQ<T, MAX> &list, T data) {
  if (list.size >= MAX) // Check if list is full
      return false;

  TElementQ<T> e;
  e.data = data;
  list.elements[list.size] = e; // Insert element at last position
  list.size++; // Increase queue size
  return true;
}

// Remove first element in the queue
template <typename T, int MAX>
T dequeueS(TListQ<T, MAX> &list) {
  if (list.size == 0) // Check if queue is empty
      return false;
  
  T data = list.elements[0].data; // Save data of the first element
  for (int i = 0; i < list.size - 1; i++)
      list.elements[i] = list.elements[i + 1];
  list.size--;
  return data; // Return data from first element
}

#endif // STATIC_QUEUE_H
