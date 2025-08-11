// Daniel Henrique da Silva

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

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
    list.start = nullptr;
    return true;
}

// Create new element
template <typename T>
TElementL<T> *newElementL(T &data) {
    TElementL<T> *e = new TElementL<T>;
    e->data = data;
    e->next = nullptr;
    return e;
}

// Insert at the end of the list
template <typename T>
bool insertLastL(TListL<T> &list, T &data) {
    TElementL<T> *e = newElementL(data); // Create new element
  
    if (list.start == nullptr) { // Check if list is empty
        list.start = e; // Insert as first (and last) position
        return true;
    } else {
        TElementL<T> *nav = list.start; // Create auxiliar pointer to navigate the list
        while (nav->next != nullptr)
            nav = nav->next; // Navigate to the last element in the list
        nav->next = e; // Insert element at the end of the list
        return true;
    }
    return false;
}
  
// Insert at the beginning of the list
template <typename T>
bool insertFirstL(TListL<T> &list, T data) {
    TElementL<T> *e = newElementL(data); // Create new element
  
    if (list.start == nullptr) { // Check if list is empty
        list.start = e; // Insert as first position
        return true;
    } else {
        e->next = list.start; // Points to list's first element
        list.start = e; // Became first element of the list
        return true;
    }
}

// Insert at chosen position
template <typename T>
bool insertPosL(TListL<T> &list, T &data, int pos) {
    if (pos < 0) { // Check if position is valid (negative positions are not valid)
        return false;
    }
  
    TElementL<T> *e = newElementL(data); // Create new element
  
    if (list.start != nullptr) { // Check if list is not empty
        TElementL<T> *nav = list.start; // Create auxiliar pointer to navigate the list
        int cont = 1;
        while (nav->next != nullptr && cont < pos - 1) { // Navigate to chosen position or reach last element
            nav = nav->next;
            cont++;
        }
        if (cont != pos - 1) // Check if navigation did not reach position chosed
            return false;
        e->next = nav->next; // New element points to the element the before element was pointing
        nav->next = e; // Element before points to new element
        return true;
    } else { // If list is empty
        list.start = e; // Insert as first element
        return true;
    }
}

// Remove last element of the list
template <typename T>
bool removeLastL(TListL<T> &list) {
    if (list.start == nullptr) { // Check if list is empty
        return false;
    } else {
        TElementL<T> *nav = list.start; // Create auxiliar pointer to navigate the list
        if (nav->next == nullptr) { // Check if list has only one element
            list.start = nullptr; // Remove first (and last) element
            delete nav;
            return true;
        } else {
            while (nav->next->next != nullptr) {
                nav = nav->next;
            }
            delete nav->next;
            nav->next = nullptr; // Nav points to nullptr, excluding last element (P) off the list
            return true;
        }
    }
}

// Remove first element of the list
template <typename T>
bool removeFirstL(TListL<T> &list) {
    if (list.start != nullptr) { // Check if list is not empty
        TElementL<T>* temp = list.start;
        list.start = list.start->next; // list.start points to second element
        delete temp;
    } else
        return false;
    return true;
}

// Remove element at chosen position
template <typename T>
bool removePosL(TListL<T> &list, int pos) {
    // Check if the list is empty or if the position is invalid (must be >= 1)
    if (list.start == nullptr || pos < 1) {
        return false;
    }

    // If removing the first element
    if (pos == 1) {
        TElementL<T>* temp = list.start;
        list.start = list.start->next; // Move start pointer // Start of the list now is the second element
        delete temp;
        return true;
    }

    // Traverse to the element before the target position
    TElementL<T>* current = list.start;
    for (int i = 1; i < pos - 1 && current->next != nullptr; i++) {
        current = current->next;
    }

    // If there is no element at the given position
    if (current->next == nullptr) {
        return false;
    }

    // Remove the target element
    TElementL<T>* temp = current->next;
    current->next = temp->next;
    delete temp;
    return true;
}

