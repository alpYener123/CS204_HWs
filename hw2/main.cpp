// Alp Onder Yener CS204 HW2

#include <iostream>
#include <string>
#include "feedback.h"
using namespace std;


// Guessing game using a regular linkedlist

/* Begin: code taken and updated from linkedList.cpp */
struct node // This is my node
{
    int digit;
    node * next;

    node ()
            :digit(-1), next(NULL) // The first pointer will point to a node of -1,
    {}                              // will make more sense in main

    node (int i,node *n)
            :digit(i), next(n)
    {}
};
/* End: code taken and updated from linkedList.cpp */

void insert(node * ptr, int num)
{
    if (ptr -> next == NULL) // The first pointer points to -1 by default so we look at the one after that
    {
        ptr -> next = new node(num, NULL);
    }
    else {
        node * temp = ptr; // Temporary pointer, to go forward in the linked list
        while (temp->next != NULL && temp->next->digit <= num) // The num part is for the insertion to be done with a sort
        {
            temp = temp -> next;
        }

        if (temp-> digit != num) // To avoid adding the same number twice
        {
            temp->next = new node(num, temp->next);
        }
    }
}

void clear(node * ptr) // Clears the whole linked list
{
    node * connect = ptr; // The pointer before the one to be deleted
    ptr = ptr -> next; // Set our original pointer to the next one
    if (ptr == NULL){return;}
    while (ptr != NULL) {
        node * temp = ptr; // temp will be the one to be deleted
        ptr = ptr -> next; // So the structure is like this: connect -> temp -> ptr
        delete temp;
        temp = NULL;
    }
    connect -> next = ptr; // Now the ones in the middle are deleted. The only ones remaining are connect (-1,ptr) and ptr which is NULL
}

void deleteNum(node * ptr, int num) // Deletes a specific number from the linked list
{                                   // ptr->digit = -1 by default
    if (ptr->next == NULL){return;} // If the list is empty, just return
    node* connect = ptr; // The structure will be as follows: connect -> temp -> ptr
    node* temp = ptr->next;
    ptr = temp->next;
    if (ptr == NULL && temp -> digit != num){return;} // One specific condition
    else if (temp -> digit == num){delete temp; temp = NULL; connect -> next = ptr; return;} // Another specific condition
    while (ptr != NULL) // Search through the list
    {
        ptr = ptr -> next;
        temp = temp -> next;
        connect = connect -> next;
        if (temp -> digit == num){delete temp; temp = NULL; connect->next = ptr; return;}
    }
    if (temp -> digit == num){delete temp; temp = NULL; connect->next = ptr; return;} // A specific condition for when we reach the end
}

bool isThere(node * ptr, int num) // To check if there is that number in the list
{
    ptr = ptr -> next; // Since our first node's digit is -1
    if (ptr == NULL){return false;} // If the list is empty
    while (ptr != NULL)
    {
        if (ptr -> digit == num){return true;}
        ptr = ptr -> next;
    }
    return false;
}

void printer(node * ptr) // Prints the list
{
        ptr = ptr -> next; // Since our first node's digit is -1
        if (ptr != NULL){
            node * ok = ptr; // Temporary pointer "ok" is assigned to go through the list
            while (ok != NULL)
            {
                cout << ok -> digit << " ";
                ok = ok -> next;
            }
            return;
        }
        return;
}

