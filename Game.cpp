#include "Game.h"

////////////////////////////////////// CONSTRUCTOR //////////////////////////////////////////

Game::Game()
{
    gameBoard = nullptr;
    currentPlayerIndex = 0;
    numPlayers = 0;
    gameRunning = false;
    winnersCount = 0;

    for (int i = 0; i < 4; i++)
    {
        players[i] = nullptr;
    }
}

////////////////////////////////////// GAME SETUP //////////////////////////////////////////

void Game::setupGame()
{
    cout << "\nSetting up game..." << endl;

    gameBoard = new Board();
    cout << "Board created with 52 cells + home paths!" << endl;

    for (int player = 0; player < 4; player++)
    {
        if (players[player] != nullptr)
        {
            for (int piece = 0; piece < 4; piece++)
            {
                Piece* p = gameBoard->getPiece(player, piece);
                if (p != nullptr)
                {
                    players[player]->setPiece(piece, p);
                    cout << "Assigned Piece " << piece << " to "
                        << players[player]->getPlayerName() << endl;
                }
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (players[i] != nullptr)
        {
            AIPlayer* aiPlayer = dynamic_cast<AIPlayer*>(players[i]);
            if (aiPlayer != nullptr)
            {
                aiPlayer->setGameBoard(gameBoard);
            }
        }
    }

    cout << "Setup complete!\n" << endl;
}

void Game::addHumanPlayer(int playerNum, MyStr name)
{
    if (playerNum < 0 || playerNum >= 4)
    {
        cout << "Invalid player number!" << endl;
        return;
    }

    if (players[playerNum] != nullptr)
        delete players[playerNum];

    players[playerNum] = new HumanPlayer(playerNum, name);
    numPlayers++;
    cout << "Added Human Player " << playerNum << ": " << name << endl;
}

void Game::addAIPlayer(int playerNum, MyStr name, int difficulty)
{
    if (playerNum < 0 || playerNum >= 4)
    {
        cout << "Invalid player number!" << endl;
        return;
    }

    if (players[playerNum] != nullptr)
        delete players[playerNum];

    players[playerNum] = new AIPlayer(playerNum, name, difficulty);
    numPlayers++;
    cout << "Added AI Player " << playerNum << " : " << name << " (Level " << difficulty << ")" << endl;
}

void Game::startGame()
{
    cout << "\n========================================" << endl;
    cout << "***    LUDO GAME STARTING NOW!    ***" << endl;
    cout << "========================================\n" << endl;

    setupGame();
    gameRunning = true;
    winnersCount = 0;

    displayGameRules();

    cout << "\nGame initialized! Ready to play!\n" << endl;
}

////////////////////////////////////// MAIN GAME LOOP //////////////////////////////////////////

void Game::playGame()
{
    if (!gameRunning)
    {
        cout << "Game not started! Call startGame() first!" << endl;
        return;
    }

    cout << "\n========================================" << endl;
    cout << "***    GAMEPLAY BEGINS!           ***" << endl;
    cout << "========================================\n" << endl;

    // Main game loop - continue until someone wins
    while (gameRunning)
    {
        playTurn();
        checkAndAnnounceWinner();
    }

    cout << "\n========================================" << endl;
    cout << "***    GAME FINISHED!            ***" << endl;
    cout << "========================================\n" << endl;
}

////////////////////////////////////// MEMBERS FUNCTIONS //////////////////////////////////////////

void Game::playTurn()
{
    Player* currentPlayer = getCurrentPlayer();
    if (currentPlayer == nullptr)
    {
        cout << "ERROR : No current player!" << endl;
        return;
    }

    cout << "\n========== " << currentPlayer->getPlayerName() << "'s TURN ==========" << endl;
    currentPlayer->displayPlayerInfo();

    bool canRollAgain = true;
    int rollCount = 0;

    while (canRollAgain && rollCount < 3)
    {
        rollCount++;

        cout << "\n--- Roll #" << rollCount << " ---" << endl;

        int diceValue = currentPlayer->rollDice();

        cout << currentPlayer->getPlayerName() << " rolled : " << diceValue << endl;

        int pieceNum = currentPlayer->choosePiece();

        if (pieceNum < 0 || pieceNum >= 4)
        {
            cout << "Invalid piece selection! Skipping move." << endl;
            canRollAgain = false;
            break;
        }

        cout << "\nMoving Piece " << pieceNum << " with dice value " << diceValue << "..." << endl;
        executeMove(currentPlayer, diceValue, pieceNum);

        if (diceValue == 6)
        {
            cout << "\n*** Got a 6! Rolling again! ***" << endl;
            canRollAgain = true;
        }
        else
        {
            cout << "\nNo 6. Your turn ends." << endl;
            canRollAgain = false;
        }
    }

    cout << "\n" << currentPlayer->getPlayerName() << "'s turn finished!" << endl;

    nextPlayer();
}

void Game::executeMove(Player* player, int diceValue, int pieceNum)
{
    if (player == nullptr || gameBoard == nullptr)
    {
        cout << "ERROR : Invalid player or board!" << endl;
        return;
    }

    Piece* piece = player->getPiece(pieceNum);
    if (piece == nullptr)
    {
        cout << "ERROR : Piece " << pieceNum << " not found!" << endl;
        return;
    }

    cout << "\nBefore move :" << endl;
    piece->displayPieceInfo();

    bool moveSuccess = gameBoard->movePiece(piece, diceValue);

    if (moveSuccess)
    {
        cout << "\n✓ Piece moved successfully!" << endl;

        cout << "After move :" << endl;
        piece->displayPieceInfo();

        checkAndApplyCapture(piece, player->getPlayerID());

        if (piece->getStatus() == IN_FINISH)
        {
            cout << "\n*** PIECE FINISHED! ***" << endl;
            player->addFinishedPiece();
        }
    }
    else
    {
        cout << "\n✗ Move FAILED! Piece could not move." << endl;
        cout << "Reasons : Overshoot, invalid status, or piece not on board" << endl;
    }
}

void Game::checkAndApplyCapture(Piece* piece, int playerID)
{
    if (piece == nullptr || gameBoard == nullptr)
        return;

    int cellID = piece->getCurrentCellID();

    if (cellID < 0 || cellID >= 52)
        return;

    Cell* cell = gameBoard->getMainCell(cellID);
    if (cell == nullptr)
        return;

    int occupiedByPlayer = cell->getOccupiedByPlayerID();

    if (occupiedByPlayer != -1 && occupiedByPlayer != playerID)
    {
        cout << "\n*** CAPTURE! ***" << endl;

        Player* opponentPlayer = players[occupiedByPlayer];
        if (opponentPlayer != nullptr)
        {
            cout << opponentPlayer->getPlayerName() << "'s piece captured!" << endl;
        }

        gameBoard->captureOpponentPieces(piece, cellID);
    }
}

void Game::checkThreeSixes(Dice* playerDice)
{
    if (playerDice == nullptr)
        return;

    if (playerDice->getConsecutiveSixes() >= 3)
    {
        Player* currentPlayer = getCurrentPlayer();
        if (currentPlayer != nullptr)
        {
            cout << "\n*** THREE 6S IN A ROW! TURN CANCELLED! ***" << endl;
        }
    }
}

void Game::checkAndAnnounceWinner()
{
    for (int i = 0; i < 4; i++)
    {
        if (players[i] != nullptr)
        {
            if (players[i]->hasPlayerWon())
            {
                winnersCount++;

                if (winnersCount >= 1)
                {
                    cout << "\n========================================" << endl;
                    cout << "*** " << players[i]->getPlayerName() << " WINS! ***" << endl;
                    cout << "========================================\n" << endl;

                    gameRunning = false;
                    return;
                }
            }
        }
    }
}

void Game::nextPlayer()
{
    currentPlayerIndex++;
    if (currentPlayerIndex >= 4)
        currentPlayerIndex = 0;
}

Player* Game::getCurrentPlayer()
{
    return players[currentPlayerIndex];
}

bool Game::isGameFinished()
{
    return !gameRunning;
}

void Game::displayGameRules()
{
    cout << "\n========== LUDO GAME RULES ==========" << endl;
    cout << "1. Roll dice (1-6) to move pieces" << endl;
    cout << "2. Need 6 to enter board from home" << endl;
    cout << "3. Roll 6 again to take another turn" << endl;
    cout << "4. THREE consecutive 6s = turn cancelled" << endl;
    cout << "5. Main board : 52 cells" << endl;
    cout << "6. Home path : 8 cells per player" << endl;
    cout << "7. Total distance to finish : 60" << endl;
    cout << "8. Safe zones : 0, 9, 18, 27, 36, 45" << endl;
    cout << "9. Cannot capture on safe zones" << endl;
    cout << "10. Captured piece goes back to home" << endl;
    cout << "11. First player to finish all 4 pieces WINS!" << endl;
    cout << "====================================\n" << endl;
}

void Game::displayAllPlayersInfo()
{
    cout << "\n========== PLAYERS INFO ==========" << endl;
    for (int i = 0; i < 4; i++)
    {
        if (players[i] != nullptr)
        {
            players[i]->displayPlayerInfo();
        }
    }
    cout << "================================\n" << endl;
}

void Game::displayGameStatus()
{
    cout << "\n========== GAME STATUS ==========" << endl;
    cout << "Current Player: " << getCurrentPlayer()->getPlayerName() << endl;
    displayAllPlayersInfo();
}


////////////////////////////////////// DESTRUCTOR //////////////////////////////////////////

Game::~Game()
{
    if (gameBoard != nullptr)
    {
        delete gameBoard;
        gameBoard = nullptr;
    }

    for (int i = 0; i < 4; i++)
    {
        if (players[i] != nullptr)
        {
            delete players[i];
            players[i] = nullptr;
        }
    }

    cout << "Game destroyed!" << endl;
}