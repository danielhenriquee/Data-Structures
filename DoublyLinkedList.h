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
    TElementDL<T> *last;
};

// Boot list
template <typename T>
bool bootListDL(TListDL<T> &list) {
    list.start = NULL;
    list.last = NULL;
    return true;
}

// Create new element
template <typename T>
TElementDL<T> *newElementDL(T &data) {
    TElementDL<T> *newElement = new TElementDL<T>;
    newElement->data = data;
    newElement->next = NULL;
    newElement->prev = NULL;
    return newElement;
}

// Insert at the end of the list
template <typename T>
bool insertLastDL(TListDL<T> &list, T &data) {
    TElementDL<T> *newElement = newElementDL(data); // Create new element
  
    if (list.start == NULL) { // Check if list is empty
        list.start = newElement;
        list.last = newElement;
        return true;
    } else {
        list.last->next = newElement; // Last element of the list points to new element
        newElement->prev = list.last; // New element's prev points to last element of the list
        list.last = newElement; // New element became the last element of the lis
        return true;
    }
    return false;
}

// Insert at the beginning of the list
template <typename T>
bool insertFirstDL(TListDL<T> &list, T data) {
    TElementDL<T> *newElement = newElementDL(data); // Create new element
  
    if (list.start == NULL) { // Check if list is empty
        list.start = newElement;
        list.last = newElement;
        return true;
    } else {
        newElement->next = list.start; // Points to first element of the list
        newElement->next->prev = newElement; // First element's prev points to new element
        list.start = newElement; // New element became first element of the list
        return true;
    }
}

// Insert at chosen position in the list
template <typename T>
bool insertPosDL(TListDL<T> &list, T &data, int pos) {
    if (pos <= 0) { // Check if position is valid (negative positions are not valid)
        return false;
    } else {
        TElementDL<T> *newElement = newElementDL(data); // Create new element
    
        if (list.start == NULL) { // Check if list is empty
            list.start = newElement;
            list.last = newElement;
            return true;
        } else {
            TElementDL<T> *nav = list.start; // Create auxiliar pointer to navigate the list
            int cont = 1;
            while (cont != pos && nav->next != NULL) { // Navigate until chosen position or last element of the list
                nav = nav->next;
                cont++;
            }
            if (cont != pos) // Check if navigation did not reach position chosed
                return false;
      
            if (nav->next == NULL) // Check if will be inserted at last position
                list.last = newElement; // New element became last element of the list
            if (nav->prev == NULL) // Check if will be inserted at first position
                list.start = newElement; // New element became first element of the list
      
            newElement->next = nav; // New element's next points to element at chosen position
            newElement->prev = nav->prev; // New element's prev points to nav's prev
            if (nav->prev != NULL) // Check if there is a previus element
                nav->prev->next = newElement; // Previous element's next points to new element
            nav->prev = newElement; // New elements's became next element's prev
      
            return true;
        }
    }
}

// Remove last element of the list
template <typename T>
bool removeLastDL(TListDL<T> &list) {
    if (list.start == NULL) // Check if list is empty
        return false;
    else {
        if (list.start->next == NULL) { // Just one element in the list
            list.start = NULL;
            list.last = NULL;
            return true;
        } else {
            list.last = list.last->prev; // Penultimate element of the list became last element
            list.last->next = NULL; // Last element's next points to NULL
            return true;
        }
    }
    return false;
}

// Remove first element of the list
template <typename T>
bool removeFirstDL(TListDL<T> &list) {
    if (list.start == NULL) // Check if list is empty
        return false;
    else {
        list.start = list.start->next; // Start of the list now is the second element
        list.start->prev = NULL;
        if (list.start->next == NULL) // If left only one element in the list
            list.last = list.start; // First element of the list became also end of the list
        return true;
    }
    return false;
}

// Remove element at chosen position
template <typename T>
bool removePosDL(TListDL<T> &list, int pos) {
    if (pos <= 0 || list.start == NULL ) // Check if: position is valid (negative positions are not valid), list is empty
        return false;
    else if (pos == 1) { // If wants to remove first element
        if (list.start->next == NULL) { // Check if list just has one element
            list.start = NULL;
            list.last = NULL;
            return true;
        }
          list.start = list.start->next; // Start of the list now is the second element
          list.start->prev = NULL;
          if (list.start->next == NULL) // If left only one element in the list
              list.last = list.start; // First element of the list became also end of the list
          return true;
    } else {
        TElementDL<T> *nav = list.start; // Create auxiliar pointer to navigate the list
        int cont = 1;
        while (cont < pos && nav->next != NULL){ // Navigate until chosen position or last element of the list
            nav = nav->next;
            cont++;
        }
        if (nav->next == NULL) { // Check if navigation did not reach position chosed
            return false;
        }
        else {
            if (nav->prev == NULL){ // If nav is the first element of the list
                list.start = nav->next; // Second element became start of the list
            }
            if (nav->next == NULL){ // If nav is the last element of the list
                list.last = nav->prev; // Penultimate element became end of the list
            }
            nav->prev->next = nav->next; // Previous element's next points to nav's next element
            nav->next->prev = nav->prev; // Next element's prev points to nav's previous element
      
            delete nav;
            return true;
        }
    }
}

// Swap
template <typename T>
void swap(TElementDL<T> *a, TElementDL<T> *b) {
    T temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// Bubblesort
template <typename T>
void bubblesortDL(TListDL<T> &list) {
    if (list.start == NULL or list.start->next == NULL) // Nothing to sort
        return;
    int swapped = 1;
    TElementDL<T> *nav = list.start; // Create auxiliar pointer to navigate the list
    while (swapped == 1) {
        swapped = 0;
        nav = list.start; // Reset nav to the beginning of the list for each loop
        while (nav->next != NULL) {
            if (nav->data > nav->next->data) { // Check if previous element is greater than next element
                swap(nav, nav->next); // Swap data of nav and next element
                swapped = 1;
            }
            nav = nav->next;
        }
    }
}

// Auxiliar function for quicksort's partition
template <typename T>
TElementDL<T>* partitionDL(TListDL<T> &list, TElementDL<T> *low, TElementDL<T> *high) {
    T pivot = high->data; // Set last element as pivot
    TElementDL<T> *i = low->prev; // Initialize the index of the smaller element
  
    for (TElementDL<T> *j = low; j != high; j = j->next) { // Navigate until penultimate element
        if (j->data < pivot) { // Check if element is lower than pivot
            if (i == NULL) {
                i = low;
            } else {
                i = i->next; // Move the index of the smaller element to the next element
            }
            swap(i, j); // Swap current element with the element at the index of the smaller element
        }
    }
    if (i == NULL) {
        i = low;
    } else {
        i = i->next;
    }
    swap(i, high); 
    return i; // Return the index of the pivot element
}

// Quicksort
template <typename T>
void quickSortDL(TListDL<T> &list, TElementDL<T> *low, TElementDL<T> *high) {
    if (high != NULL && low != high && low != high->next) {
        TElementDL<T> *pivot = partitionDL(list, low, high); // Determine pivot element and its position
        quickSortDL(list, low, pivot->prev); // Recursively sort the left part (lower elements than pivot)
        quickSortDL(list, pivot->next, high); // Recursively sort the right part (higher elements than pivot)
    }
}

#endif // DOUBLYLINKEDLIST_H
