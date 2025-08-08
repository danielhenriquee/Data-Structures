// Daniel Henrique da Silva

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

// Generic element T
template <typename T>
struct TElement {
    T data;
};

// Generic static list of generic elements
template <typename T, int MAX>
struct TList {
    TElement<T> elements[MAX];
    int size; // Counter of elements' number
};

// Boot list
template <typename T, int MAX>
void bootStaticListS(TList<T, MAX> &list) {
    list.size = 0;
}

// Insert at the end of the list
template <typename T, int MAX>
bool insertLastS(TList<T, MAX> &list, T data) {
    if (list.size >= MAX) { // Check if list is full
        return false;
    } else {
        TElement<T> element;
        element.data = data;
        list.elements[list.size] = element; // Insert element at last position
        list.size++; // Increase list size
        return true;
  }
}

// Insert at the beginning of the list
template <typename T, int MAX>
bool insertFirstS(TList<T, MAX> &list, T data) {
    if (list.size >= MAX) { // Check if list is full
        return false;
    } else {
        for (int i = list.size; i > 0; i--) {
            list.elements[i] = list.elements[i - 1]; // Pull all elements one spot to the right
        }
  
        TElement<T> element;
        element.data = data;
        list.elements[0] = element; // Insert element at first position
        list.size++; // Increase list size
        return true;
    }
}

// Insert at a position in the list
template <typename T, int MAX>
bool insertPosS(TList<T, MAX> &list, T data, int pos) {
    if ((list.size >= MAX) || (pos > list.size) || pos <= 0) { // Check if: list is full; position chosed is greater than list size; position chosed is an invalid number
        return false;
    } else {
        for (int i = list.size; i >= pos; i--) {
            list.elements[i] = list.elements[i - 1]; // Pull all elements (starting from position chosed) one cell to the right
        }
        TElement<T> element;
        element.data = data;
        list.elements[pos - 1] = element; // Insert element at position chosed
        list.size++; // Increase list size
        return true;
    }
}

// Remove last element in the list
template <typename T, int MAX>
bool removeLastS(TList<T, MAX> &list) {
    if (list.size <= 0) // Check if list is empty
        return false;
    else
        list.size--; // Remove last element
    return true;
}

// Remove first element in the list
template <typename T, int MAX>
bool removeFirstS(TList<T, MAX> &list) {
    if (list.size <= 0) { // Check if list is empty
        return false;
    } else {
        for (int i = 0; i < list.size - 1; i++) {
            list.elements[i] = list.elements[i + 1];
        }
        list.size--;
        return true;
    }
}

// Remove element at a position in the list
template <typename T, int MAX>
bool removePosS(TList<T, MAX> &list, int pos) {
    if ((list.size <= 0) || (pos >= list.size) || pos <= 0) { // Check if list is empty; position chosed is greater than list size; position chosed is an invalid number
        return false;
    } else {
        for (int i = pos; i < list.size - 1; i++) { // Starts at position chosed to be removed
            list.elements[i] = list.elements[i + 1]; // Pull all elements one spot to the left
        }
        list.size--;
        return true;
    }
}

// Swap
template <typename T, int MAX>
void swap(TList<T,MAX> &list, int a, int b) {
    T temp = list.elements[a].data;
    list.elements[a].data = list.elements[b].data;;
    list.elements[b].data = temp;
}

// Bubblesort
template <typename T, int MAX>
void bubblesortS(TList<T, MAX> &list) {
    int swapped = 1;
    T temp;
  
    for (int i = list.size - 1; (i >= 1) && (swapped == 1); i--) {
        swapped = 0;
        for (int j = 0; j < i; j++) {
            if (list.elements[j].data > list.elements[j + 1].data) { // Check if previous element is greater than next element
                swap(list, j, j + 1); // Swap positions
                swapped = 1;
            }
        }
    }
}

// Auxiliar function for quicksort's partition
template <typename T, int MAX>
int partition(TList<T, MAX> &list, int low, int high) {
    T pivot = list.elements[high].data; // Set last element as pivot
    int i = low - 1; // Initialize the index of the smaller element
  
    for (int j = low; j < high; j++) { // Iterates until penultimate element
        if (list.elements[j].data < pivot) { // Check if element is lower than pivot
            i++;
            swap(list, i, j); // Swap element to the left of i
        }
    }
    swap(list, i + 1, high);// Swap pivot to its sorted position
    return (i + 1); // Return partition's index
}

// Quicksort
template <typename T, int MAX>
void quicksortS(TList<T, MAX> &list, int low, int high) {
    if (low < high) {
        int pivot = partition(list, low, high); // Determine pivot element and its position
        quicksort(list, low, pivot - 1); // Recursively sort the left part (lower elements than pivot)
        quicksort(list, pivot + 1, high); // Recursively sort the right part (higher elements than pivot)
    }
}

#endif // STATIC_LIST_H
