//
// Created by ALP on 5/9/2023.
//
#include "Player.h"
#include <string>
using namespace std;
#include <iostream>

int Player::move(int steps)
{
    int returnValue = 0; // will be 1 if the player has stopped or gone past the starting point
    for (int i = 0; i < steps; i++) // moves the player by steps many steps
    {
        position = position -> next;
        if (position == (onBoard.getterFirst())){returnValue = 1;} // if position points to the node that the "first" pointer points on the board, returnValue = 1
    }
    if (returnValue != 1){returnValue = 0;}
    return returnValue;
}

Node * Player::where_am_I(){return (this -> position);} // returns the position

void Player::pay_to_player(Player & otherPlayer, int money)
{
    this -> balance -= money; // left hand side will have money taken from their account
    otherPlayer.balance += money; // otherPlayer will have that money inserted to theirs
}

int Player::get_balance() {return (this -> balance);} // getter for the player's balance
void Player::deposit_money(int deposit) {balance+=deposit;} // adds the deposit value to the players balance

void Player::buy_slot(int slotCost) // buys the slot and updates the slot's owner and the player's balance accordingly
{
    balance-=slotCost;
    position -> owner = name;
}

bool Player::is_bankrupt() // checks if the player has gone bankrupt
{
    if(balance < 0){return true;}
    return false;
}

void Player::display() // displays the positions of the players and their balances
{
    int num = 0; // when the board is displayed, how many nodes after the first node is the player on
    Node * temp = onBoard.getterFirst();
    while(temp != position){num++; temp = temp -> next;} // updates num and finds the position of the player
    string whitespace = ""; // the whitespace before we display the player's name
    for (int i = 0; i < num*6; i++){whitespace += " ";} // adds the whitespace. *6 because for every node 6 space characters are used

    cout << whitespace << name << " " << balance << endl; // prints out in the wanted format
}