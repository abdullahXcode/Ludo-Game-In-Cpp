#pragma once

#include <iostream>

using namespace std;

enum PieceStatus
{
    IN_HOME,
    IN_PLAY,
    IN_SAFE,
    IN_FINISH
};

class Piece
{
private:
    static int pieceCount;
    int pieceID;
    int playerID;
    int currentCellID;
    PieceStatus status;
    int distanceMoved;

public:
    Piece(int owner);

    static void resetPieceCount();
    static int getPieceCount();

    int getPieceID() const;
    int getPlayerID() const;
    int getCurrentCellID() const;
    PieceStatus getStatus() const;
    int getDistanceMoved() const;

    void setCurrentCellID(int cellID);
    void setStatus(PieceStatus newStatus);
    void setDistanceMoved(int distance);

    void movePiece(int steps);
    void capture();
    bool canMove() const;
    bool isAtFinish() const;
    void displayPieceInfo() const;

    ~Piece();
};