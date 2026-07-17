#include "raylib.h"
#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Piece.h"
#include "MyStr.h"
#include <iostream>
#include <vector>
using namespace std;

const int CELL_SIZE = 40;
const int BOARD_SIZE = 15;
const int WINDOW_WIDTH = CELL_SIZE * BOARD_SIZE + 500;
const int WINDOW_HEIGHT = CELL_SIZE * BOARD_SIZE;
const int PANEL_START_X = CELL_SIZE * BOARD_SIZE;

enum GameState { STATE_MAIN_MENU, STATE_PLAYER_SETUP, STATE_GAME_PLAYING, STATE_GAME_OVER };

// Turn flow is now staged across these phases so the player can actually
// see what happened, instead of everything resolving instantly:
//   TURN_WAITING_ROLL      -> waiting for a roll (human button / AI timer)
//   TURN_ROLLED_DELAY      -> dice value is shown, ~1s pause before the token moves
//   TURN_WAITING_SELECTION -> human must click which token to move
//   TURN_MOVED_DELAY       -> token has moved, ~1s pause so it's visible
//   TURN_SHIFT_DELAY       -> ~1s pause before the turn actually passes on
enum TurnState { TURN_WAITING_ROLL, TURN_ROLLED_DELAY, TURN_WAITING_SELECTION, TURN_MOVED_DELAY, TURN_SHIFT_DELAY };

struct PlayerSetup {
    MyStr name;
    int type;
    PlayerSetup() : name("Player"), type(0) {}
};

