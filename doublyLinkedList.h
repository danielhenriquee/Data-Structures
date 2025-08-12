// Daniel Henrique da Silva

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

// Generic element
template <typename T>
struct DoublyLinkedL_TElement {
    T data;
    DoublyLinkedL_TElement<T> *next; // Points to next element
    DoublyLinkedL_TElement<T> *prev; // Points to previous element
};

// Generic doubly linked list
template <typename T>
struct DoublyLinkedL_TList {
    DoublyLinkedL_TElement<T> *start;
    DoublyLinkedL_TElement<T> *end;
};

// Boot list
template <typename T>
bool DoublyLinkedL_boot(DoublyLinkedL_TList<T> &list) {
    list.start = nullptr;
    list.end = nullptr;
    return true;
}

// Create new element
template <typename T>
DoublyLinkedL_TElement<T> *DoublyLinkedL_newElement(const T &data) {
    DoublyLinkedL_TElement<T> *e = new DoublyLinkedL_TElement<T>;
    e->data = data;
    e->next = nullptr;
    e->prev = nullptr;
    return e;
}

// Insert at the end of the list
template <typename T>
bool DoublyLinkedL_insertLast(DoublyLinkedL_TList<T> &list, const T &data) {
    DoublyLinkedL_TElement<T> *e = DoublyLinkedL_newElement(data); // Create new element
    if (list.start == nullptr) { // If list is empty
        list.start = e;
        list.end = e;
        return true;
    }
    list.end->next = e; // Last element of the list points to new element
    e->prev = list.end; // New element's prev points to last element of the list
    list.end = e; // New element became the last element of the list
    return true;
}

// Insert at the beginning of the list
template <typename T>
bool DoublyLinkedL_insertFirst(DoublyLinkedL_TList<T> &list, const T &data) {
    DoublyLinkedL_TElement<T> *e = DoublyLinkedL_newElement(data); // Create new element
  
    if (list.start == nullptr) { // Check if list is empty
        list.start = e;
        list.end = e;
        return true;
    }
    e->next = list.start; // Points to first element of the list
    list.start->prev = e; // First element's prev points to new element
    list.start = e; // New element became first element of the list
    return true;
}

// Insert at chosen position in the list
template <typename T>
bool DoublyLinkedL_insertPos(DoublyLinkedL_TList<T> &list, const T &data, int pos) {
    if (pos < 0) // Check if position is valid (negative positions are not valid)
        return false;

    if (list.start == nullptr || pos == 0) { // If list is empty or pos = 0
        return DoublyLinkedL_insertFirst(list, data);
    }

    DoublyLinkedL_TElement<T> *nav = list.start; // Create auxiliary pointer to navigate the list
    int i = 0;
    while (i < pos-1 && nav->next != nullptr) { // Navigate until chosen position or last element of the list
        nav = nav->next;
        i++;
    }

    if (i != pos-1) { // Invalid position
        return false;
    }

    DoublyLinkedL_TElement<T> *e = DoublyLinkedL_newElement(data);
    e->prev = nav;
    e->next = nav->next;

    if (nav->next != nullptr) { // Inserting at the middle
        nav->next->prev = e; // Previous element's next points to new element
    } else { // Inserting at the end position
        list.end = e; // New element becomes the last element of the list
    }
    
    nav->next = e;
    return true;
}

// Remove last element of the list
template <typename T>
bool DoublyLinkedL_removeLast(DoublyLinkedL_TList<T> &list) {
    if (list.start == nullptr) // Check if list is empty
        return false;
    
    DoublyLinkedL_TElement<T>* temp = list.end;
    if (list.start->next == nullptr) { // Just one element in the list
        list.start = nullptr;
        list.end = nullptr;
    } else {
        list.end = list.end->prev; // Penultimate element of the list became last element
        list.end->next = nullptr; // Last element's next points to nullptr
    }
    delete temp;
    return true; 
}

// Remove first element of the list
template <typename T>
bool DoublyLinkedL_removeFirst(DoublyLinkedL_TList<T> &list) {
    if (list.start == nullptr) { // Check if list is empty
        return false;
    } 
    DoublyLinkedL_TElement<T>* temp = list.start;
    if (list.start->next == nullptr) { // If there is only one element in the list
        list.start = nullptr;
        list.end = nullptr;
    } else {
        list.start = list.start->next; // Start of the list now is the second element
        list.start->prev = nullptr;
    }
    delete temp;
    return true;
}

