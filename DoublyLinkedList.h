// Daniel Henrique da Silva

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

// Generic element
template <typename T>
struct TElementDL {
    T data;
    TElementDL<T> *next; // Points to next element
    TElementDL<T> *prev; // Points to previous element
};

// Generic list doubly linked
template <typename T>
struct TListDL {
    TElementDL<T> *start;
    TElementDL<T> *end;
};

// Boot list
template <typename T>
bool bootListDL(TListDL<T> &list) {
    list.start = nullptr;
    list.end = nullptr;
    return true;
}

// Create new element
template <typename T>
TElementDL<T> *newElementDL(const T &data) {
    TElementDL<T> *e = new TElementDL<T>;
    e->data = data;
    e->next = nullptr;
    e->prev = nullptr;
    return e;
}

// Insert at the end of the list
template <typename T>
bool insertLastDL(TListDL<T> &list, const T &data) {
    TElementDL<T> *e = newElementDL(data); // Create new element
    if (list.start == nullptr) { // If list is empty
        list.start = e;
        list.end = e;
        return true;
    }
    list.end->next = e; // Last element of the list points to new element
    e->prev = list.end; // New element's prev points to last element of the list
    list.end = e; // New element became the last element of the lis
    return true;
}

// Insert at the beginning of the list
template <typename T>
bool insertFirstDL(TListDL<T> &list, const T &data) {
    TElementDL<T> *e = newElementDL(data); // Create new element
  
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
bool insertPosDL(TListDL<T> &list, const T &data, int pos) {
    if (pos < 0) // Check if position is valid (negative positions are not valid)
        return false;

    if (list.start == nullptr || pos == 0) { // If list is empty or pos = 0
        return insertFirstDL(list, data);
    }

    TElementDL<T> *nav = list.start; // Create auxiliar pointer to navigate the list
    int i = 0;
    while (i < pos-1 && nav->next != nullptr) { // Navigate until chosen position or last element of the list
        nav = nav->next;
        i++;
    }

    if (i != pos-1) { // Invalid position
        return false;
    }

    TElementDL<T> *e = newElementDL(data);
    e->prev = nav;
    e->next = nav->next;

    if (nav->next != nullptr) { // Inserting at the middle
        nav->next->prev = e; // Previous element's next points to new element
    } else { // Inserting at the end position
        list.end = e; // New element became last element of the list
    }
    
    nav->next = e;
    return true;
}

// Remove last element of the list
template <typename T>
bool removeLastDL(TListDL<T> &list) {
    if (list.start == nullptr) // Check if list is empty
        return false;
    
    TElementDL<T>* temp = list.end;
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
bool removeFirstDL(TListDL<T> &list) {
    if (list.start == nullptr) { // Check if list is empty
        return false;
    } 
    TElementDL<T>* temp = list.start;
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
bool removePosDL(TListDL<T> &list, int pos) {
    if (pos < 0 || list.start == nullptr) // Check if: position is valid (negative positions are not valid) || list is empty
        return false;

    TElementDL<T> *nav = list.start; // Create auxiliary pointer to navigate the list
    int i = 0;
    // Navigate until chosen position or last element of the list
    while (i < pos && nav) {
        nav = nav->next;
        i++;
    }

    if (nav == nullptr) // Invalid position
        return false;

    // If removing first element
    if (nav == list.start) {
        list.start = nav->next; // Second element becomes start of the list
        if (list.start != nullptr)
            list.start->prev = nullptr;
        else
            list.end = nullptr; // List became empty
        delete nav;
        return true;
    }

    // If removing last element
    if (nav == list.end) {
        list.end = nav->prev; // Penultimate element became end of the list
        if (list.end != nullptr)
            list.end->next = nullptr;
        else
            list.start = nullptr;
        delete nav;
        return true;
    }

    // Removing element in the middle
    nav->prev->next = nav->next; // Previous element's next points to nav's next element
    nav->next->prev = nav->prev; // Next element's prev points to nav's previous element

    delete nav;
    return true;
}

// Swap
template <typename T>
void swapDL(TElementDL<T> *a, TElementDL<T> *b) {
    if (!a || !b) 
        return;
    T temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// Bubblesort
template <typename T>
void bubblesortDL(TListDL<T> &list) {
    if (list.start == nullptr || list.start->next == nullptr) // Nothing to sort
        return;
    bool swapped = true;
    TElementDL<T> *nav = list.start; // Create auxiliary pointer to navigate the list
    while (swapped) {
        swapped = false;
        nav = list.start; // Reset nav to the beginning of the list for each loop
        while (nav->next != nullptr) {
            if (nav->data > nav->next->data) { // Check if previous element is greater than next element
                swapDL(nav, nav->next); // Swap data of nav and next element
                swapped = true;
            }
            nav = nav->next;
        }
    }
}

// Auxiliar function for quicksort's partition
template <typename T>
TElementDL<T>* partitionDL(TElementDL<T> *low, TElementDL<T> *high) {
    T pivot = high->data; // Set last element as pivot
    TElementDL<T> *i = low->prev; // Initialize the index of the smaller element
  
    for (TElementDL<T> *j = low; j != high; j = j->next) { // Navigate until penultimate element
        if (j->data < pivot) { // Check if element is lower than pivot
            if (i == nullptr) {
                i = low;
            } else {
                i = i->next; // Move the index of the smaller element to the next element
            }
            swapDL(i, j); // Swap current element with the element at the index of the smaller element
        }
    }
    if (i == nullptr) {
        i = low;
    } else {
        i = i->next;
    }
    swapDL(i, high); 
    return i; // Return the index of the pivot element
}

// Quicksort
template <typename T>
void quickSortDL(TListDL<T> &list, TElementDL<T> *low, TElementDL<T> *high) {
    if (high != nullptr && low != high && low != high->next) {
        TElementDL<T> *pivot = partitionDL(low, high); // Determine pivot element and its position
        quickSortDL(list, low, pivot->prev); // Recursively sort the left part (lower elements than pivot)
        quickSortDL(list, pivot->next, high); // Recursively sort the right part (higher elements than pivot)
    }
}

// Destroy the list (free all memory)
template <typename T>
void destroyListDL(TListDL<T> &list) {
    TElementDL<T> *nav = list.start;
    while (nav != nullptr) {
        TElementDL<T> *temp = nav;
        nav = nav->next;
        delete temp;
    }
    list.start = nullptr;
    list.end = nullptr;
}

// Return the size of the list
template <typename T>
int sizeDL(const TListDL<T> &list) {
    int size = 0;
    TElementDL<T> *nav = list.start;
    while (nav != nullptr) {
        size++;
        nav = nav->next;
    }
    return size;
}

#endif // DOUBLYLINKEDLIST_H