struct Button {
    Rectangle rect;
    MyStr text;
    bool hovered;
    Button(float x, float y, float w, float h, const char* t) : rect({ x, y, w, h }), text(t), hovered(false) {}
    bool IsClicked() {
        Vector2 mouse = GetMousePosition();
        hovered = CheckCollisionPointRec(mouse, rect);
        return hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    }
    void Draw(Color bgColor, Color textColor) {
        Color drawColor = hovered ? Color{ 200, 200, 200, 255 } : bgColor;
        DrawRectangleRec(rect, drawColor);
        DrawRectangleLines((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, BLACK);
        DrawText(text.c_str(), (int)rect.x + 10, (int)rect.y + 10, 16, textColor);
    }
};

// GLOBAL VARIABLES
GameState currentState = STATE_MAIN_MENU;
TurnState turnState = TURN_WAITING_ROLL;
int selectedPlayerCount = 0;
vector<PlayerSetup> playersSetup;
int currentSetupIndex = 0;
Game* gameInstance = nullptr;

// GAMEPLAY
int lastDiceValue = 0;
int consecutiveSixes = 0;
vector<int> movablePieces;   // indices (0-3) of the current player's pieces that can move with lastDiceValue
MyStr gameMessage = "";
int messageTimer = 0;
MyStr winnerName = "";
float aiDelayTimer = 0.0f;
const float AI_DELAY = 1.0f;

// Pacing: pause for ~1 second after a dice roll, and ~1 second after a
// move resolves, so the game doesn't feel instant/jumpy.
enum DelayPhase { DELAY_NONE, DELAY_AFTER_ROLL, DELAY_AFTER_MOVE };
DelayPhase delayPhase = DELAY_NONE;
float delayTimer = 0.0f;
const float ACTION_DELAY = 1.0f;

int pendingPieceChoice = -3;   // -3 = none pending, -2 = needs human click, -1 = no move/skip, >=0 = piece index
bool pendingAdvanceTurn = false;
bool pendingRollAgain = false;

void DrawCell(int row, int col, Color color) {
    DrawRectangle(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE, color);
    DrawRectangleLines(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
}

void DrawBoard() {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            DrawCell(row, col, WHITE);
        }
    }

    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 6; c++) {
            DrawCell(r, c, RED);
        }
    }
    for (int r = 1; r < 5; r++) {
        for (int c = 1; c < 5; c++) {
            DrawCell(r, c, WHITE);
        }
    }

    for (int r = 0; r < 6; r++) {
        for (int c = 9; c < 15; c++) {
            DrawCell(r, c, GREEN);
        }
    }
    for (int r = 1; r < 5; r++) {
        for (int c = 10; c < 14; c++) {
            DrawCell(r, c, WHITE);
        }
    }

    for (int r = 9; r < 15; r++) {
        for (int c = 0; c < 6; c++) {
            DrawCell(r, c, BLUE);
        }
    }
    for (int r = 10; r < 14; r++) {
        for (int c = 1; c < 5; c++) {
            DrawCell(r, c, WHITE);
        }
    }

    for (int r = 9; r < 15; r++) {
        for (int c = 9; c < 15; c++) {
            DrawCell(r, c, YELLOW);
        }
    }
    for (int r = 10; r < 14; r++) {
        for (int c = 10; c < 14; c++) {
            DrawCell(r, c, WHITE);
        }
    }

    for (int r = 0; r < 15; r++) {
        DrawCell(r, 6, WHITE);
        DrawCell(r, 7, WHITE);
        DrawCell(r, 8, WHITE);
    }
    for (int c = 0; c < 15; c++) {
        DrawCell(6, c, WHITE);
        DrawCell(7, c, WHITE);
        DrawCell(8, c, WHITE);
    }

    for (int c = 1; c <= 6; c++) DrawCell(7, c, RED);
    for (int r = 1; r <= 6; r++) DrawCell(r, 7, GREEN);
    for (int c = 8; c <= 13; c++) DrawCell(7, c, YELLOW);
    for (int r = 8; r <= 13; r++) DrawCell(r, 7, BLUE);

    DrawCell(6, 1, RED);
    DrawCell(1, 8, GREEN);
    DrawCell(8, 13, YELLOW);
    DrawCell(13, 6, BLUE);

    int safe[8][2] = { {2,6}, {6,12}, {8,2}, {12,8}, {1,8}, {6,1}, {8,13}, {13,6} };
    for (int i = 0; i < 8; i++) {
        int r = safe[i][0];
        int c = safe[i][1];
        DrawText("*", c * CELL_SIZE + CELL_SIZE / 3, r * CELL_SIZE + CELL_SIZE / 6, 24, BLACK);
    }

    int x = 6 * CELL_SIZE;
    int y = 6 * CELL_SIZE;
    int s = 3 * CELL_SIZE;

    DrawRectangle(x, y, s, s, WHITE);
    DrawTriangle({ (float)x, (float)y }, { (float)(x + s / 2), (float)(y + s / 2) }, { (float)(x + s), (float)y }, GREEN);
    DrawTriangle({ (float)(x + s), (float)y }, { (float)(x + s / 2), (float)(y + s / 2) }, { (float)(x + s), (float)(y + s) }, YELLOW);
    DrawTriangle({ (float)x, (float)(y + s) }, { (float)(x + s), (float)(y + s) }, { (float)(x + s / 2), (float)(y + s / 2) }, BLUE);
    DrawTriangle({ (float)x, (float)y }, { (float)x, (float)(y + s) }, { (float)(x + s / 2), (float)(y + s / 2) }, RED);

    DrawLine(x, y, x + s / 2, y + s / 2, BLACK);
    DrawLine(x + s, y, x + s / 2, y + s / 2, BLACK);
    DrawLine(x, y + s, x + s / 2, y + s / 2, BLACK);
    DrawLine(x + s, y + s, x + s / 2, y + s / 2, BLACK);
    DrawRectangleLines(x, y, s, s, BLACK);

    int radius = CELL_SIZE / 3;
    DrawCircle(2 * CELL_SIZE, 2 * CELL_SIZE, radius, RED);
    DrawCircle(4 * CELL_SIZE, 2 * CELL_SIZE, radius, RED);
    DrawCircle(2 * CELL_SIZE, 4 * CELL_SIZE, radius, RED);
    DrawCircle(4 * CELL_SIZE, 4 * CELL_SIZE, radius, RED);
    DrawCircle(11 * CELL_SIZE, 2 * CELL_SIZE, radius, GREEN);
    DrawCircle(13 * CELL_SIZE, 2 * CELL_SIZE, radius, GREEN);
    DrawCircle(11 * CELL_SIZE, 4 * CELL_SIZE, radius, GREEN);
    DrawCircle(13 * CELL_SIZE, 4 * CELL_SIZE, radius, GREEN);
    DrawCircle(2 * CELL_SIZE, 11 * CELL_SIZE, radius, BLUE);
    DrawCircle(4 * CELL_SIZE, 11 * CELL_SIZE, radius, BLUE);
    DrawCircle(2 * CELL_SIZE, 13 * CELL_SIZE, radius, BLUE);
    DrawCircle(4 * CELL_SIZE, 13 * CELL_SIZE, radius, BLUE);
    DrawCircle(11 * CELL_SIZE, 11 * CELL_SIZE, radius, YELLOW);
    DrawCircle(13 * CELL_SIZE, 11 * CELL_SIZE, radius, YELLOW);
    DrawCircle(11 * CELL_SIZE, 13 * CELL_SIZE, radius, YELLOW);
    DrawCircle(13 * CELL_SIZE, 13 * CELL_SIZE, radius, YELLOW);
}

