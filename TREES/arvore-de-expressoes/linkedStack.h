#ifndef linkedStack_H_INCLUDED
#define linkedStack_H_INCLUDED

#include <iostream>

// Generic element
template <typename T>
struct StackNode {
    T data;
    StackNode<T> *next; // Points to next element of the stack
};

// Generic linked stack
template <typename T>
struct Stack { 
    StackNode<T> *top;
};

// Boot generic linked stack
template <typename T>
void bootStack(Stack<T> &stack) {
    stack.top = NULL;
}

// Insert at the top of the stack
template <typename T>
void push(Stack<T> &stack, T data) {
    StackNode<T> *newNode = new StackNode<T>;
    newNode->data = data;
    newNode->next = stack.top; // Points to stack's top node
    stack.top = newNode; // New node became top node of the stack
}

// Remove top element of the stack
template <typename T>
T pop(Stack<T> &stack) {
    if (stack.top == NULL) // Check if stack is empty
        return NULL;
    else {
        T data = stack.top->data; // Save data of the top node
        stack.top = stack.top->next; // stack.top points to second node
        return data; // Return data from top node
    }
}

// Check if stack is empty
template <typename T>
bool isEmpty(Stack<T> stack) {
    return stack.top == NULL; // Empty = 1, Filled = 0
}

// Return top node's data
template <typename T>
T top(Stack<T> stack) {
    if (stack.top == NULL)
        return NULL;
    return stack.top->data;
}

#endif // linkedStack_H_INCLUDED