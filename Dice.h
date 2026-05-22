#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Dice
{
private:
    int diceValue;
    int consecutiveSixes;
    bool canRollAgain;

public:
    Dice();

    int roll();

    int getDiceValue() const;
    int getConsecutiveSixes() const;

    bool canPlayerRollAgain() const;
    void resetConsecutiveSixes();
    void printDiceValue() const;

    ~Dice();
};