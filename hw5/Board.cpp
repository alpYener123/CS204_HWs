//
// Created by ALP on 5/9/2023.
//

#include <iostream>
#include "Board.h"
using namespace std;

Board::Board(int num)
{
    first = new Node; // dynamically allocate nodes
    Node * temp = first; // temp will go through the circular linked list while creating new nodes at each step
    for (int i = 1; i < num; i++) // i does not start from 0 since we already have a starting node (first)
    {
        temp -> next = new Node;
        temp = temp -> next;
    }
    temp -> next = first; // link the last node with first
}

Board::~Board()
{
    if (first != NULL) { // if the board exists with elements
        Node *temp = first->next;
        while (temp != first) { // until we go from (first -> next) node to first node, delete the node
            Node *deleted = temp;
            temp = temp->next;
            delete deleted;
        }
        delete first; // delete the first node
        first = NULL;
    }
}

void Board::display()
{
    int nodeCnt = this -> howMany();
    string upperRow, lowerRow = "|----<", spaces; // the lower row's most left side has this by default
    Node * temp = first;
    for (int i = 0; i < nodeCnt-1; i++) // except for the first node, go through all the other nodes
    {
        string own = temp -> owner;
        if (temp -> owner != "None"){own+=" ";} // for all the upper row nodes to have 4 chars
        upperRow += own + "->"; // example: "Ali ->"
        temp = temp -> next;

        if (i < nodeCnt -2){lowerRow += "-----<";} // the nodes between the last and the first node have this in the lower row
    }
    string own = temp -> owner;
    if (temp -> owner != "None"){own+=" ";}
    upperRow += own; // the last name on the display will not have ->

    lowerRow += "---v"; // the specific lower row display for the last node
    spaces += "^"; // first char of the middle row (the row with the spaces)
    for (int i = 0; i < lowerRow.length()-2; i++){spaces += " ";} // add the necessary amount of spaces
    spaces += "|"; // add this to the end
    cout << upperRow << endl; // print out the board
    cout << spaces << endl;
    cout << lowerRow << endl;
}

string Board::who_owns(Node *p) // returns the owner of the node on the parameter
{
    return (p->owner);
}

Node * Board::getterFirst() // getter function for the node pointer "first"
{
    return (this -> first);
}

int Board::howMany() // prerequisite: Board must have the first node
{
    int i = 1;
    if (first -> next != NULL) // if we have more than the first node
    {
        Node * temp = first -> next;
        while(temp != first) // go over the board, doing i++ on every node
        {
            i++;
            temp = temp -> next;
        }
    }
    return i; // i is the number of nodes
}