int main() {

    node* possible[3]; // created an array of 3 pointers, pointing to a node (which hasnt been created yet)
    node* impossible[3];

    for (int i = 0; i < 3; i++) // Assign new nodes to all the pointers in the arrays, all with digit = -1 and next = NULL
    {
        possible[i] = new node();
        impossible[i] = new node();
    }

    int id; // game id
    string guess; // input guess

    cout << "Please enter a game ID." << endl;
    cin >> id;

    bool goldenNumber[3] = {false, false, false}; // This will come in handy when checking if that slot's number has been
    //                                                              found or not.

    while(true) { // Our entire code loops here
    cout << "Enter your guess." << endl;
    cin >> guess;

    while (true) // after the first guess input, this check is done in order to see if the input guess is valid
    {
        int checker = 0; // If this is 3, our check is done successfully
        if (guess.length() == 3) //checks for the length
        {
            checker++;
            if ((guess[0] != guess[1]) && (guess[0] != guess[2]) && (guess[1] != guess[2])){checker++;} // checks if the digits are unique

            int digitCheck = 0; // used to see if all the digits are actually digits (ASCII TABLE)
            for (int i = 0; i < 3; i++)
            {
                if ((48 <= guess[i]) && (57 >= guess[i])){digitCheck++;}
            }
            if (digitCheck == 3){checker++;} //all 3 digits are actually digits
            if (checker == 3){break;} // if all 3 requirements are met, move on (break)
        }
        cout << "Invalid guess. Enter your guess." << endl; // if the input is invalid, try again
        cin >> guess;
    }

    string feedback = get_the_feedback(guess, id);

    // There are 3 loops. First for G, then for Y and finally for R.
    // The necessary actions are done in a more easy way with this order

        for (int i = 0; i < 3; i++) { // Loop for G
            int num = (int) guess.at(i) - 48; // Using ASCII table to get the digit
            if (feedback.at(i)=='G')
            {
                for (int a = 0; a < 3; a++) // i is for the digit at ith spot
                {                           // a is for running through the spots for i
                    if (a == i)
                    {
                            if (goldenNumber[i] == false)
                            {
                                goldenNumber[i] = true; // We have found the correct number for slot i
                                clear(possible[i]); // Clear the possible linked list for i
                                insert(possible[i], num); // Insert
                                for (int g = 0; g < 10; g++)
                                {
                                    if (g != num)
                                    {
                                        insert(impossible[i], g); // Insert all the digits from 0 to 9 except num
                                    }                                       // in the impossible linked list
                                }
                            }
                    }
                    else{ // if a != i
                        insert(impossible[a], num);
                        deleteNum(possible[a], num);
                    }
                }
            }
        }
        for (int l = 0; l < 3; l++) // this is for Y
        {
            int num = (int) guess.at(l) - 48;
            if (feedback.at(l) == 'Y')
            {
                for (int a = 0; a < 3; a++)
                {
                    if (a == l) // If we have a Y at 2nd slot and a == 2, do these actions:
                    {
                        deleteNum(possible[a], num);
                        insert(impossible[a], num);
                    }
                    else
                    {
                        if ((goldenNumber[a] == false) && isThere(impossible[a], num) == false)
                        { // If we haven't found that number in position "a" and num is not at the impossible[a]
                            insert(possible[a], num);
                        }
                    }
                }
            }
        }


        for (int k = 0; k < 3; k++) // Loop for R
        {
            int num = (int) guess.at(k) - 48;
            if (feedback.at(k) == 'R') {
                insert(impossible[0], num);
                insert(impossible[1], num);
                insert(impossible[2], num);
            }
        }
        // This part is for printing the current lists
        cout << "Linked lists:" << endl;
        cout << "Slot: 1" << endl;
        cout << "Impossibles: ";
        printer(impossible[0]);
        cout << endl;
        cout << "Possibles: ";
        printer(possible[0]);
        cout << endl;
        cout << endl;

        cout << "Slot: 2" << endl;
        cout << "Impossibles: ";
        printer(impossible[1]);
        cout << endl;
        cout << "Possibles: ";
        printer(possible[1]);
        cout << endl;
        cout << endl;

        cout << "Slot: 3" << endl;
        cout << "Impossibles: ";
        printer(impossible[2]);
        cout << endl;
        cout << "Possibles: ";
        printer(possible[2]);
        cout << endl;
        cout << endl;

        // From now on, we will check if we have completed the game with GGG

        int nodeCountOne = 0, nodeCountTwo = 0, nodeCountThree = 0; // How many nodes are in the impossible lists
        node * tempOne = impossible[0] -> next; // To exclude -1
        node * tempTwo = impossible[1] -> next;
        node * tempThree = impossible[2] -> next;

        for (int u = 0; u < 10; u++) // Gets the number of nodes
        {
            if (tempOne != NULL){nodeCountOne++; tempOne = tempOne -> next;}
            if (tempTwo != NULL){nodeCountTwo++; tempTwo = tempTwo -> next;}
            if (tempThree != NULL){nodeCountThree++; tempThree = tempThree -> next;}
        }

        tempOne = impossible[0] -> next; // Takes the temp nodes back to their starting point
        tempTwo = impossible[1] -> next;
        tempThree = impossible[2] -> next;

        int number[3] = {-1,-1,-1}; // Our numbers
        if ((nodeCountOne == 9) && (nodeCountTwo == 9) && (nodeCountThree == 9)) // If we have 9 nodes on the impossible part for all
        {                                                                           // now we know that the game is finished.
                                                                                // just need to find the numbers
            bool one = false, two = false, three = false; // These check if our number for that slot is 0 or not
            if (tempOne -> digit != 0){one = true; number[0] = 0;}
            if (tempTwo -> digit != 0){two = true; number[1] = 0;}
            if (tempThree -> digit != 0){three = true; number[2] = 0;}

            tempOne = tempOne -> next; // Go to the next node
            tempTwo = tempTwo -> next;
            tempThree = tempThree -> next;

            if (!one) // If the number is not 0
            {
                for (int w = 1; w < 9; w++) // 1 to 8
                {
                    if (tempOne -> digit != w) // w is incrementing linearly so as the nodes' digits
                    {                            // if there is a difference, that is our wanted number
                        number[0] = w;
                        one = true;
                        break;
                    }
                    if (tempOne != NULL){tempOne = tempOne -> next;}
                    else{break;}
                }
            }

            if (!two) // same as the previous method, for the second slot
            {
                for (int w = 1; w < 9; w++) // 1 to 8
                {
                    if (tempTwo -> digit != w)
                    {
                        number[1] = w;
                        two = true;
                        break;
                    }
                    if (tempTwo != NULL){tempTwo = tempTwo -> next;}
                    else{break;}
                }
            }

            if (!three) // same as the previous method, for the third slot
            {
                for (int w = 1; w < 9; w++) // 1 to 8
                {
                    if (tempThree -> digit != w)
                    {
                        number[2] = w;
                        three = true;
                        break;
                    }
                    if (tempThree != NULL){tempThree = tempThree -> next;}
                    else{break;}
                }
            }

            if (!one){number[0] = 9;} // if the numbers are not 0 to 8, they must be 9
            if (!two){number[1] = 9;}
            if (!three){number[2] = 9;}

        } // exists the check part
        if ((number[0] != -1) && (number[1] != -1) && (number[2] != -1))
        {
            cout << "The secret number is: " << number[0] << number[1] << number[2] << endl;
            cout << "Congrats! Now, deleting the lists..." << endl;
            break; // break from the while(true) loop
        }
    }


    for (int i = 0; i < 3; i++) // delete the nodes
    {
        clear(possible[i]); // this one deletes the nonnegative digits
        delete possible[i]; // this is for the head, the one with the digit as -1
        possible[i] = NULL;

        clear(impossible[i]);
        delete impossible[i];
        impossible[i] == NULL;
    }
    return 0;
}