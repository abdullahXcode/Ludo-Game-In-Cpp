#pragma once

#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Board;

class AIPlayer : public Player
{
private:
    int difficulty;
    Board* gameBoard;

public :

    AIPlayer(int id, MyStr name, int level = 1);

    void setGameBoard(Board* board);

    void takeTurn();
    int choosePiece();

    int choosePieceWithDice(int diceValue);
    int getRandomPiece();
    int getSmartPiece(int diceValue);
    int getHardPiece(int diceValue);
    bool canCaptureOpponent(int pieceNum, int diceValue);
    int findCaptureablePiece(int diceValue);
    int getBestProgressPiece();

    ~AIPlayer();
};