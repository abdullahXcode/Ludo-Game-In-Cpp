#pragma once

#include "Cell.h"
#include "Piece.h"
#include <iostream>

using namespace std;

class Board
{
private:
    Cell mainBoard[52];
    Cell homePath[4][8];
    Piece* pieces[4][4];

    int safeZones[6]; // 0, 9, 18, 27, 36, 45

public:
    Board();
    ~Board();

    void createBoard();
    void setupMainBoard();
    void setupHomePath();
    void setupPieces();
    void markSafeZones();

    Piece* getPiece(int player, int pieceNum);
    Cell* getMainCell(int cellNum);
    Cell* getHomeCell(int player, int homePosition);

    bool isSafeZone(int cellNum);

    bool canPieceMove(Piece* piece, int diceValue);
    int getGlobalCellID(int playerID, int distanceMoved);
    bool movePiece(Piece* piece, int diceValue);
    void capturePiece(int cellNum, int playerID);
    bool checkWinner(Piece* piece);
    void captureOpponentPieces(Piece* piece, int cellID);

    void showBoard();
    void showMainBoard();
    void showHomePath();
    void showAllPieces();
};