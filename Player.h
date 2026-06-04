#pragma once

#include "Dice.h"
#include "Piece.h"
#include <iostream>
#include "MyStr.h"
using namespace std;

class Player
{
protected:
    int playerID;
    MyStr playerName;
    MyStr pieceColor;
    Piece* pieces[4];
    int finishedPieces;
    bool isCurrentTurn;
    Dice dice;

public:
    Player(int id, MyStr name);

    int getPlayerID() const;
    MyStr getPlayerName() const;
    MyStr getPieceColor() const;
    int getFinishedPieces() const;
    bool getIsCurrentTurn() const;
    Piece* getPiece(int pieceNum);

    void setPlayerName(MyStr name);
    void setPieceColor(MyStr color);
    void setFinishedPieces(int count);
    void setIsCurrentTurn(bool turn);
    void setPiece(int pieceNum, Piece* piece);

    void addFinishedPiece();
    bool hasPlayerWon();

    void displayPlayerInfo();
    void displayPieces();

    int rollDice();

    virtual void takeTurn() = 0;
    virtual int choosePiece() = 0;

    virtual ~Player();
};