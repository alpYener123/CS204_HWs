//
// Created by ALP on 4/5/2023.
//


#include "Board.h"
#include <string>
using namespace std;

Board::Board() // default constructor
{
    head = nullptr;
    tail = nullptr;
    xCnt = 0;
    oCnt = 0;
}

// We have a Board object named futureTavla which is defaultly constructed

/* Begin: Code taken and updated from DoublyLinkedList.cpp */
void Board::createSlotEnd(char ch, int num)
{
    if (tail == nullptr) // if the list is empty
    {
        slot * temp = new slot; // create a new slot. This slot will be the only slot so prev and next are pointing to null
        temp -> prev = nullptr;
        temp -> next = nullptr;
        tail = temp;
        head = tail; // hence our head and tail are the same
        for (int i = 0; i < num ; i++)
        {
            if (ch == 'x'){xCnt++;} // updating the xCnt (or oCnt) accordingly
            else if (ch == 'o'){oCnt++;}
            (tail -> slotStack).push(ch); // create the slot
        }
    }

    else // if the list is not empty
    {
        slot * temp = new slot; // create temporary new slot
        temp -> next = nullptr; // that slots next will point to null
        temp -> prev = tail; // that slots prev will point to tail
        tail -> next = temp; // tails next will point to temp
        tail = temp; // our new tail will be temp
        for (int i = 0; i < num ; i++)
        {
            if (ch == 'x'){xCnt++;} // update the xCnt (or oCnt)
            else if (ch == 'o'){oCnt++;}
            (tail -> slotStack).push(ch); // add the chars
        }
    }
}
/* End: Code taken and updated from DoublyLinkedList.cpp */

void Board::createEmptySlotEnd()
{
    if (tail == nullptr) // if the list is empty, create a new slot and make it both the head and the tail
    {
        slot * temp = new slot;
        temp -> prev = nullptr;
        temp -> next = nullptr;
        tail = temp;
        head = tail;
    }

    else // if the list is not empty
    {
        slot * temp = new slot; // create temporary new slot
        temp -> next = nullptr; // that slots next point to null
        temp -> prev = tail; // that slots prev will point to tail
        tail -> next = temp; // tails next will point to temp
        tail = temp; // our new tail will be temp
    }
}

void Board::createSlotBegin(char ch, int num)
{
    if (tail == nullptr) // same process as before, if the list is empty create a new slot and make it both the tail and the head
    {                   // whilst updating the xCnt and oCnt
        slot * temp = new slot;
        temp -> prev = nullptr;
        temp -> next = nullptr;
        tail = temp;
        head = tail;
        for (int i = 0; i < num ; i++)
        {
            if (ch == 'x'){xCnt++;}
            else if (ch == 'o'){oCnt++;}
            (tail -> slotStack).push(ch);
        }
    }

    else // if the list is not empty
    {
        slot * temp = new slot; // create temporary new slot, make it point to null and our head
        temp -> next = head;  // then update the head as the new slot (the temporary one)
        temp -> prev = nullptr;
        head -> prev = temp;
        head = temp;
        for (int i = 0; i < num ; i++)
        {
            if (ch == 'x'){xCnt++;} // update the xCnt/oCnt
            else if (ch == 'o'){oCnt++;}
            (head -> slotStack).push(ch); // add the chars
        }
    }
}

