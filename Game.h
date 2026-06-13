#pragma once

#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include <iostream>
#include "MyStr.h"

using namespace std;

class Game
{
private:

    Board* gameBoard;

    Player* players[4];

    int currentPlayerIndex;

    int numPlayers;

    bool gameRunning;

    int winnersCount;

public:

    ////////////////////////////////////// CONSTRUCTOR & DESTRUCTOR //////////////////////////////////////////

    Game();

    ~Game();

    ////////////////////////////////////// GAME SETUP //////////////////////////////////////////

    void setupGame();

    void addHumanPlayer(int playerNum, MyStr name);

    void addAIPlayer(int playerNum, MyStr name, int difficulty);

    void startGame();

    ////////////////////////////////////// GAME FLOW //////////////////////////////////////////

    void playGame();

    void playTurn();

    void nextPlayer();

    ////////////////////////////////////// TURN LOGIC //////////////////////////////////////////

    void executeMove(Player* player, int diceValue, int pieceNum);

    void checkAndApplyCapture(Piece* piece, int playerID);

    void checkThreeSixes(Dice* playerDice);

    void checkAndAnnounceWinner();

    ////////////////////////////////////// DISPLAY FUNCTIONS //////////////////////////////////////////

    void displayGameRules();

    void displayAllPlayersInfo();

    void displayGameStatus();

    ////////////////////////////////////// HELPER FUNCTIONS //////////////////////////////////////////

    Player* getCurrentPlayer();

    bool isGameFinished();
};