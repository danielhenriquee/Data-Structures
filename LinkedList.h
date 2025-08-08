// Daniel Henrique da Silva

#ifndef linkedList_H_INCLUDED
#define linkedList_H_INCLUDED

// Generic element type
template <typename T>
struct TElementL {
    T data;
    TElementL<T> *next;
};

// Generic linked list start's of generic elements
template <typename T>
struct TListL {
    TElementL<T> *start;
};

// Boot list
template <typename T>
bool bootListL(TListL<T> &list) {
    list.start = NULL;
    return true;
}

// Create new element
template <typename T>
TElementL<T> *newElementL(T &data) {
    TElementL<T> *newElement = new TElementL<T>;
    newElement->data = data;
    newElement->next = NULL;
    return newElement;
}

// Insert at the end of the list
template <typename T>
bool insertLastL(TListL<T> &list, T &data) {
    TElementL<T> *newElement = newElementL(data); // Create new element
  
    if (list.start == NULL) {  // Check if list is empty
        list.start = newElement; // Insert as first (and last) position
        return true;
    } else {
        TElementL<T> *nav = list.start; // Create auxiliar pointer to navigate the list
        while (nav->next != NULL)
            nav = nav->next;      // Navigate to the last element in the list
        nav->next = newElement; // Insert element at the end of the list
        return true;
    }
    return false;
}
  
// Insert at the beginning of the list
template <typename T>
bool insertFirstL(TListL<T> &list, T data) {
    TElementL<T> *newElement = newElementL(data); // Create new element
  
    if (list.start == NULL) {  // Check if list is empty
        list.start = newElement; // Insert as first position
        return true;
    } else {
        newElement->next = list.start; // Points to list's first element
        list.start = newElement;       // Became first element of the list
        return true;
    }
}

// Insert at chosen position
template <typename T>
bool insertPosL(TListL<T> &list, T &data, int pos) {
    if (pos < 0) { // Check if position is valid (negative positions are not valid)
        return false;
    }
  
    TElementL<T> *newElement = newElementL(data); // Create new element
  
    if (list.start != NULL) { // Check if list is not empty
        TElementL<T> *nav = list.start; // Create auxiliar pointer to navigate the list
        int cont = 1;
        while (nav->next != NULL && cont < pos - 1) { // Navigate to chosen position or reach last element
            nav = nav->next;
            cont++;
        }
        if (cont != pos - 1) // Check if navigation did not reach position chosed
            return false;
        newElement->next = nav->next; // New element points to the element the before element was pointing
        nav->next = newElement;       // Element before points to new element
        return true;
    } else {                   // If list is empty
        list.start = newElement; // Insert as first element
        return true;
    }
}

// Remove last element of the list
template <typename T>
bool removeLastL(TListL<T> &list) {
    if (list.start == NULL) { // Check if list is empty
        return false;
    } else {
        TElementL<T> *nav = list.start; // Create auxiliar pointer to navigate the list
        if (nav->next == NULL) { // Check if list has only one element
            list.start = NULL;     // Remove first (and last) element
            delete nav;
            return true;
        } else {
            while (nav->next->next != NULL) {
                nav = nav->next;
            }
            nav->next = NULL; // Nav points to NULL, excluding last element (P) off the list
            return true;
        }
    }
}

// Remove first element of the list
template <typename T>
bool removeFirstL(TListL<T> &list) {
    if (list.start != NULL)            // Check if list is not empty
        list.start = list.start->next; // list.start points to second element
    else
        return false;
    return true;
}

// Remove element at chosen position
template <typename T>
bool removePosL(TListL<T> &list, int pos) {
    TElementL<T> *nav = list.start; // Create auxiliar pointer to navigate the list
    if (list.start != NULL or pos >= 0) { // Check if list is not empty or position invalid (equal or less than 0)
        int cont = 1;
        if (pos == 1) { // Check if wants to remove first position
            list.start = list.start->next; // Start of the list now is the second element
            return true;
        }
        while (nav->next != NULL && cont < pos-1) { // Navigate until position chosed or last position
            nav = nav->next;
            cont++;
        }
        if (nav->next == NULL) { // Check if navigation did not reach position chosed
            return false;
        }
        nav->next = nav->next->next; // Nav jumps on element and points to the next one
        return true;
    }
    return false;
}

