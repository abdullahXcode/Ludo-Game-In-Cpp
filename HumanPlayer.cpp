#include "HumanPlayer.h"

////////////////////////////////////// DESTRUCTOR //////////////////////////////////////////

HumanPlayer::HumanPlayer(int id, MyStr name) : Player(id, name)
{
}

////////////////////////////////////// OVERRIDE FUCNTIONS //////////////////////////////////////////

void HumanPlayer::takeTurn()
{
    cout << "\n========================================" << endl;
    cout << "*** " << playerName << " (" << pieceColor << ") - YOUR TURN! ***" << endl;
    cout << "========================================" << endl;

    displayPlayerInfo();

    cout << "\nYour Pieces : " << endl;
    displayPieces();

    cout << "\nPress ENTER to roll dice..." << endl;
    cin.ignore();

    int diceValue = rollDice();

    cout << "\nDice rolled : " << diceValue << endl;
    int pieceChoice = choosePiece();

    Piece* chosenPiece = getPiece(pieceChoice);

    if (chosenPiece != nullptr)
    {
        cout << "\nYou choose Piece " << pieceChoice << endl;
        chosenPiece->displayPieceInfo();
        cout << "Ready to move with value : " << diceValue << endl;
    }
}

int HumanPlayer::choosePiece()
{
    int pieceNum;
    bool validChoice = false;

    while (!validChoice)
    {
        cout << "\nWhich piece do you want to move? (0/1/2/3): ";
        cin >> pieceNum;

        if (pieceNum < 0 || pieceNum >= 4)
        {
            cout << "Invalid! Please enter 0, 1, 2, or 3." << endl;
            continue;
        }

        Piece* piece = getPiece(pieceNum);
        if (piece == nullptr)
        {
            cout << "Piece " << pieceNum << " is not assigned!" << endl;
            continue;
        }

        validChoice = true;
    }

    return pieceNum;
}

////////////////////////////////////// DESTRUCTOR //////////////////////////////////////////

HumanPlayer::~HumanPlayer()
{
}