// =====================================================
// FIXED 52-CELL MAIN LOOP PATH
// (verified: 52 distinct cells, no duplicates, each player's
//  start offset lands exactly on their own start cell)
// =====================================================
int boardPath[52][2] = {
    {6,1},{6,2},{6,3},{6,4},{6,5},
    {5,6},{4,6},{3,6},{2,6},{1,6},{0,6},
    {0,7},
    {0,8},{1,8},{2,8},{3,8},{4,8},{5,8},
    {6,9},{6,10},{6,11},{6,12},{6,13},{6,14},
    {7,14},
    {8,14},{8,13},{8,12},{8,11},{8,10},{8,9},
    {9,8},{10,8},{11,8},{12,8},{13,8},{14,8},
    {14,7},
    {14,6},{13,6},{12,6},{11,6},{10,6},{9,6},
    {8,5},{8,4},{8,3},{8,2},{8,1},{8,0},
    {7,0},
    {6,0}
};

// COLOR OFFSETS: where each player enters the main track (verified against boardPath above)
int colorOffset[4] = { 0, 13, 26, 39 };  // RED, GREEN, YELLOW, BLUE

Vector2 DistanceToCoords(int playerID, int distance, int pieceIndex = 0) {
    int row, col;

    if (distance == 0) {
        if (playerID == 0) { row = (pieceIndex < 2) ? 2 : 4; col = (pieceIndex % 2) ? 4 : 2; }
        else if (playerID == 1) { row = (pieceIndex < 2) ? 2 : 4; col = (pieceIndex % 2) ? 13 : 11; }
        else if (playerID == 2) { row = (pieceIndex < 2) ? 13 : 11; col = (pieceIndex % 2) ? 13 : 11; }
        else { row = (pieceIndex < 2) ? 13 : 11; col = (pieceIndex % 2) ? 4 : 2; }
    }
    else if (distance >= 1 && distance <= 52) {
        int globalIdx = (colorOffset[playerID] + distance - 1) % 52;
        row = boardPath[globalIdx][0];
        col = boardPath[globalIdx][1];
    }
    else if (distance >= 53 && distance <= 59) {
        int homeStep = distance - 53;
        if (playerID == 0) { row = 7; col = 1 + homeStep; }
        else if (playerID == 1) { row = 1 + homeStep; col = 7; }
        else if (playerID == 2) { row = 7; col = 13 - homeStep; }
        else { row = 13 - homeStep; col = 7; }
    }
    else {
        row = 7;
        col = 7;
    }

    return { (float)(col * CELL_SIZE + CELL_SIZE / 2), (float)(row * CELL_SIZE + CELL_SIZE / 2) };
}