void Board::printBoard() { // The document says we cannot use vectors or arrays so that's why I only used strings

    string board = ""; // create an empty string, we will fill it up
    slot *temp = tail; // our temporary slot
    while (temp != nullptr) { // we will get the content of the stacks until the very end
        CharStack toBePrinted = temp->slotStack; // with = operator create a duplicate of temp
        while (!toBePrinted.isEmpty()) { // until our duplicate is empty, pop the chars and add them to board
            char ch;
            toBePrinted.pop(ch);
            board += ch;
        }
        board += "A"; // this is to indicate new stacks within the string
        temp = temp->prev;
    }

    // flip the string board
    string reversed = "";
    for (int i = board.length()-1; i > -1; i--)
    {
        reversed += board.at(i); // get the whole thing reversed, thats how it should be printed
    }
    reversed = reversed.substr(1) + 'A'; // add the A to not mess up the format
    board = reversed;

    for (int i = 0; i < board.length() - 1; i++) { // switch A with ^
        if (board[i] == 'A') {
            board[i] = '^';
            board.insert(i + 1, "\n"); // to get a paragraph string instead of a lengthy line
        }
    }
    board = board.substr(0, board.length() - 1);
    board += "^\n "; // to get the string be same for all lines

    string tempStr = board;

    int counter = 0;
    int idx = 0;
    while (tempStr.find('\n') != string::npos) { // here, I took the maximum length in a line to adjust the string in the upcoming lines
        int temp = tempStr.find('\n');
        if (counter < temp) { counter = temp; }
        idx = temp + 1;
        tempStr = tempStr.substr(idx);
    }


    string draft = "";

    tempStr = board;

    int numOfRows = 0;

    idx = 0;
    while (tempStr.find('\n') != string::npos) { // I used a similar loop since I cannot use vectors
        int temp = tempStr.find('\n'); // this gives the position of \n also length of that row
        idx = temp + 1;
        string pieceOfRow = tempStr.substr(0,idx); // we got ourselves a row
        tempStr = tempStr.substr(idx); // to continue searching for \n
        int addedSpaces = counter - temp; // max - length of that row
        string add = "";
        for (int a = 0; a < addedSpaces; a++){add+=" ";} // add as much space as needed, this will make all the lines same length
        string row = add + pieceOfRow; // to have that row completed
        draft+=row;
        numOfRows++;
    }

    string final = ""; // our finalized string

    int addThis = counter + 1; // max + 1 (for the ^ char)

    for (int j = 0; j < counter; j++) // loop this as much as the length of a row (the counter's row has no spaces the other ones have
    {                                   // spaces but in the end they all have the same amount of chars)
        string row = ""; // this will be a proper row, the one we will print
        int a = 0;
        for (int k = 0; k < numOfRows; k++) // here, consider the string as a matrix that needs to have rows as columns and columns as rows
        {                                   // addThis will let us access the char exactly one row below the one we are on
            row = row + draft.at(j+a);   // hence we switch rows and columns and get our finalized string
            a += addThis;
        }
        row += '\n';
        final+=row;
    }

    int emptyRow = 5 - counter; // since we need our board to be of length 5 by default
    for (int k = 0; k < emptyRow; k++){cout << endl;} // add the necessary amount of cout's

    cout << final;
}

/* Begin: Code taken and updated from DoublyLinkedList.cpp */
void Board::clearBoard()
{
    slot * temp = tail;
    while(tail != nullptr) // start from tail, delete tail and make tail = tail -> prev
    {
        tail = tail -> prev;
        while (!(temp->slotStack).isEmpty())
        {
            char ch;
            (temp->slotStack).pop(ch);
        } // first delete the stack then delete the pointer
        delete temp;
        temp = nullptr;
        temp = tail;
    }
    head = nullptr;
    xCnt = 0;
    oCnt = 0;
}
/* End: Code taken and updated from DoublyLinkedList.cpp */

bool Board::targetSlotFull(int idx)
{
    slot * temp = head;
    for (int i = 0; i < idx; i++) // go to that index's slot
    {
        temp = temp -> next;
    }
    bool result = (temp -> slotStack).isFull(); // check if it is full or not
    return result;
}

void Board::destroySlot(int idx)
{
    if (idx == 0) // if we want to destroy the head
    {
        char symbol;
        int count = 0;
        while (!(head->slotStack).isEmpty()) // empty out the stack
        {
            char ch;
            (head->slotStack).pop(ch);
            count++;
            symbol = ch;
        }

        slot * temp = head; // assign head -> next as the new head
        head = head -> next;
        head -> prev = nullptr;
        delete temp;
        temp = nullptr;

        if (symbol == 'x'){xCnt-=count;} // update the xCnt/oCnt
        else if (symbol == 'o'){oCnt-=count;}

        return;
    }

    else
    {
        int idxCounter = 0;
        slot * temp = head;
        while((temp -> next) != nullptr) // if the stack is between head and tail
        {
            if (idx == idxCounter) // when we get to our target index
            {
                int count = 0;
                char symbol;
                while (!(temp->slotStack).isEmpty()) // same procedure as before
                {
                    char ch;
                    (temp->slotStack).pop(ch);
                    count++;
                    symbol = ch;
                }
                (temp -> prev) -> next = temp -> next; // delete that stack and link the stacks next to that together
                (temp -> next) -> prev = temp -> prev;
                delete temp;
                temp = nullptr;

                if (symbol == 'x'){xCnt-=count;} // update the xCnt/oCnt
                else if (symbol == 'o'){oCnt-=count;}

                return;
            }
            temp = temp -> next;
            idxCounter++;
        }
        // now our temp = tail since temp -> next == nullptr

        char symbol;
        int count = 0;
        while (!(tail->slotStack).isEmpty()) // same procedure as deleting the head
        {
            char ch;
            (tail->slotStack).pop(ch);
            count++;
            symbol = ch;
        }

        tail = tail -> prev;
        tail -> next = nullptr;
        delete temp;
        temp = nullptr;

        if (symbol == 'x'){xCnt-=count;}
        else if (symbol == 'o'){oCnt-=count;}

        return;
    }
}