// Swap
template <typename T>
void swap(TElementL<T> *a, TElementL<T> *b) {
    T temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// Bubblesort
template <typename T>
void bubblesortL(TListL<T> &list) {
    if (list.start == NULL or list.start->next == NULL) // Nothing to sort
        return;
  
    int swapped = 1;
    TElementL<T> *nav = list.start; // Create auxiliar pointer to navigate the list
  
    while (swapped == 1) {
        swapped = 0;
        nav = list.start; // Reset nav to the beginning of the list for each loop
        while (nav->next != NULL) {
            if (nav->data > nav->next->data) { // Check if previous element is greater than next element
                swap(nav,nav->next); // Swap positions
                swapped = 1;
            }
            nav = nav->next;
        }
    }
}

// Return last element of the list
template <typename T>
TElementL<T>* lastElement(TElementL<T> *head) {
    while (head != NULL && head->next != NULL)
        head = head->next;
    return head;
}

// Quicksort's partition
template <typename T>
TElementL<T>* partition(TElementL<T> *head, TElementL<T>* end, TElementL<T>** newHead, TElementL<T>** newEnd) { 
    TElementL<T>* pivot = end; 
    TElementL<T> *prev = NULL, *current = head, *tail = pivot; 
  
    // During partition, both head and End of the list might change which is updated in the newHead and newEnd variables 
    while (current != pivot) { // Navigate until penultimate element
        if (current->data < pivot->data) { // Check if element is tailer than pivot
            if ((*newHead) == NULL)
                (*newHead) = current; 
            prev = current; 
            current = current->next; 
        } else { // If current element is greater than pivot 
            // Move current element to next of tail, and change tail 
            if (prev) 
                prev->next = current->next; 
            TElementL<T>* temp = current->next; 
            current->next = NULL; 
            tail->next = current; 
            tail = current; 
            current = temp; 
        } 
    } 
  
    if ((*newHead) == NULL) // Check if the pivot data is the smallest element in the list, pivot becomes the head 
        (*newHead) = pivot; // Pivot becomes the newHead
    (*newEnd) = tail; // Update newEnd to the current last element 
    return pivot; // Return the pivot
} 

// Quicksort recurrent
template <typename T>
TElementL<T>* quickSortRecurrent(TElementL<T>* head, TElementL<T>* end) { 
    if (!head || head == end) // Base condition 
        return head; 

    TElementL<T> *newHead = NULL, *newEnd = NULL; 

    // Partition the list, newHead and newEnd will be updated by the partition function 
    TElementL<T>* pivot = partition(head, end, &newHead, &newEnd); 

    // If pivot is the smallest element - no need to recurrent for the left part. 
    if (newHead != pivot) { 
        // Set the node before the pivot node as NULL 
        TElementL<T>* tmp = newHead; 
        while (tmp->next != pivot) 
            tmp = tmp->next; 
        tmp->next = NULL; 

        // Recurrent for the list before pivot 
        newHead = quickSortRecurrent(newHead, tmp); 

        // Change next of last node of the left half to pivot 
        tmp = lastElement(newHead); 
        tmp->next = pivot; 
    } 

    // Recurrent for the list after the pivot element 
    pivot->next = quickSortRecurrent(pivot->next, newEnd); 

    return newHead; 
} 

// Quicksort
template <typename T>
void quickSort(TElementL<T>** headRef) { 
    (*headRef)= quickSortRecurrent(*headRef, lastElement(*headRef)); 
    return; 
} 

#endif // linkedList_H_INCLUDED
