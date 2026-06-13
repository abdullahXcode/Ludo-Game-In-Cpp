#include "Cell.h"

int Cell::cellCount = 0;

////////////////////////////////////// Constructor //////////////////////////////////////////
Cell::Cell() : Cell(0, 0)
{
    // Calling the main constructor with (0, 0)
}
Cell::Cell(int x, int y)
{
    cellID = cellCount++;
    xPosition = x;
    yPosition = y;
    isOccupied = false;
    occupiedByPlayerID = -1;
    isSafeZone = false;
    isHomeZone = false;
}

////////////////////////////////////// GETTERS //////////////////////////////////////////

int Cell::getCellID() const
{
    return cellID;
}
int Cell::getXPosition() const
{
    return xPosition;
}
int Cell::getYPosition() const
{
    return yPosition;
}
bool Cell::getIsOccupied() const
{
    return isOccupied;
}
int Cell::getOccupiedByPlayerID() const
{
    return occupiedByPlayerID;
}
bool Cell::getIsSafeZone() const
{
    return isSafeZone;
}
bool Cell::getIsHomeZone() const
{
    return isHomeZone;
}

////////////////////////////////////// SETTERS //////////////////////////////////////////

void Cell::setOccupied(bool occupied, int playerID)
{
    isOccupied = occupied;
    if (occupied)
    {
        occupiedByPlayerID = playerID;
    }
    else
    {
        occupiedByPlayerID = -1;
    }
}
void Cell::setPlayerID(int playerID)
{
    occupiedByPlayerID = playerID;
    if (playerID != -1)
    {
        isOccupied = true;
    }
}
void Cell::setSafeZone(bool safe)
{
    isSafeZone = safe;
}
void Cell::setHomeZone(bool home)
{
    isHomeZone = home;
}
void Cell::setPosition(int x, int y)
{
    xPosition = x;
    yPosition = y;
}

////////////////////////////////////// MEMBER FUNCTIONS //////////////////////////////////////////

void Cell::displayCellInfo() const
{
    cout << "Cell ID  : " << cellID << " | Position : (" << xPosition << ", " << yPosition << ")";

    if (isOccupied)
        cout << " | Occupied by Player : " << occupiedByPlayerID;
    else
        cout << " | Empty";

    if (isSafeZone)
        cout << " | [ SAFE ZONE ]";

    if (isHomeZone)
        cout << " | [ HOME ZONE ]";

    cout << endl;
}
void Cell::clearCell()
{
    isOccupied = false;
    occupiedByPlayerID = -1;
}

////////////////////////////////////// STATIC FUNCTIONS //////////////////////////////////////////

void Cell::resetCellCount()
{
    cellCount = 0;
}
int Cell::getCellCount()
{
    return cellCount;
}

////////////////////////////////////// DESTRUCTOR //////////////////////////////////////////

Cell::~Cell()
{
    // Nothing to delete bro ! 
}