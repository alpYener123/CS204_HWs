//
// Created by ALP on 4/4/2023.
//

#ifndef HW3_BOARD_H
#define HW3_BOARD_H

using namespace std;

#include <iostream>
#include "CharStack.h"

struct slot
{
    slot * next;
    slot * prev;
    CharStack slotStack;
    slot ()
    {}
};

class Board
{
    private:
        slot * head;
        slot * tail;
        int xCnt;
        int oCnt;

    public:
        Board();
        void createSlotEnd(char ch, int num);
        void createEmptySlotEnd();
        void createSlotBegin(char ch, int num);
        void printBoard();
        void clearBoard();
        bool targetSlotFull(int idx);
        void destroySlot(int idx);
        int evaluateGame();
        bool noMove(char ch, int step);
        int validMove(char ch, int start, int step, int direction);
        void movePiece(int start, int target);
};












#endif