void DrawToken(Vector2 pos, Color color, bool highlighted) {
    DrawCircle((int)pos.x, (int)pos.y, CELL_SIZE / 3, color);
    DrawCircleLines((int)pos.x, (int)pos.y, CELL_SIZE / 3, BLACK);
    if (highlighted)
        DrawCircleLines((int)pos.x, (int)pos.y, CELL_SIZE / 3 + 5, YELLOW);
}

void DrawGamePieces(Game* game) {
    if (!game) return;
    Color pieceColors[] = { MAROON, DARKGREEN, GOLD, DARKBLUE };
    Player* currentPlayer = game->players[game->currentPlayerIndex];

    for (int p = 0; p < 4; p++) {
        Player* player = game->players[p];
        if (!player) continue;
        for (int i = 0; i < 4; i++) {
            Piece* piece = player->pieces[i];
            if (!piece) continue;

            Vector2 pos = DistanceToCoords(p, piece->getDistanceMoved(), i);

            bool isHighlighted = false;
            if (turnState == TURN_WAITING_SELECTION && player == currentPlayer) {
                for (int idx : movablePieces) {
                    if (idx == i) { isHighlighted = true; break; }
                }
            }

            DrawToken(pos, pieceColors[p], isHighlighted);
        }
    }
}

void DrawMainMenu() {
    DrawText("CLASSIC LUDO GAME", WINDOW_WIDTH / 2 - 150, 50, 40, DARKBLUE);
    Button btn2(WINDOW_WIDTH / 2 - 75, 150, 150, 50, "2 PLAYERS");
    Button btn3(WINDOW_WIDTH / 2 - 75, 220, 150, 50, "3 PLAYERS");
    Button btn4(WINDOW_WIDTH / 2 - 75, 290, 150, 50, "4 PLAYERS");
    btn2.Draw(SKYBLUE, BLACK);
    btn3.Draw(SKYBLUE, BLACK);
    btn4.Draw(SKYBLUE, BLACK);
    if (btn2.IsClicked()) { selectedPlayerCount = 2; currentState = STATE_PLAYER_SETUP; playersSetup.clear(); for (int i = 0; i < 2; i++) playersSetup.push_back(PlayerSetup()); currentSetupIndex = 0; }
    if (btn3.IsClicked()) { selectedPlayerCount = 3; currentState = STATE_PLAYER_SETUP; playersSetup.clear(); for (int i = 0; i < 3; i++) playersSetup.push_back(PlayerSetup()); currentSetupIndex = 0; }
    if (btn4.IsClicked()) { selectedPlayerCount = 4; currentState = STATE_PLAYER_SETUP; playersSetup.clear(); for (int i = 0; i < 4; i++) playersSetup.push_back(PlayerSetup()); currentSetupIndex = 0; }
}

