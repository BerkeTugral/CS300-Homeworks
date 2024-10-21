#include "stack.h"

// Constructor to initialize an empty stack
template <class Object>
Stack<Object>::Stack() {}

// Check if the stack is empty
template <class Object>
bool Stack<Object>::isEmpty() const {
    return theArray.empty();
}

// Access the top element (without removing it)
template <class Object>
const Object& Stack<Object>::top() const {
    if (isEmpty()) {
        throw std::runtime_error("UNDERFLOW: Stack is empty.");
    }
    return theArray.back();
}

// Remove the top element
template <class Object>
void Stack<Object>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("UNDERFLOW: Stack is empty.");
    }
    theArray.pop_back();
}

// Add an element to the top of the stack
template <class Object>
void Stack<Object>::push(const Object& x) {
    theArray.push_back(x);
}

// Clear the stack
template <class Object>
void Stack<Object>::makeEmpty() {
    theArray.clear();
}

// Access and remove the top element
template <class Object>
Object Stack<Object>::topAndPop() {
    if (isEmpty()) {
        throw std::runtime_error("UNDERFLOW: Stack is empty.");
    }
    Object topElement = theArray.back();
    theArray.pop_back();
    return topElement;
}
