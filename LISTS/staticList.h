// Daniel Henrique da Silva

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

// Generic element T
template <typename T>
struct StaticL_TElement {
    T data;
};

// Generic static list of generic elements
template <typename T, int MAX>
struct StaticL_TList {
    StaticL_TElement<T> elements[MAX];
    int size; // Counter of elements' number
};

// Boot list
template <typename T, int MAX>
void StaticL_boot(StaticL_TList<T, MAX> &list) {
    list.size = 0;
}

// Insert at the end of the list
template <typename T, int MAX>
bool StaticL_insertLast(StaticL_TList<T, MAX> &list, const T &data) {
    if (list.size >= MAX) { // Check if list is full
        return false;
    }

    list.elements[list.size].data = data; // Insert element at last position
    list.size++; // Increase list size
    return true;
}

// Insert at the beginning of the list
template <typename T, int MAX>
bool StaticL_insertFirst(StaticL_TList<T, MAX> &list, const T &data) {
    if (list.size >= MAX) { // Check if list is full
        return false;
    }
    
    for (int i = list.size; i > 0; i--)
        list.elements[i] = list.elements[i - 1]; // Pull all elements one spot to the right
  
    list.elements[0].data = data; // Insert element at first position
    list.size++; // Increase list size
    return true;
}

// Insert at a position in the list
template <typename T, int MAX>
bool StaticL_insertPos(StaticL_TList<T, MAX> &list, const T &data, int pos) {
    if ((list.size >= MAX) || (pos > list.size) || pos < 0) // Check if: list is full; chosen position is greater than list size; chosen position is an invalid number
        return false;

    for (int i = list.size; i > pos; i--)
        list.elements[i] = list.elements[i - 1]; // Pull all elements (starting from chosen position) one cell to the right
    
    list.elements[pos].data = data; // Insert element at chosen position
    list.size++; // Increase list size
    return true;
}

// Remove last element in the list
template <typename T, int MAX>
bool StaticL_removeLast(StaticL_TList<T, MAX> &list) {
    if (list.size <= 0) // Check if list is empty
        return false;
    
    list.size--; // Remove last element
    return true;
}

// Remove first element in the list
template <typename T, int MAX>
bool StaticL_removeFirst(StaticL_TList<T, MAX> &list) {
    if (list.size <= 0) { // Check if list is empty
        return false;
    }
    for (int i = 0; i < list.size - 1; i++)
        list.elements[i] = list.elements[i + 1];
    list.size--;
    return true;
}

// Remove element at a position in the list
template <typename T, int MAX>
bool StaticL_removePos(StaticL_TList<T, MAX> &list, int pos) {
    if ((list.size <= 0) || (pos >= list.size) || pos < 0) { // Check if list is empty; chosen position is greater than list size; chosen position is an invalid number
        return false;
    }
    for (int i = pos; i < list.size - 1; i++) // Starts at chosen position to be removed
        list.elements[i] = list.elements[i + 1]; // Pull all elements one spot to the left
    list.size--;
    return true;
}

// Swap
template <typename T, int MAX>
void StaticL_swap(StaticL_TList<T,MAX> &list, int a, int b) {
    if (a < 0 || a >= list.size || b < 0 || b >= list.size || a == b)
        return;
    T temp = list.elements[a].data;
    list.elements[a].data = list.elements[b].data;
    list.elements[b].data = temp;
}

// Bubblesort
template <typename T, int MAX>
void StaticL_bubblesort(StaticL_TList<T, MAX> &list) {
    bool swapped = true;
    T temp;
  
    for (int i = list.size - 1; (i >= 1) && (swapped); i--) {
        swapped = false;
        for (int j = 0; j < i; j++) {
            if (list.elements[j].data > list.elements[j + 1].data) { // Check if previous element is greater than next element
                StaticL_swap(list, j, j + 1); // Swap positions
                swapped = true;
            }
        }
    }
}

// Auxiliary function for quicksort's partition
template <typename T, int MAX>
int StaticL_partition(StaticL_TList<T, MAX> &list, int low, int high) {
    T pivot = list.elements[high].data; // Set last element as pivot
    int i = low - 1; // Initialize the index of the smaller element
  
    for (int j = low; j < high; j++) { // Iterates until penultimate element
        if (list.elements[j].data < pivot) { // Check if element is smaller than pivot
            i++;
            StaticL_swap(list, i, j); // Swap element to the left of i
        }
    }
    StaticL_swap(list, i + 1, high);// Swap pivot to its sorted position
    return (i + 1); // Return partition's index
}

// Quicksort
template <typename T, int MAX>
void StaticL_quicksort(StaticL_TList<T, MAX> &list, int low, int high) {
    if (low < high) {
        int pivot = StaticL_partition(list, low, high); // Determine pivot element and its position
        StaticL_quicksort(list, low, pivot - 1); // Recursively sort the left part (smaller elements than pivot)
        StaticL_quicksort(list, pivot + 1, high); // Recursively sort the right part (higher elements than pivot)
    }
}

#endif // STATIC_LIST_H
