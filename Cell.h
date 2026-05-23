#pragma once

#include <iostream>

using namespace std;

class Cell
{
private:
    static int cellCount;

    int cellID;
    int xPosition;
    int yPosition;
    bool isOccupied;
    int occupiedByPlayerID;
    bool isSafeZone;
    bool isHomeZone;

public:
    Cell(int x, int y);

    static void resetCellCount();
    static int getCellCount();

    int getCellID() const;
    int getXPosition() const;
    int getYPosition() const;
    bool getIsOccupied() const;
    int getOccupiedByPlayerID() const;
    bool getIsSafeZone() const;
    bool getIsHomeZone() const;

    void setOccupied(bool occupied, int playerID = -1);
    void setPlayerID(int playerID);
    void setSafeZone(bool safe);
    void setHomeZone(bool home);
    void setPosition(int x, int y);

    void displayCellInfo() const;
    void clearCell();

    ~Cell();
};