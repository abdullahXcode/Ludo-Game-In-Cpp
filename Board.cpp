#include "Board.h"

////////////////////////////////////// CONSTRUCTOR //////////////////////////////////////////

Board::Board()
{
    createBoard();
}

////////////////////////////////////// FUNCTIONS //////////////////////////////////////////

void Board::createBoard()
{
    setupMainBoard();
    setupHomePath();
    setupPieces();
    markSafeZones();
    cout << "Board created with all Ludo rules !" << endl;
}
void Board::setupMainBoard()
{
    for (int i = 0; i < 52; i++)
    {
        mainBoard[i] = Cell(i * 10, 0);
    }
    cout << "Main board created : 52 cells" << endl;
}
void Board::setupHomePath()
{
    for (int player = 0; player < 4; player++)
    {
        for (int homePos = 0; homePos < 8; homePos++)
        {
            homePath[player][homePos] = Cell(player * 100, homePos * 10);
            homePath[player][homePos].setHomeZone(true);
        }
    }
    cout << "Home path created : 4 players × 8 cells" << endl;
}
void Board::setupPieces()
{
    for (int player = 0; player < 4; player++)
    {
        for (int pieceNum = 0; pieceNum < 4; pieceNum++)
        {
            pieces[player][pieceNum] = new Piece(player);
        }
    }
    cout << "Created 16 pieces: 4 players × 4 pieces" << endl;
}
void Board::markSafeZones()
{
    safeZones[0] = 0;
    safeZones[1] = 9;
    safeZones[2] = 18;
    safeZones[3] = 27;
    safeZones[4] = 36;
    safeZones[5] = 45;

    for (int i = 0; i < 6; i++)
    {
        mainBoard[safeZones[i]].setSafeZone(true);
    }

    cout << "Safe zones marked at : 0, 9, 18, 27, 36, 45" << endl;
}

////////////////////////////////////// GETTERS //////////////////////////////////////////

Piece* Board::getPiece(int player, int pieceNum)
{
    if (player < 0 || player >= 4)
    {
        cout << "Invalid player !" << endl;
        return nullptr;
    }

    if (pieceNum < 0 || pieceNum >= 4)
    {
        cout << "Invalid piece !" << endl;
        return nullptr;
    }

    return pieces[player][pieceNum];
}
Cell* Board::getMainCell(int cellNum)
{
    if (cellNum < 0 || cellNum >= 52)
    {
        cout << "Invalid cell number !" << endl;
        return nullptr;
    }
    return &mainBoard[cellNum];
}
Cell* Board::getHomeCell(int player, int homePosition)
{
    if (player < 0 || player >= 4)
    {
        cout << "Invalid player !" << endl;
        return nullptr;
    }

    if (homePosition < 0 || homePosition >= 8)
    {
        cout << "Invalid home position !" << endl;
        return nullptr;
    }

    return &homePath[player][homePosition];
}

////////////////////////////////////// FUNCTIONS //////////////////////////////////////////

