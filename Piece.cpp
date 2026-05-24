#include "Piece.h"

int Piece::pieceCount = 0;

////////////////////////////////////// CONSTRUCTOR //////////////////////////////////////////

Piece::Piece(int owner)
{
    pieceID = pieceCount++;
    playerID = owner;
    currentCellID = -1;
    status = IN_HOME;
    distanceMoved = 0;
}

////////////////////////////////////// STATIC FUNCTIONS //////////////////////////////////////////

void Piece::resetPieceCount()
{
    pieceCount = 0;
}
int Piece::getPieceCount()
{
    return pieceCount;
}

////////////////////////////////////// GETTERS //////////////////////////////////////////

int Piece::getPieceID() const
{
    return pieceID;
}
int Piece::getPlayerID() const
{
    return playerID;
}
int Piece::getCurrentCellID() const
{
    return currentCellID;
}
PieceStatus Piece::getStatus() const
{
    return status;
}
int Piece::getDistanceMoved() const
{
    return distanceMoved;
}

////////////////////////////////////// SETTERS //////////////////////////////////////////

void Piece::setCurrentCellID(int cellID)
{
    currentCellID = cellID;
}
void Piece::setStatus(PieceStatus newStatus)
{
    status = newStatus;
}
void Piece::setDistanceMoved(int distance)
{
    distanceMoved = distance;
}

////////////////////////////////////// MEMBER FUNCTIONS //////////////////////////////////////////

void Piece::movePiece(int steps)
{
    if (status == IN_HOME)
    {
        cout << "Piece " << pieceID << " is still in home. Cannot move yet." << endl;
        return;
    }
    if (status == IN_FINISH)
    {
        cout << "Piece " << pieceID << " has already finished!" << endl;
        return;
    }

    int newDistance = distanceMoved + steps;
    if (newDistance > 52)
    {
        cout << "Piece " << pieceID << " would overshoot! Game rules will decide." << endl;
        return;
    }

    distanceMoved = newDistance;
 
    if (distanceMoved <= 52)
    {
        currentCellID = distanceMoved - 1;
    }
    if (distanceMoved == 52)
    {
        status = IN_FINISH;
        currentCellID = -1;
        cout << "Piece " << pieceID << " has reached position 52! Waiting for game validation..." << endl;
    }
    else
    {
        cout << "Piece " << pieceID << " moved " << steps << " steps. Distance: " << distanceMoved << endl;
    }
}
void Piece::capture()
{
    if (status == IN_SAFE)
    {
        cout << "Piece " << pieceID << " is in safe zone and cannot be captured!" << endl;
        return;
    }

    if (status == IN_HOME)
    {
        cout << "Piece " << pieceID << " is already in home!" << endl;
        return;
    }

    status = IN_HOME;
    currentCellID = -1;
    distanceMoved = 0;
    cout << "Piece " << pieceID << " has been captured and sent back to home!" << endl;
}
bool Piece::canMove() const
{
    return (status != IN_HOME && status != IN_FINISH);
}
bool Piece::isAtFinish() const
{
    return (distanceMoved == 52);
}
void Piece::displayPieceInfo() const
{
    cout << "Piece ID: " << pieceID << " | Player: " << playerID << " | ";

    switch (status)
    {
    case IN_HOME:
        cout << "Status: IN HOME";
        break;
    case IN_PLAY:
        cout << "Status: IN PLAY | Cell: " << currentCellID;
        break;
    case IN_SAFE:
        cout << "Status: IN SAFE | Cell: " << currentCellID;
        break;
    case IN_FINISH:
        cout << "Status: IN FINISH";
        break;
    }

    cout << " | Distance: " << distanceMoved << endl;
}

////////////////////////////////////// DESTRUCTOR //////////////////////////////////////////

Piece::~Piece()
{
    // Nothing to detele bro !
}