void DrawPlayerSetup() {
    DrawText("PLAYER SETUP", WINDOW_WIDTH / 2 - 100, 30, 30, DARKBLUE);
    PlayerSetup& currentPlayer = playersSetup[currentSetupIndex];
    char playerLabel[50];
    sprintf_s(playerLabel, "Player %d of %d", currentSetupIndex + 1, selectedPlayerCount);
    DrawText(playerLabel, 50, 100, 20, BLACK);
    DrawText("Name:", 50, 150, 16, BLACK);
    DrawRectangle(150, 145, 200, 30, WHITE);
    DrawRectangleLines(150, 145, 200, 30, BLACK);
    DrawText(currentPlayer.name.c_str(), 160, 155, 16, BLACK);
    DrawText("Type:", 50, 200, 16, BLACK);
    Button btnHuman(150, 190, 100, 30, "HUMAN");
    Button btnAIEasy(270, 190, 100, 30, "AI EASY");
    Button btnAIMed(390, 190, 120, 30, "AI MEDIUM");
    Button btnAIHard(530, 190, 100, 30, "AI HARD");
    btnHuman.Draw((currentPlayer.type == 0) ? LIME : LIGHTGRAY, BLACK);
    btnAIEasy.Draw((currentPlayer.type == 1) ? LIME : LIGHTGRAY, BLACK);
    btnAIMed.Draw((currentPlayer.type == 2) ? LIME : LIGHTGRAY, BLACK);
    btnAIHard.Draw((currentPlayer.type == 3) ? LIME : LIGHTGRAY, BLACK);
    if (btnHuman.IsClicked()) currentPlayer.type = 0;
    if (btnAIEasy.IsClicked()) currentPlayer.type = 1;
    if (btnAIMed.IsClicked()) currentPlayer.type = 2;
    if (btnAIHard.IsClicked()) currentPlayer.type = 3;
    Button btnNext(200, 280, 100, 40, "NEXT");
    Button btnPrev(50, 280, 100, 40, "PREV");
    Button btnStart(350, 280, 150, 40, "START GAME");
    btnPrev.Draw(LIGHTGRAY, BLACK);
    btnNext.Draw(SKYBLUE, BLACK);
    btnStart.Draw(LIME, BLACK);
    if (btnPrev.IsClicked() && currentSetupIndex > 0) currentSetupIndex--;
    if (btnNext.IsClicked() && currentSetupIndex < selectedPlayerCount - 1) currentSetupIndex++;
    if (btnStart.IsClicked() && currentSetupIndex == selectedPlayerCount - 1) {
        gameInstance = new Game();
        for (int i = 0; i < selectedPlayerCount; i++) {
            if (playersSetup[i].type == 0) {
                gameInstance->addHumanPlayer(i, playersSetup[i].name.c_str());
            }
            else {
                gameInstance->addAIPlayer(i, playersSetup[i].name.c_str(), playersSetup[i].type);
            }
        }
        gameInstance->setupGame();
        gameInstance->gameRunning = true;
        currentState = STATE_GAME_PLAYING;
        turnState = TURN_WAITING_ROLL;
        lastDiceValue = 0;
        consecutiveSixes = 0;
        movablePieces.clear();
        aiDelayTimer = 0.0f;
    }
    int key = GetCharPressed();
    if (key > 0 && currentPlayer.name.size() < 15) {
        currentPlayer.name = currentPlayer.name + (char)key;
    }
    if (IsKeyPressed(KEY_BACKSPACE) && currentPlayer.name.size() > 0) {
        currentPlayer.name.erase(currentPlayer.name.size() - 1, 1);
    }
}

// =====================================================
// CORE TURN LOGIC
// =====================================================

// Game::nextPlayer() in the backend doesn't skip empty (nullptr) player
// slots, which breaks 2 and 3 player games. Fixing it here in main.cpp
// instead of touching Game.cpp.
void AdvanceToNextPlayer(Game* game) {
    for (int i = 0; i < 4; i++) {
        game->currentPlayerIndex = (game->currentPlayerIndex + 1) % 4;
        if (game->players[game->currentPlayerIndex] != nullptr)
            break;
    }
}

// =====================================================
// CAPTURE LOGIC (computed entirely from verified board
// positions in this file — does not depend on backend
// safe-zone/occupancy state)
// =====================================================

bool IsSafeCell(int row, int col) {
    static const int safeCells[8][2] = {
        {2,6},{6,12},{8,2},{12,8},
        {1,8},{6,1},{8,13},{13,6}
    };
    for (int i = 0; i < 8; i++)
        if (safeCells[i][0] == row && safeCells[i][1] == col)
            return true;
    return false;
}

