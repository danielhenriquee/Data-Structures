// Daniel Henrique da Silva

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// Generic element type
template <typename T>
struct LinkedL_TElement {
    T data;
    LinkedL_TElement<T> *next;
};

// Generic linked list start of generic elements
template <typename T>
struct LinkedL_TList {
    LinkedL_TElement<T> *start;
};

// Boot list
template <typename T>
bool LinkedL_boot(LinkedL_TList<T> &list) {
    list.start = nullptr;
    return true;
}

// Create new element
template <typename T>
LinkedL_TElement<T> *LinkedL_newElement(const T &data) {
    LinkedL_TElement<T> *e = new LinkedL_TElement<T>;
    e->data = data;
    e->next = nullptr;
    return e;
}

// Insert at the end of the list
template <typename T>
bool LinkedL_insertLast(LinkedL_TList<T> &list, const T &data) {
    LinkedL_TElement<T> *e = LinkedL_newElement(data); // Create new element
  
    if (list.start == nullptr) { // Check if list is empty
        list.start = e; // Insert as first (and last) position
        return true;
    }
    LinkedL_TElement<T> *nav = list.start; // Create auxiliary pointer to navigate the list
    while (nav->next != nullptr)
        nav = nav->next; // Navigate to the last element in the list
    nav->next = e; // Insert element at the end of the list
    return true;
}
  
// Insert at the beginning of the list
template <typename T>
bool LinkedL_insertFirst(LinkedL_TList<T> &list, const T &data) {
    LinkedL_TElement<T> *e = LinkedL_newElement(data); // Create new element
    
    if (list.start == nullptr) { // Check if list is empty
        list.start = e; // Insert as first position
    } else {
        e->next = list.start; // Points to list's first element
        list.start = e; // Becomes first element of the list
    }
    return true;
}

// Insert at chosen position
template <typename T>
bool LinkedL_insertPos(LinkedL_TList<T> &list, const T &data, int pos) {
    if (pos < 0) // Check if position is valid (negative positions are not valid)
        return false;
  
    LinkedL_TElement<T> *e = LinkedL_newElement(data); // Create new element

    if (pos == 0) { // Insert at beginning
        e->next = list.start;
        list.start = e;
        return true;
    }
    
    LinkedL_TElement<T> *nav = list.start; // Create auxiliary pointer to navigate the list
    int i = 0;
    // Traverse until position before the desired one
    while (nav != nullptr && i < pos - 1) {
        nav = nav->next;
        i++;
    }

    if (nav == nullptr) { // Position not reached
        delete e;
        return false;
    }

    // Insert element in the chosen position
    e->next = nav->next; // New element points to the element the previous element was pointing
    nav->next = e; // Element before points to new element
    return true;
}

// Remove last element of the list
template <typename T>
bool LinkedL_removeLast(LinkedL_TList<T> &list) {
    if (list.start == nullptr) { // Check if list is empty
        return false;
    }
    LinkedL_TElement<T> *nav = list.start; // Create auxiliary pointer to navigate the list
    if (nav->next == nullptr) { // Check if list has only one element
        list.start = nullptr; // Remove first (and last) element
        delete nav;
    } else {
        while (nav->next->next != nullptr) {
            nav = nav->next;
        }
        delete nav->next;
        nav->next = nullptr; // Nav points to nullptr, excluding last element off the list
    }
    return true;
}

// Remove first element of the list
template <typename T>
bool LinkedL_removeFirst(LinkedL_TList<T> &list) {
    if (list.start != nullptr) { // Check if list is not empty
        LinkedL_TElement<T>* temp = list.start;
        list.start = list.start->next; // list.start points to second element
        delete temp;
        return true;
    }
    return false;
}

// Remove element at chosen position
template <typename T>
bool LinkedL_removePos(LinkedL_TList<T> &list, int pos) {
    if (list.start == nullptr || pos < 0) // Empty list or invalid position
        return false;

    if (pos == 0) { // Removing first element
        LinkedL_TElement<T>* temp = list.start;
        list.start = list.start->next;
        delete temp;
        return true;
    }
    
    // Traverse to the element before the target position
    LinkedL_TElement<T> *nav = list.start;
    for (int i = 0; i < pos - 1 && nav->next; i++)
        nav = nav->next;
    
    if (!nav->next) // If there is no element at the given position
        return false;

    // Remove the target element
    LinkedL_TElement<T>* temp = nav->next;
    nav->next = temp->next;
    delete temp;
    return true;
}

