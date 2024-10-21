#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

template <class Object>
class Stack {
    
public:
    
    Stack();  // Constructor

    bool isEmpty() const;        // Check if the stack is empty
    const Object& top() const;   // Access the top element
    void pop();                  // Remove the top element
    void push(const Object& x);  // Add an element to the top
    void makeEmpty();            // Clear the stack
    Object topAndPop();          // Access and remove the top element

private:
    
    std::vector<Object> theArray;
    
};

#endif
