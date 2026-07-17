#include "Dice.h"

////////////////////////////////////// Constructor //////////////////////////////////////////

Dice::Dice()
{
	diceValue = 0;
	consecutiveSixes = 0;
	canRollAgain = false;
	srand((unsigned)time(0));
}

////////////////////////////////////// ROLL FUNCTION //////////////////////////////////////////

int Dice::roll()
{
	diceValue = (rand() % 6) + 1;

	if (diceValue == 6)
	{
		consecutiveSixes++;
		canRollAgain = true;
	}
	else
	{
		canRollAgain = false;
	}

	return diceValue;
}

////////////////////////////////////// GETTERS //////////////////////////////////////////

int Dice::getDiceValue() const
{
	return diceValue;
}
int Dice::getConsecutiveSixes() const
{
	return consecutiveSixes;
}
bool Dice::canPlayerRollAgain() const
{
	return canRollAgain;
}

////////////////////////////////////// MEMBER FUNCTIONS //////////////////////////////////////////

void Dice::resetConsecutiveSixes()
{
	consecutiveSixes = 0;
	canRollAgain = false;
}
void Dice::printDiceValue() const
{
	cout << "Dice rolled : " << diceValue << endl;
	if (canRollAgain && consecutiveSixes != 3)
	{
		cout << "You got a 6! Roll Again !\n";
	}
	else if (consecutiveSixes == 3)
	{
		cout << "Your turn is cancelled due to 3 consecutive 6.\n";
	}
}

////////////////////////////////////// DESTRUCTOR //////////////////////////////////////////

Dice::~Dice()
{
	// Nothing to delete bro ! 
}