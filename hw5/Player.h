//
// Created by ALP on 5/9/2023.
//

#ifndef HW5_PLAYER_H
#define HW5_PLAYER_H
#include "Board.h"
#include <string>
using namespace std;

class Player
{
    private:
        Board & onBoard; // each player will have a board. Since we want 2 players to play on a single board, the reference will be given
        string name;
        int balance;
        Node * position;

    public:
        Player(Board & b, string n, int m):onBoard(b), name(n), balance(m), position(onBoard.getterFirst()){}; // parametered constructor
        int move(int steps); // moves the player on the Board
        Node * where_am_I(); // tells where the player is
        void pay_to_player(Player & otherPlayer, int money); // makes the exchange of some money from one player to the otehr
        int get_balance(); // getter for the player's balance
        void deposit_money(int deposit); // deposits money to the balance of the player
        void buy_slot(int slotCost); // buys slot and updates balance accordingly
        bool is_bankrupt(); // checks if the player is bankrupt or not
        void display(); // displays players and their balances according to their positions

};




#endif //HW5_PLAYER_H
