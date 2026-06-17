#include "raylib.h"
#include "Game.h"
#include <iostream>

using namespace std;

const int CELL_SIZE = 40;
const int BOARD_SIZE = 15;
const int WINDOW_WIDTH = CELL_SIZE * BOARD_SIZE + 500;
const int WINDOW_HEIGHT = CELL_SIZE * BOARD_SIZE;
const int BOARD_START_X = 0;
const int BOARD_START_Y = 0;
const int PANEL_START_X = CELL_SIZE * BOARD_SIZE;

Vector2 DistanceToCoords(int playerID, int distance, int pieceIndex = 0)
{
    int row, col;

    if (distance == 0)
    {
        if (playerID == 0)
        {
            row = (pieceIndex < 2) ? 1 : 4;
            col = (pieceIndex % 2) ? 4 : 1;
        }
        else if (playerID == 1)
        {
            row = (pieceIndex < 2) ? 1 : 4;
            col = (pieceIndex % 2) ? 13 : 10;
        }
        else if (playerID == 2)
        {
            row = (pieceIndex < 2) ? 13 : 10;
            col = (pieceIndex % 2) ? 13 : 10;
        }
        else
        {
            row = (pieceIndex < 2) ? 13 : 10;
            col = (pieceIndex % 2) ? 4 : 1;
        }
    }
    else if (distance >= 1 && distance <= 52)
    {
        if (playerID == 0)
        {
            if (distance <= 6)
            {
                row = 6;
                col = 1 + distance;
            }
            else if (distance <= 14)
            {
                row = 6 - (distance - 6);
                col = 7;
            }
            else if (distance <= 20)
            {
                row = 0;
                col = 7 + (distance - 14);
            }
            else if (distance <= 28)
            {
                row = (distance - 20);
                col = 13;
            }
            else if (distance <= 34)
            {
                row = 8;
                col = 13 - (distance - 28);
            }
            else if (distance <= 42)
            {
                row = 8 + (distance - 34);
                col = 7;
            }
            else if (distance <= 48)
            {
                row = 14;
                col = 7 - (distance - 42);
            }
            else
            {
                row = 14 - (distance - 48);
                col = 1;
            }
        }
        else if (playerID == 1)
        {
            if (distance <= 6)
            {
                row = 1 - distance;
                col = 8;
            }
            else if (distance <= 14)
            {
                row = -7;
                col = 8 + (distance - 6);
            }
        }
        else if (playerID == 2)
        {
        }
        else
        {
        }
    }
    else if (distance >= 53 && distance <= 59)
    {
        int pathPos = distance - 52;

        if (playerID == 0)
        {
            row = 1 + pathPos;
            col = 7;
        }
        else if (playerID == 1)
        {
            row = 7;
            col = 8 + pathPos;
        }
        else if (playerID == 2)
        {
            row = 8 + pathPos;
            col = 7;
        }
        else
        {
            row = 7;
            col = 6 - pathPos;
        }
    }
    else
    {
        row = 7;
        col = 7;
    }

    return {
        (float)(col * CELL_SIZE + CELL_SIZE / 2),
        (float)(row * CELL_SIZE + CELL_SIZE / 2)
    };
}

void DrawCell(int row, int col, Color color)
{
    DrawRectangle(
        col * CELL_SIZE,
        row * CELL_SIZE,
        CELL_SIZE,
        CELL_SIZE,
        color
    );

    DrawRectangleLines(
        col * CELL_SIZE,
        row * CELL_SIZE,
        CELL_SIZE,
        CELL_SIZE,
        BLACK
    );
}

void DrawToken(Vector2 pos, Color color)
{
    DrawCircle(pos.x, pos.y, CELL_SIZE / 3, color);
    DrawCircleLines(pos.x, pos.y, CELL_SIZE / 3, BLACK);
}