// Delete all elements of the list
template <typename T>
void LinkedL_destroyList(LinkedL_TList<T> &list) {
    LinkedL_TElement<T>* nav = list.start;
    while (nav) { // Navigate through the list
        LinkedL_TElement<T>* temp = nav;
        nav = nav->next;
        delete temp;
    }
    list.start = nullptr;
    list.end = nullptr;
}

// Check if list is empty
template <typename T>
bool LinkedL_isEmpty(const LinkedL_TList<T> &list) {
    return list.start == nullptr;
}

// Swap
template <typename T>
void LinkedL_swap(LinkedL_TElement<T> *a, LinkedL_TElement<T> *b) {
    if (!a || !b) 
        return;
    T temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// Bubblesort
template <typename T>
void LinkedL_bubblesort(LinkedL_TList<T> &list) {
    if (list.start == nullptr || list.start->next == nullptr) // Nothing to sort
        return;
  
    bool swapped = true;
    LinkedL_TElement<T> *nav = list.start; // Create auxiliary pointer to navigate the list
  
    while (swapped) {
        swapped = false;
        nav = list.start; // Reset nav to the beginning of the list for each loop
        while (nav->next != nullptr) {
            if (nav->data > nav->next->data) { // Check if previous element is greater than next element
                LinkedL_swap(nav,nav->next); // Swap positions
                swapped = true;
            }
            nav = nav->next;
        }
    }
}

// Return last element of the list
template <typename T>
LinkedL_TElement<T>* LinkedL_lastElement(LinkedL_TElement<T> *head) {
    while (head != nullptr && head->next != nullptr)
        head = head->next;
    return head;
}

// Quicksort's partition
template <typename T>
LinkedL_TElement<T>* LinkedL_partition(LinkedL_TElement<T> *head, LinkedL_TElement<T>* end, LinkedL_TElement<T>** newHead, LinkedL_TElement<T>** newEnd) { 
    LinkedL_TElement<T>* pivot = end; 
    LinkedL_TElement<T> *prev = nullptr, *current = head, *tail = pivot; 
  
    // During partition, both head and End of the list might change which is updated in the newHead and newEnd variables 
    while (current != pivot) { // Navigate until penultimate element
        if (current->data < pivot->data) { // Check if element is smaller than pivot
            if ((*newHead) == nullptr)
                (*newHead) = current; 
            prev = current; 
            current = current->next; 
        } else { // If current element is greater than pivot 
            // Move current element to next of tail, and change tail 
            if (prev) 
                prev->next = current->next; 
            LinkedL_TElement<T>* temp = current->next; 
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

// Quicksort recursive
template <typename T>
LinkedL_TElement<T>* LinkedL_quickSortRecursive(LinkedL_TElement<T>* head, LinkedL_TElement<T>* end) { 
    if (!head || head == end) // Base condition 
        return head; 

    LinkedL_TElement<T> *newHead = nullptr, *newEnd = nullptr; 

    // Partition the list, newHead and newEnd will be updated by the partition function 
    LinkedL_TElement<T>* pivot = LinkedL_partition(head, end, &newHead, &newEnd); 

    // If pivot is the smallest element - no need to recurrent for the left part. 
    if (newHead != pivot) { 
        // Set the node before the pivot node as nullptr 
        LinkedL_TElement<T>* tmp = newHead; 
        while (tmp->next != pivot) 
            tmp = tmp->next; 
        tmp->next = nullptr; 

        // Recurrent for the list before pivot 
        newHead = LinkedL_quickSortRecursive(newHead, tmp); 

        // Change next of last node of the left half to pivot 
        tmp = LinkedL_lastElement(newHead); 
        tmp->next = pivot; 
    } 

    // Recurrent for the list after the pivot element 
    pivot->next = LinkedL_quickSortRecursive(pivot->next, newEnd); 

    return newHead; 
} 

// Quicksort
template <typename T>
void LinkedL_quickSort(LinkedL_TElement<T>** headRef) { 
    (*headRef)= LinkedL_quickSortRecursive(*headRef, LinkedL_lastElement(*headRef)); 
    return; 
} 

#endif // LINKED_LIST_H
