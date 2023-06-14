#ifndef CHARSTACK_H
#define CHARSTACK_H


/**
 * @brief Character Stack Implementation
 */
class CharStack
{
private:
    char *stackArray{};
    int stackSize{};
    int top{};

public:
    CharStack(const CharStack&); // copy constructor, creates a new
    // CharStack by copying the given CharStack
    CharStack& operator=(const CharStack &rhs); // An assignment
    // operator that assigns the contents of one CharStack object
    // to another.
    CharStack(int);
    ~CharStack();
    CharStack();
    bool push(char);
    bool pop(char &); // pops the top char and stores it
    bool isFull(void);
    bool isEmpty(void);
};

#endif