void DrawBoard()
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            DrawCell(row, col, WHITE);
        }
    }

    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 6; col++)
        {
            DrawCell(row, col, Fade(RED, 0.35f));
        }
    }

    for (int row = 0; row < 6; row++)
    {
        for (int col = 9; col < 15; col++)
        {
            DrawCell(row, col, Fade(GREEN, 0.35f));
        }
    }

    for (int row = 9; row < 15; row++)
    {
        for (int col = 0; col < 6; col++)
        {
            DrawCell(row, col, Fade(BLUE, 0.35f));
        }
    }

    for (int row = 9; row < 15; row++)
    {
        for (int col = 9; col < 15; col++)
        {
            DrawCell(row, col, Fade(YELLOW, 0.35f));
        }
    }

    for (int row = 1; row <= 6; row++)
    {
        DrawCell(row, 7, RED);
    }

    for (int col = 8; col <= 13; col++)
    {
        DrawCell(7, col, GREEN);
    }

    for (int row = 8; row <= 13; row++)
    {
        DrawCell(row, 7, YELLOW);
    }

    for (int col = 1; col <= 6; col++)
    {
        DrawCell(7, col, BLUE);
    }

    DrawCell(6, 1, RED);
    DrawCell(1, 8, GREEN);
    DrawCell(8, 13, YELLOW);
    DrawCell(13, 6, BLUE);

    DrawCell(2, 6, LIGHTGRAY);
    DrawCell(6, 12, LIGHTGRAY);
    DrawCell(8, 2, LIGHTGRAY);
    DrawCell(12, 8, LIGHTGRAY);

    DrawCircle(
        6 * CELL_SIZE + CELL_SIZE / 2,
        2 * CELL_SIZE + CELL_SIZE / 2,
        8,
        BLACK
    );

    DrawCircle(
        12 * CELL_SIZE + CELL_SIZE / 2,
        6 * CELL_SIZE + CELL_SIZE / 2,
        8,
        BLACK
    );

    DrawCircle(
        2 * CELL_SIZE + CELL_SIZE / 2,
        8 * CELL_SIZE + CELL_SIZE / 2,
        8,
        BLACK
    );

    DrawCircle(
        8 * CELL_SIZE + CELL_SIZE / 2,
        12 * CELL_SIZE + CELL_SIZE / 2,
        8,
        BLACK
    );

    DrawTriangle(
        { 7 * CELL_SIZE, 7 * CELL_SIZE },
        { 8 * CELL_SIZE, 8 * CELL_SIZE },
        { 7 * CELL_SIZE, 8 * CELL_SIZE },
        BLUE
    );

    DrawTriangle(
        { 7 * CELL_SIZE, 7 * CELL_SIZE },
        { 8 * CELL_SIZE, 7 * CELL_SIZE },
        { 8 * CELL_SIZE, 8 * CELL_SIZE },
        GREEN
    );

    DrawTriangle(
        { 7 * CELL_SIZE, 7 * CELL_SIZE },
        { 8 * CELL_SIZE, 7 * CELL_SIZE },
        { 7 * CELL_SIZE, 8 * CELL_SIZE },
        RED
    );

    DrawTriangle(
        { 8 * CELL_SIZE, 8 * CELL_SIZE },
        { 8 * CELL_SIZE, 7 * CELL_SIZE },
        { 7 * CELL_SIZE, 8 * CELL_SIZE },
        YELLOW
    );
}

void DrawGamePieces(Game* game)
{
    Color pieceColors[] = { MAROON, DARKGREEN, GOLD, DARKBLUE };

    for (int p = 0; p < 4; p++)
    {
        Player* player = game->players[p];

        if (!player)
        {
            continue;
        }

        for (int i = 0; i < 4; i++)
        {
            Piece* piece = player->pieces[i];

            if (!piece)
            {
                continue;
            }

            Vector2 pos = DistanceToCoords(
                p,
                piece->getDistanceMoved(),
                i
            );

            DrawToken(pos, pieceColors[p]);
        }
    }
}

void DrawRightPanel()
{
    DrawRectangle(
        PANEL_START_X,
        BOARD_START_Y,
        500,
        WINDOW_HEIGHT,
        LIGHTGRAY
    );

    DrawLine(
        PANEL_START_X,
        BOARD_START_Y,
        PANEL_START_X,
        WINDOW_HEIGHT,
        BLACK
    );

    DrawText(
        "LUDO GAME",
        PANEL_START_X + 20,
        20,
        20,
        BLACK
    );
}

int main()
{
    InitWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "Ludo - Raylib"
    );

    SetTargetFPS(60);

    Game game;

    game.addHumanPlayer(0, "Ali");
    game.addAIPlayer(1, "Bot Easy", 1);
    game.addAIPlayer(2, "Bot Medium", 2);
    game.addAIPlayer(3, "Bot Hard", 3);

    game.setupGame();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawBoard();
        DrawGamePieces(&game);
        DrawRightPanel();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}