void CheckAndCapture(Game* game, Player* moverPlayer, Piece* moverPiece) {
    int moverDist = moverPiece->getDistanceMoved();
    if (moverDist < 1 || moverDist > 52) return; // home / home-stretch / finish are never capturable

    Vector2 moverPos = DistanceToCoords(moverPlayer->playerID, moverDist, 0);
    int moverRow = (int)(moverPos.y / CELL_SIZE);
    int moverCol = (int)(moverPos.x / CELL_SIZE);

    if (IsSafeCell(moverRow, moverCol)) return; // safe cell — no captures here

    for (int p = 0; p < 4; p++) {
        Player* otherPlayer = game->players[p];
        if (!otherPlayer || otherPlayer == moverPlayer) continue;

        for (int i = 0; i < 4; i++) {
            Piece* otherPiece = otherPlayer->pieces[i];
            if (!otherPiece) continue;

            int otherDist = otherPiece->getDistanceMoved();
            if (otherDist < 1 || otherDist > 52) continue;

            Vector2 otherPos = DistanceToCoords(p, otherDist, i);
            int otherRow = (int)(otherPos.y / CELL_SIZE);
            int otherCol = (int)(otherPos.x / CELL_SIZE);

            if (otherRow == moverRow && otherCol == moverCol) {
                otherPiece->capture();
                gameMessage = "Captured an opponent's token!";
                messageTimer = 90;
                cout << "Player " << moverPlayer->playerID << " captured player "
                    << p << "'s piece " << i << "!" << endl;
            }
        }
    }
}

void ExecuteMove(Game* game, Player* currentPlayer, int pieceIndex) {
    Piece* piece = currentPlayer->pieces[pieceIndex];
    if (!piece) return;

    cout << "Player " << currentPlayer->playerID << " moves piece " << pieceIndex
        << " by " << lastDiceValue << endl;

    game->gameBoard->movePiece(piece, lastDiceValue);

    CheckAndCapture(game, currentPlayer, piece);

    if (piece->getStatus() == IN_FINISH) {
        currentPlayer->addFinishedPiece();
        gameMessage = "A token reached home!";
        messageTimer = 90;
    }

    if (currentPlayer->hasPlayerWon()) {
        winnerName = currentPlayer->playerName;
        currentState = STATE_GAME_OVER;
        return;
    }

    // Don't switch turns / allow the next roll immediately — pause first
    // so the move is clearly visible before anything else happens.
    pendingRollAgain = (lastDiceValue == 6 && consecutiveSixes < 3);
    delayPhase = DELAY_AFTER_MOVE;
    delayTimer = 0.0f;
}

// Called once the post-move pause finishes.
void ResolveAfterMove(Game* game) {
    delayPhase = DELAY_NONE;

    if (pendingRollAgain) {
        gameMessage = "Rolled a 6! Roll again.";
        messageTimer = 90;
    }
    else {
        AdvanceToNextPlayer(game);
        consecutiveSixes = 0;
        gameMessage = "Next player's turn.";
        messageTimer = 60;
    }

    lastDiceValue = 0;
    movablePieces.clear();
    turnState = TURN_WAITING_ROLL;
}

// Called once the post-roll pause finishes — actually acts on the dice result.
void ResolveAfterRoll(Game* game) {
    delayPhase = DELAY_NONE;

    Player* currentPlayer = game->players[game->currentPlayerIndex];
    if (!currentPlayer) return;

    if (pendingPieceChoice == -1) {
        // Forfeited turn (3 sixes) or no valid move available.
        if (pendingAdvanceTurn) {
            AdvanceToNextPlayer(game);
            consecutiveSixes = 0;
        }
        lastDiceValue = 0;
        turnState = TURN_WAITING_ROLL;
    }
    else if (pendingPieceChoice == -2) {
        gameMessage = "Click one of your highlighted tokens!";
        messageTimer = 150;
        turnState = TURN_WAITING_SELECTION;
    }
    else {
        ExecuteMove(game, currentPlayer, pendingPieceChoice);
    }

    pendingPieceChoice = -3;
}

