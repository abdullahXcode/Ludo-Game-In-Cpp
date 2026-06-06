#pragma once 

#include "Player.h"
#include <iostream>

using namespace std;

class HumanPlayer : public Player
{
private :

public :

    HumanPlayer(int id, MyStr name);

    void takeTurn();
    int choosePiece();

    ~HumanPlayer();
};