int Board::evaluateGame() // we updated our xCnt and oCnt throughout the functions so no hardwork is done here
{
    if (xCnt < oCnt){return 1;}
    else if (oCnt < xCnt){return 2;}
    else {return 3;}
}

bool Board::noMove(char ch, int step)
{
    char symbol; // symbol of temp
    slot * temp = head; // start from head

    int num;
    if (ch == 'x'){num=xCnt;}
    else if (ch == 'o'){num=oCnt;}
    if (num == 0){return true;} // if we do not have any x on the table than x cannot play, vice versa

    while (temp != nullptr) // we will check for every stack
    {
        CharStack tempStack = temp->slotStack; // create a duplicate stack
        if (!tempStack.isEmpty())
        {
            tempStack.pop(symbol);
            if (symbol == ch) // if tempStack is owned by our player
            {
                slot * goRight = temp;
                slot * goLeft = temp;
                int wentLeft = 0, wentRight = 0;
                for (int i = 0; i < step; i++) // try to go "step" amount of steps to left and right
                {
                    if ((goRight -> next) != nullptr){goRight = goRight -> next; wentRight++;}
                    if ((goLeft -> prev) != nullptr){goLeft = goLeft -> prev; wentLeft++;}
                }
                if (wentRight == step) // if we were able to go that much steps
                {
                    if ((goRight->slotStack).isEmpty()) { return false; } // we can move
                    else
                    {
                        CharStack tempRight = goRight->slotStack;
                        char rightCh;
                        tempRight.pop(rightCh);
                        if (rightCh == ch) { return false; } // we can move
                    }
                }

                if (wentLeft == step) // same procedure as before
                {
                    if ((goLeft->slotStack).isEmpty()) { return false; }
                    else {
                        CharStack tempLeft = goLeft->slotStack;
                        char leftCh;
                        tempLeft.pop(leftCh);
                        if (leftCh == ch) { return false; }
                    }
                }
            }
        }
        temp = temp -> next;
    }
    return true; // if we came here than we cannot move
}

int Board::validMove(char ch, int start, int step, int direction)
{
    bool valid = true;
    slot * temp = head;
    if ((temp == nullptr)|| (start < 0)){return 1;} // just in case, if there is no board or some minus index is given
    for (int i = 0; i < start; i++)
    {
        temp = temp -> next;
        if (temp == nullptr){valid = false; break;}
    }
    if (!valid){return 1;} // if our starting index is out of boundary

    // now temp is on the start index

    CharStack charChecker = temp -> slotStack;
    char checker;
    charChecker.pop(checker); // try out our starting index. If it does not belong to our player, return 4
    if (checker != ch){return 4;}

    // now we know that the starting index's slot belongs to our player

    if (direction == 1) // checks if our target index exists
    {
        for (int i = 0; i < step; i++)
        {
            temp = temp -> next;
            if (temp == nullptr){valid = false; break;}
        }
        if (!valid){return 2;}
    }

    else if (direction == 0) // checks if our target index exists
    {
        for (int i = 0; i < step; i++)
        {
            temp = temp -> prev;
            if (temp == nullptr){valid = false; break;}
        }
        if (!valid){return 2;}
    }

    if (!(temp -> slotStack).isEmpty())
    {
        CharStack charCheck = temp -> slotStack;
        char check;
        charCheck.pop(check);
        if (check != ch){return 3;} // checks if our target index belongs to the player
    }
    // now we know that the target slot does not belong to the other player

    return 0;
}

void Board::movePiece(int start, int target)
{
    slot * startTemp = head;
    for (int i = 0; i < start; i++)
    {
        startTemp = startTemp -> next;
    }
    // now startTemp is pointing to our source stack
    char popCh;
    (startTemp->slotStack).pop(popCh); // pop the char from our source stack

    slot * targetTemp = head;
    for (int i = 0; i < target; i++)
    {
        targetTemp = targetTemp -> next;
    }
    // now targetTemp is pointing to our target stack

    (targetTemp->slotStack).push(popCh); // add the char that was popped from our source stack
}