void PerformRoll(Game* game) {
    Player* currentPlayer = game->players[game->currentPlayerIndex];
    if (!currentPlayer) return;

    lastDiceValue = currentPlayer->rollDice();

    if (lastDiceValue == 6)
        consecutiveSixes++;
    else
        consecutiveSixes = 0;

    // Three sixes in a row: forfeit the rest of this turn.
    // Any moves made on the first two sixes already happened and stand.
    if (consecutiveSixes == 3) {
        gameMessage = "Three 6s in a row! Turn forfeited.";
        messageTimer = 90;
        pendingPieceChoice = -1;
        pendingAdvanceTurn = true;
        delayPhase = DELAY_AFTER_ROLL;
        delayTimer = 0.0f;
        return;
    }

    movablePieces.clear();
    for (int i = 0; i < 4; i++) {
        Piece* piece = currentPlayer->pieces[i];
        if (piece != nullptr && game->gameBoard->canPieceMove(piece, lastDiceValue))
            movablePieces.push_back(i);
    }

    if (movablePieces.empty()) {
        gameMessage = "No valid move!";
        messageTimer = 90;

        pendingPieceChoice = -1;
        // If it was a 6 with no usable move, the player still keeps their
        // extra roll — don't advance the turn in that case.
        pendingAdvanceTurn = (lastDiceValue != 6);

        delayPhase = DELAY_AFTER_ROLL;
        delayTimer = 0.0f;
        return;
    }

    bool isAI = (dynamic_cast<HumanPlayer*>(currentPlayer) == nullptr);

    if (isAI) {
        AIPlayer* aiCurrent = dynamic_cast<AIPlayer*>(currentPlayer);
        int chosen = aiCurrent->choosePieceWithDice(lastDiceValue);

        bool valid = false;
        for (int idx : movablePieces) if (idx == chosen) valid = true;
        if (!valid) chosen = movablePieces[0];

        pendingPieceChoice = chosen;
    }
    else if (movablePieces.size() == 1) {
        pendingPieceChoice = movablePieces[0];
    }
    else {
        pendingPieceChoice = -2;
    }

    delayPhase = DELAY_AFTER_ROLL;
    delayTimer = 0.0f;
}

void HandlePieceSelection(Game* game) {
    if (turnState != TURN_WAITING_SELECTION) return;
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;

    Player* currentPlayer = game->players[game->currentPlayerIndex];
    if (!currentPlayer) return;

    Vector2 mouse = GetMousePosition();

    for (int idx : movablePieces) {
        Piece* piece = currentPlayer->pieces[idx];
        if (!piece) continue;

        Vector2 pos = DistanceToCoords(currentPlayer->playerID, piece->getDistanceMoved(), idx);

        if (CheckCollisionPointCircle(mouse, pos, CELL_SIZE / 3.0f + 5)) {
            ExecuteMove(game, currentPlayer, idx);
            break;
        }
    }
}

