/**
 * @file CharStack.cpp
 * @author CS-204
 * @brief Character Stack Implementation
 * @version 0.1
 * @date 2023-03-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// 28.03.2023 Modified by Selim Kirbiyik from IntStack class

#include <iostream>
#include "CharStack.h"
using namespace std;

/**
 * @brief Construct a new Char Stack:: Char Stack object
 * 
 * @param size 
 */
CharStack::CharStack(int size)
{
    stackArray = new char[size];
    stackSize = size;
    top = -1;	// Empty
}

/**
 * Construct a CharStack with size 4 as default
 */
CharStack::CharStack() {
    stackArray = new char[4];
    stackSize = 4;
    top = -1;
}

/**
 * @brief Member function push pushes the argument onto the stack.  
 * 
 * @param sym 
 * @return true 
 * @return false 
 */
bool CharStack::push(char sym)
{
    bool valid  = true;
    if (isFull())
    {
        valid = false;
    }
    else
    {
        top++;
        stackArray[top] = sym;
    }
    return valid;
}

/**
 * @brief Member function pop pops the value at the top
 * of the stack off, and copies it into the variable
 * passed as an argument.
 * 
 * @param sym 
 * @return true 
 * @return false 
 */
bool CharStack::pop(char &sym)
{
    bool valid  = true;
    if (isEmpty())
    {
        valid   = false;
    }
    else
    {
        sym = stackArray[top];
        top--;
    }
    return valid;
}

/**
 * @brief Member function isFull returns true if the stack 
 * is full, or false otherwise.
 * 
 * @return true 
 * @return false 
 */
bool CharStack::isFull()
{
    bool status;

    if (top == stackSize - 1)
        status = true;
    else
        status = false;

    return status;
}

/**
 * @brief Member funciton isEmpty returns true if the stack 
 * is empty, or false otherwise. 
 * 
 * @return true 
 * @return false 
 */
bool CharStack::isEmpty()
{
    bool status;

    if (top == -1)
        status = true;
    else
        status = false;

    return status;
}

CharStack::~CharStack() {
    delete [] stackArray;
}

CharStack::CharStack(const CharStack & chStk) {
    if(this != &chStk)
    {
        stackArray = new char[chStk.stackSize];
        stackSize = chStk.stackSize;
        top = chStk.top;

        for (int i = 0; i < stackSize; i++) {
            this->stackArray[i] = chStk.stackArray[i];
        }
    }
}

CharStack & CharStack::operator=(const CharStack &rhs) {
    if(this != &rhs)
    {
        stackArray = new char[rhs.stackSize];
        stackSize = rhs.stackSize;
        top = rhs.top;

        for (int i = 0; i < stackSize; i++) {
            this->stackArray[i] = rhs.stackArray[i];
        }
    }
    return *this;
}
