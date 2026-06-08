#include "AIPlayer.h"
#include "Board.h"

////////////////////////////////////// CONSTRUCTOR //////////////////////////////////////////

AIPlayer::AIPlayer(int id, MyStr name, int level) : Player(id, name)
{
    if (level < 1 || level > 3)
        difficulty = 1;
    else
        difficulty = level;

    gameBoard = nullptr;

    cout << playerName << " : (AI - Level " << difficulty << ") created ! " << endl;
}

////////////////////////////////////// SET GAME BOARD //////////////////////////////////////////

void AIPlayer::setGameBoard(Board* board)
{
    gameBoard = board;
}

////////////////////////////////////// OVERRIDE FUNCTIONS //////////////////////////////////////////

void AIPlayer::takeTurn()
{
    cout << "\n========================================" << endl;
    cout << "*** " << playerName << " (" << pieceColor << ") - AI TURN! ***" << endl;
    cout << "========================================" << endl;

    displayPlayerInfo();

    cout << "\nAI Difficulty : ";

    if (difficulty == 1)
        cout << "EASY (Random choices)" << endl;
    else if (difficulty == 2)
        cout << "MEDIUM (Smart choices)" << endl;
    else
        cout << "HARD (Very strategic)" << endl;

    cout << "\nAI's Pieces : " << endl;
    displayPieces();

    cout << "\n" << playerName << " (AI) is thinking..." << endl;

    int diceValue = rollDice();

    cout << "\nAI is analyzing board..." << endl;
    int pieceChoice = choosePieceWithDice(diceValue);
    
    Piece* chosenPiece = getPiece(pieceChoice);

    if (chosenPiece != nullptr)
    {
        cout << "\nAI chose Piece " << pieceChoice << endl;
        chosenPiece->displayPieceInfo();
        cout << "AI will move with value : " << diceValue << endl;
    }

    cout << "\n" << playerName << " (AI) completed turn!" << endl;
}
int AIPlayer::choosePiece()
{
    return getRandomPiece();
}

////////////////////////////////////// FUNCTIONS //////////////////////////////////////////

int AIPlayer::choosePieceWithDice(int diceValue)
{
    if (difficulty == 1)
    {
        cout << "AI (Easy) : Choosing randomly..." << endl;
        return getRandomPiece();
    }

    if (difficulty == 2)
    {
        cout << "AI (Medium) : Looking for captures..." << endl;
        return getSmartPiece(diceValue);
    }

    cout << "AI (Hard) : Strategic analysis..." << endl;
    return getHardPiece(diceValue);
}

////////////////////////////////////// RANDOM PIECE //////////////////////////////////////////

int AIPlayer::getRandomPiece()
{
    int pieceNum;
    bool validPiece = false;
    int attempts = 0;

    while (!validPiece && attempts < 20)
    {
        pieceNum = rand() % 4;

        Piece* piece = getPiece(pieceNum);

        if (piece == nullptr)
        {
            attempts++;
            continue;
        }

        if (piece->getStatus() == IN_FINISH)
        {
            attempts++;
            continue;
        }

        if (piece->getStatus() == IN_HOME)
        {
            int lastDice = dice.getDiceValue();

            if (lastDice == 6)
                validPiece = true;
            else
            {
                attempts++;
                continue;
            }
        }
        else
        {
            validPiece = true;
        }
    }

    if (!validPiece)
    {
        cout << "No valid piece to move!" << endl;
        return 0;
    }

    return pieceNum;
}

////////////////////////////////////// SMART PIECE //////////////////////////////////////////

int AIPlayer::getSmartPiece(int diceValue)
{
    if (gameBoard == nullptr)
    {
        cout << "Board not set! Using random choice." << endl;
        return getRandomPiece();
    }

    int captureablePiece = findCaptureablePiece(diceValue);

    if (captureablePiece != -1)
    {
        cout << "AI (Medium) : Found opponent to capture! Choosing Piece "
            << captureablePiece << endl;

        return captureablePiece;
    }

    cout << "AI (Medium) : No opponent to capture. Choosing randomly." << endl;

    return getRandomPiece();
}

////////////////////////////////////// HARD PIECE //////////////////////////////////////////

int AIPlayer::getHardPiece(int diceValue)
{
    if (gameBoard == nullptr)
    {
        cout << "Board not set! Using random choice." << endl;
        return getRandomPiece();
    }

    int captureablePiece = findCaptureablePiece(diceValue);

    if (captureablePiece != -1)
    {
        cout << "AI (Hard) : Found opponent to capture! Choosing Piece "
            << captureablePiece << endl;

        return captureablePiece;
    }

    int bestProgressPiece = getBestProgressPiece();

    if (bestProgressPiece != -1)
    {
        cout << "AI (Hard) : Advancing piece closest to finish. Choosing Piece "
            << bestProgressPiece << endl;

        return bestProgressPiece;
    }

    cout << "AI (Hard) : No capture or progress. Choosing randomly." << endl;

    return getRandomPiece();
}

////////////////////////////////////// FIND CAPTURABLE PIECE //////////////////////////////////////////

int AIPlayer::findCaptureablePiece(int diceValue)
{
    for (int pieceNum = 0; pieceNum < 4; pieceNum++)
    {
        Piece* piece = getPiece(pieceNum);

        if (piece == nullptr ||
            piece->getStatus() == IN_HOME ||
            piece->getStatus() == IN_FINISH)
        {
            continue;
        }

        if (canCaptureOpponent(pieceNum, diceValue))
        {
            return pieceNum;
        }
    }

    return -1;
}

////////////////////////////////////// CAN CAPTURE OPPONENT //////////////////////////////////////////

bool AIPlayer::canCaptureOpponent(int pieceNum, int diceValue)
{
    if (gameBoard == nullptr)
        return false;

    Piece* piece = getPiece(pieceNum);

    if (piece == nullptr)
        return false;

    if (piece->getStatus() == IN_FINISH)
        return false;

    if (piece->getStatus() == IN_HOME)
    {
        if (diceValue != 6)
            return false;
    }

    int currentDistance = piece->getDistanceMoved();
    int newDistance = currentDistance + diceValue;

    if (newDistance < 1 || newDistance > 52)
        return false;

    int targetCell = newDistance - 1;

    Cell* cell = gameBoard->getMainCell(targetCell);

    if (cell == nullptr)
        return false;

    if (cell->getIsOccupied() && !cell->getIsSafeZone())
    {
        int occupiedByPlayer = cell->getOccupiedByPlayerID();

        if (occupiedByPlayer != -1 &&
            occupiedByPlayer != playerID)
        {
            cout << "    → Piece " << pieceNum
                << " can capture at cell "
                << targetCell << " !" << endl;

            return true;
        }
    }

    return false;
}

////////////////////////////////////// BEST PROGRESS PIECE //////////////////////////////////////////

int AIPlayer::getBestProgressPiece()
{
    int bestPiece = -1;
    int maxDistance = 0;

    for (int pieceNum = 0; pieceNum < 4; pieceNum++)
    {
        Piece* piece = getPiece(pieceNum);

        if (piece == nullptr ||
            piece->getStatus() == IN_HOME ||
            piece->getStatus() == IN_FINISH)
        {
            continue;
        }

        int distance = piece->getDistanceMoved();

        if (distance > maxDistance)
        {
            maxDistance = distance;
            bestPiece = pieceNum;
        }
    }

    return bestPiece;
}

////////////////////////////////////// DESTRUCTOR //////////////////////////////////////////

AIPlayer::~AIPlayer()
{
    /// nothing to do here!
}