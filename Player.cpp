#include "Player.h"

////////////////////////////////////// CONSTRUCTOR //////////////////////////////////////////

Player::Player(int id, MyStr name)
{
    playerID = id;
    playerName = name;
    finishedPieces = 0;
    isCurrentTurn = false;

    if (playerID == 0)
        pieceColor = "RED";
    else if (playerID == 1)
        pieceColor = "GREEN";
    else if (playerID == 2)
        pieceColor = "YELLOW";
    else if (playerID == 3)
        pieceColor = "BLUE";

    for (int i = 0; i < 4; i++)
    {
        pieces[i] = nullptr;
    }
}

////////////////////////////////////// GETTERS //////////////////////////////////////////

int Player::getPlayerID() const
{
    return playerID;
}
MyStr Player::getPlayerName() const
{
    return playerName;
}
MyStr Player::getPieceColor() const
{
    return pieceColor;
}
int Player::getFinishedPieces() const
{
    return finishedPieces;
}
bool Player::getIsCurrentTurn() const
{
    return isCurrentTurn;
}
Piece* Player::getPiece(int pieceNum)
{
    if (pieceNum < 0 || pieceNum >= 4)
    {
        cout << "Invalid piece number!" << endl;
        return nullptr;
    }

    return pieces[pieceNum];
}
int Player::getDiceValue() const
{
    return dice.getDiceValue();
}

////////////////////////////////////// SETTERS //////////////////////////////////////////

void Player::setPlayerName(MyStr name)
{
    playerName = name;
}
void Player::setPieceColor(MyStr color)
{
    pieceColor = color;
}
void Player::setFinishedPieces(int count)
{
    if (count < 0 || count > 4)
    {
        cout << "Invalid finished pieces count !\n";
        return;
    }
    finishedPieces = count;
}
void Player::setIsCurrentTurn(bool turn)
{
    isCurrentTurn = turn;
}
void Player::setPiece(int pieceNum, Piece* piece)
{
    if (pieceNum < 0 || pieceNum >= 4)
    {
        cout << "Invalid piece number !\n";
        return;
    }

    pieces[pieceNum] = piece;
}

////////////////////////////////////// MEMBER FUNCTIONS //////////////////////////////////////////

void Player::displayPlayerInfo()
{
    cout << "\n===== PLAYER INFO =====\n" ;
    cout << "Player ID : " << playerID << endl;
    cout << "Player Name : " << playerName << endl;
    cout << "Piece Color : " << pieceColor << endl;
    cout << "Finished Pieces : " << finishedPieces << "/4 \n";

    if (isCurrentTurn)
        cout << "Status : CURRENT TURN" << endl;
    else
        cout << "Status : WAITING" << endl;
}

void Player::displayPieces()
{
    cout << "\nPieces of " << playerName << " : " << endl;

    for (int i = 0; i < 4; i++)
    {
        if (pieces[i] != nullptr)
        {
            cout << "Piece " << i << " : ";
            pieces[i]->displayPieceInfo();
        }
        else
        {
            cout << "Piece " << i << " : Not assigned" << endl;
        }
    }
}

////////////////////////////////////// DICE ROLL //////////////////////////////////////////

int Player::rollDice()
{
    int diceValue = dice.roll();

    cout << playerName << " rolled : " << diceValue << endl;

    if (diceValue == 6)
    {
        cout << "Got a 6! Can roll again!" << endl;
    }

    return diceValue;
}

////////////////////////////////////// FUNCTIONS //////////////////////////////////////////

void Player::addFinishedPiece()
{
    finishedPieces++;
    cout << playerName << " finished a piece! Total finished : " << finishedPieces << "/4" << endl;
}

bool Player::hasPlayerWon()
{
    if (finishedPieces == 4)
    {
        cout << "\n*** " << playerName << " (" << pieceColor << ") WINS THE GAME! ***\n" << endl;
        return true;
    }
    return false;
}

////////////////////////////////////// DESTRUCTOR //////////////////////////////////////////

Player::~Player()
{
    // nope to dlte
}