// Remove element at chosen position
template <typename T>
bool DoublyLinkedL_removePos(DoublyLinkedL_TList<T> &list, int pos) {
    if (pos < 0 || list.start == nullptr) // Check if: position is valid (negative positions are not valid) || list is empty
        return false;

    if (pos == 0) { // Removing first element
        return DoublyLinkedL_removeFirst(list);
    }
    
    DoublyLinkedL_TElement<T> *nav = list.start; // Create auxiliary pointer to navigate the list
    int i = 0;
    // Navigate until chosen position or last element of the list
    while (i < pos-1 && nav->next != nullptr) {
        nav = nav->next;
        i++;
    }

    if (nav->next == nullptr) // Invalid position
        return false;

    DoublyLinkedL_TElement<T> *toRemove = nav->next;
    if (toRemove == list.end) { // If removing last element
        list.end = nav;
        nav->next = nullptr;
    } else { // Removing element in the middle
        nav->next = toRemove->next;
        toRemove->next->prev = nav;
    }
    delete toRemove;
    return true;
}

// Swap
template <typename T>
void DoublyLinkedL_swap(DoublyLinkedL_TElement<T> *a, DoublyLinkedL_TElement<T> *b) {
    if (!a || !b) 
        return;
    T temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// Bubblesort
template <typename T>
void DoublyLinkedL_bubblesort(DoublyLinkedL_TList<T> &list) {
    if (list.start == nullptr || list.start->next == nullptr) // Nothing to sort
        return;
    bool swapped = true;
    DoublyLinkedL_TElement<T> *nav = list.start; // Create auxiliary pointer to navigate the list
    while (swapped) {
        swapped = false;
        nav = list.start; // Reset nav to the beginning of the list for each loop
        while (nav->next != nullptr) {
            if (nav->data > nav->next->data) { // Check if previous element is greater than next element
                DoublyLinkedL_swap(nav, nav->next); // Swap data of nav and next element
                swapped = true;
            }
            nav = nav->next;
        }
    }
}

// Auxiliary function for quicksort's partition
template <typename T>
DoublyLinkedL_TElement<T>* DoublyLinkedL_partition(DoublyLinkedL_TElement<T> *low, DoublyLinkedL_TElement<T> *high) {
    T pivot = high->data; // Set last element as pivot
    DoublyLinkedL_TElement<T> *i = low->prev; // Initialize the index of the smaller element
  
    for (DoublyLinkedL_TElement<T> *j = low; j != high; j = j->next) { // Navigate until penultimate element
        if (j->data < pivot) { // Check if element is lower than pivot
            if (i == nullptr) {
                i = low;
            } else {
                i = i->next; // Move the index of the smaller element to the next element
            }
            DoublyLinkedL_swap(i, j); // Swap current element with the element at the index of the smaller element
        }
    }
    if (i == nullptr) {
        i = low;
    } else {
        i = i->next;
    }
    DoublyLinkedL_swap(i, high); 
    return i; // Return the index of the pivot element
}

// Quicksort
template <typename T>
void DoublyLinkedL_quickSort(DoublyLinkedL_TList<T> &list, DoublyLinkedL_TElement<T> *low, DoublyLinkedL_TElement<T> *high) {
    if (high != nullptr && low != high && low != high->next) {
        DoublyLinkedL_TElement<T> *pivot = DoublyLinkedL_partition(low, high); // Determine pivot element and its position
        DoublyLinkedL_quickSort(list, low, pivot->prev); // Recursively sort the left part (lower elements than pivot)
        DoublyLinkedL_quickSort(list, pivot->next, high); // Recursively sort the right part (higher elements than pivot)
    }
}

// Destroy the list (free all memory)
template <typename T>
void DoublyLinkedL_destroyList(DoublyLinkedL_TList<T> &list) {
    DoublyLinkedL_TElement<T> *nav = list.start;
    while (nav != nullptr) {
        DoublyLinkedL_TElement<T> *temp = nav;
        nav = nav->next;
        delete temp;
    }
    list.start = nullptr;
    list.end = nullptr;
}

// Return the size of the list
template <typename T>
int DoublyLinkedL_size(const DoublyLinkedL_TList<T> &list) {
    int size = 0;
    DoublyLinkedL_TElement<T> *nav = list.start;
    while (nav != nullptr) {
        size++;
        nav = nav->next;
    }
    return size;
}

#endif // DOUBLYLINKEDLIST_H
