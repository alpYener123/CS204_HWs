//
// Created by ALP on 5/9/2023.
//

#ifndef HW5_BOARD_H
#define HW5_BOARD_H
#include <string>
using namespace std;

struct Node
{
    string owner;
    Node* next;
    Node () : owner("None"), next(NULL){}; // default constructor
    Node (string o, Node * p): owner(o), next(p) {}; // parametered constructor
};

class Board
{
    private:
        Node * first;

    public:
        Board(int num); // parametered constructor
        ~Board(); // destructor
        void display();
        string who_owns(Node * p);

        // helper functions that are not used in main:
        int howMany(); // how many nodes are there
        Node * getterFirst(); // getter function for the node pointer first
};

#endif //HW5_BOARD_H