void DrawRightPanel(Game* game) {
    DrawRectangle(PANEL_START_X, 0, 500, WINDOW_HEIGHT, LIGHTGRAY);
    DrawLine(PANEL_START_X, 0, PANEL_START_X, WINDOW_HEIGHT, BLACK);
    DrawText("LUDO GAME", PANEL_START_X + 20, 20, 20, DARKBLUE);

    if (!game) return;
    Player* currentPlayer = game->players[game->currentPlayerIndex];
    if (!currentPlayer) return;

    DrawText("CURRENT TURN:", PANEL_START_X + 20, 70, 14, BLACK);
    DrawText(currentPlayer->playerName.c_str(), PANEL_START_X + 20, 95, 18, BLACK);

    char diceText[50];
    sprintf_s(diceText, "Dice: %d", lastDiceValue);
    DrawText(diceText, PANEL_START_X + 20, 130, 16, BLACK);

    bool isAI = (dynamic_cast<HumanPlayer*>(currentPlayer) == nullptr);

    if (!isAI) {
        if (turnState == TURN_WAITING_ROLL && delayPhase == DELAY_NONE) {
            Button btnRoll(PANEL_START_X + 20, 180, 150, 50, "ROLL DICE");
            btnRoll.Draw(LIME, BLACK);
            if (btnRoll.IsClicked()) {
                PerformRoll(game);
            }
        }
        else if (turnState == TURN_WAITING_SELECTION) {
            DrawText("Pick a token on the board", PANEL_START_X + 20, 190, 14, DARKBLUE);
        }
        else {
            DrawText("...", PANEL_START_X + 20, 190, 14, DARKBLUE);
        }
    }
    else {
        DrawText("AI is playing...", PANEL_START_X + 20, 190, 16, MAROON);
    }

    if (messageTimer > 0) {
        DrawText(gameMessage.c_str(), PANEL_START_X + 20, 260, 14, RED);
        messageTimer--;
    }
}

void DrawGameOver() {
    DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Color{ 0, 0, 0, 150 });
    DrawText("GAME OVER!", WINDOW_WIDTH / 2 - 120, 150, 50, GOLD);
    char winText[100];
    sprintf_s(winText, "Winner: %s", winnerName.c_str());
    DrawText(winText, WINDOW_WIDTH / 2 - 100, 250, 30, LIME);
    Button btnMenu(WINDOW_WIDTH / 2 - 75, 350, 150, 50, "MAIN MENU");
    btnMenu.Draw(SKYBLUE, BLACK);
    if (btnMenu.IsClicked()) {
        if (gameInstance) delete gameInstance;
        gameInstance = nullptr;
        currentState = STATE_MAIN_MENU;
        turnState = TURN_WAITING_ROLL;
    }
}

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Ludo - Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentState == STATE_MAIN_MENU) {
            DrawMainMenu();
        }
        else if (currentState == STATE_PLAYER_SETUP) {
            DrawPlayerSetup();
        }
        else if (currentState == STATE_GAME_PLAYING) {
            DrawBoard();

            if (gameInstance) {
                Player* currentPlayer = gameInstance->players[gameInstance->currentPlayerIndex];

                if (!currentPlayer) {
                    currentState = STATE_GAME_OVER;
                    winnerName = "Player";
                }
                else if (currentPlayer->hasPlayerWon()) {
                    currentState = STATE_GAME_OVER;
                    winnerName = currentPlayer->playerName;
                }
                else {
                    bool isAI = (dynamic_cast<HumanPlayer*>(currentPlayer) == nullptr);

                    // Tick the post-roll / post-move pause first.
                    if (delayPhase != DELAY_NONE) {
                        delayTimer += GetFrameTime();
                        if (delayTimer >= ACTION_DELAY) {
                            if (delayPhase == DELAY_AFTER_ROLL)
                                ResolveAfterRoll(gameInstance);
                            else if (delayPhase == DELAY_AFTER_MOVE)
                                ResolveAfterMove(gameInstance);
                        }
                    }
                    else if (isAI && turnState == TURN_WAITING_ROLL) {
                        aiDelayTimer += GetFrameTime();
                        if (aiDelayTimer >= AI_DELAY) {
                            aiDelayTimer = 0.0f;
                            PerformRoll(gameInstance);
                        }
                    }

                    if (delayPhase == DELAY_NONE)
                        HandlePieceSelection(gameInstance);
                }

                DrawGamePieces(gameInstance);
            }

            DrawRightPanel(gameInstance);
        }
        else if (currentState == STATE_GAME_OVER) {
            DrawGameOver();
        }

        EndDrawing();
    }

    if (gameInstance) delete gameInstance;
    CloseWindow();
    return 0;
}