bool Board::isSafeZone(int cellNum)
{
    for (int i = 0; i < 6; i++)
    {
        if (safeZones[i] == cellNum)
            return true;
    }
    return false;
}
bool Board::canPieceMove(Piece* piece, int diceValue)
{
    if (piece == nullptr)
        return false;

    if (piece->getStatus() == IN_HOME)
    {
        if (diceValue == 6)
            return true;
        else
            return false;
    }

    if (piece->getStatus() == IN_FINISH)
        return false;

    return true;
}
bool Board::movePiece(Piece* piece, int diceValue)
{
    if (!canPieceMove(piece, diceValue))
        return false;

    int currentDistance = piece->getDistanceMoved();
    int newDistance = currentDistance + diceValue;

    if (newDistance > 60)
    {
        cout << "Cannot move! Would overshoot finish!" << endl;
        return false;
    }

    if (piece->getStatus() == IN_HOME && diceValue == 6)
    {
        piece->setStatus(IN_PLAY);
        piece->setDistanceMoved(1);
        piece->setCurrentCellID(0);
        cout << "Piece enters board at cell 0 !" << endl;
        return true;
    }

    if (newDistance <= 52)
    {
        piece->setDistanceMoved(newDistance);
        piece->setCurrentCellID(newDistance - 1);

        if (isSafeZone(newDistance - 1))
        {
            piece->setStatus(IN_SAFE);
            cout << "Piece moved to safe zone !" << endl;
        }
        else
        {
            piece->setStatus(IN_PLAY);
        }

        return true;
    }

    if (newDistance > 52 && newDistance <= 60)
    {
        piece->setDistanceMoved(newDistance);

        int homePosition = newDistance - 53;
        piece->setCurrentCellID(-1);
        piece->setStatus(IN_SAFE);

        cout << "Piece entered home path at position " << homePosition << endl;

        if (newDistance == 60)
        {
            piece->setStatus(IN_FINISH);
            cout << "PIECE FINISHED!!!" << endl;
        }

        return true;
    }

    return false;
}
void Board::capturePiece(int cellNum, int playerID)
{
    if (isSafeZone(cellNum))
    {
        cout << "Cannot capture! Safe zone!" << endl;
        return;
    }

    for (int otherPlayer = 0; otherPlayer < 4; otherPlayer++)
    {
        if (otherPlayer == playerID)
            continue;

        for (int pieceNum = 0; pieceNum < 4; pieceNum++)
        {
            Piece* otherPiece = getPiece(otherPlayer, pieceNum);

            if (otherPiece != nullptr && otherPiece->getCurrentCellID() == cellNum)
            {
                otherPiece->capture();
                cout << "Player " << playerID << " captured Player " << otherPlayer << "'s piece! Sent back to home!" << endl;
                return;
            }
        }
    }
}
bool Board::checkWinner(Piece* piece)
{
    if (piece == nullptr)
        return false;

    if (piece->getDistanceMoved() == 60 && piece->getStatus() == IN_FINISH)
    {
        cout << "\n*** PLAYER " << piece->getPlayerID() << " WINS WITH PIECE " << piece->getPieceID() << " ***\n" << endl;
        return true;
    }

    return false;
}
void Board::showMainBoard()
{
    cout << "\n===== MAIN BOARD (52 cells) =====" << endl;

    for (int i = 0; i < 52; i++)
    {
        cout << "Cell " << i << " : ";

        // Check if safe zone
        if (isSafeZone(i))
            cout << "[SAFE] ";

        cout << endl;
    }
}
void Board::showHomePath()
{
    cout << "\n===== HOME PATH (4 players × 8 cells) =====" << endl;

    for (int player = 0; player < 4; player++)
    {
        cout << "Player " << player << " home path : ";

        for (int pos = 0; pos < 8; pos++)
        {
            cout << "[" << pos << "] ";
        }
        cout << endl;
    }
}
void Board::showAllPieces()
{
    cout << "\n===== ALL PIECES =====" << endl;

    for (int player = 0; player < 4; player++)
    {
        cout << "\nPlayer " << player << " : " << endl;

        for (int pieceNum = 0; pieceNum < 4; pieceNum++)
        {
            Piece* p = getPiece(player, pieceNum);
            if (p != nullptr)
            {
                p->displayPieceInfo();
            }
        }
    }
}
void Board::showBoard()
{
    showMainBoard();
    showHomePath();
    showAllPieces();
}

////////////////////////////////////// DESTRUCTOR //////////////////////////////////////////

Board::~Board()
{
    for (int player = 0; player < 4; player++)
    {
        for (int pieceNum = 0; pieceNum < 4; pieceNum++)
        {
            if (pieces[player][pieceNum] != nullptr)
            {
                delete pieces[player][pieceNum];
                pieces[player][pieceNum] = nullptr;
            }
        }
    }
    cout << "Board destroyed !" << endl;
}