// Delete all elements of the list
template <typename T>
void destroyL(TListL<T> &list) {
    TElementL<T>* nav = list.start;
    while (nav) { // Navigate through the list
        TElementL<T>* temp = nav;
        nav = nav->next;
        delete temp;
    }
    list.start = nullptr;
}

// Check if list is empty
template <typename T>
bool isEmptyL(const TListL<T> &list) {
    return list.start == nullptr;
}

// Swap
template <typename T>
void swapL(TElementL<T> *a, TElementL<T> *b) {
    T temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// Bubblesort
template <typename T>
void bubblesortL(TListL<T> &list) {
    if (list.start == nullptr || list.start->next == nullptr) // Nothing to sort
        return;
  
    int swapped = 1;
    TElementL<T> *nav = list.start; // Create auxiliar pointer to navigate the list
  
    while (swapped == 1) {
        swapped = 0;
        nav = list.start; // Reset nav to the beginning of the list for each loop
        while (nav->next != nullptr) {
            if (nav->data > nav->next->data) { // Check if previous element is greater than next element
                swapL(nav,nav->next); // Swap positions
                swapped = 1;
            }
            nav = nav->next;
        }
    }
}

// Return last element of the list
template <typename T>
TElementL<T>* lastElementL(TElementL<T> *head) {
    while (head != nullptr && head->next != nullptr)
        head = head->next;
    return head;
}

// Quicksort's partition
template <typename T>
TElementL<T>* partitionL(TElementL<T> *head, TElementL<T>* end, TElementL<T>** newHead, TElementL<T>** newEnd) { 
    TElementL<T>* pivot = end; 
    TElementL<T> *prev = nullptr, *current = head, *tail = pivot; 
  
    // During partition, both head and End of the list might change which is updated in the newHead and newEnd variables 
    while (current != pivot) { // Navigate until penultimate element
        if (current->data < pivot->data) { // Check if element is tailer than pivot
            if ((*newHead) == nullptr)
                (*newHead) = current; 
            prev = current; 
            current = current->next; 
        } else { // If current element is greater than pivot 
            // Move current element to next of tail, and change tail 
            if (prev) 
                prev->next = current->next; 
            TElementL<T>* temp = current->next; 
            current->next = nullptr; 
            tail->next = current; 
            tail = current; 
            current = temp; 
        } 
    } 
  
    if ((*newHead) == nullptr) // Check if the pivot data is the smallest element in the list, pivot becomes the head 
        (*newHead) = pivot; // Pivot becomes the newHead
    (*newEnd) = tail; // Update newEnd to the current last element 
    return pivot; // Return the pivot
} 

// Quicksort recurrent
template <typename T>
TElementL<T>* quickSortRecurrentL(TElementL<T>* head, TElementL<T>* end) { 
    if (!head || head == end) // Base condition 
        return head; 

    TElementL<T> *newHead = nullptr, *newEnd = nullptr; 

    // Partition the list, newHead and newEnd will be updated by the partition function 
    TElementL<T>* pivot = partitionL(head, end, &newHead, &newEnd); 

    // If pivot is the smallest element - no need to recurrent for the left part. 
    if (newHead != pivot) { 
        // Set the node before the pivot node as nullptr 
        TElementL<T>* tmp = newHead; 
        while (tmp->next != pivot) 
            tmp = tmp->next; 
        tmp->next = nullptr; 

        // Recurrent for the list before pivot 
        newHead = quickSortRecurrentL(newHead, tmp); 

        // Change next of last node of the left half to pivot 
        tmp = lastElementL(newHead); 
        tmp->next = pivot; 
    } 

    // Recurrent for the list after the pivot element 
    pivot->next = quickSortRecurrentL(pivot->next, newEnd); 

    return newHead; 
} 

// Quicksort
template <typename T>
void quickSortL(TElementL<T>** headRef) { 
    (*headRef)= quickSortRecurrentL(*headRef, lastElement(*headRef)); 
    return; 
} 

#endif // LINKED_LIST_H
