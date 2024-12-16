#include "snakeGame.h"
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// ==========
// Snake Game
// ==========
/*
 * Description:
 * This program implements the famous Snake game in C.
 * The player controls a snake that moves within a grid,
 * eating fruits. Each fruit consumed increases the length
 * of the snake and the player's score. The game ends if the snake
 * collides with the walls or with its own body.
 *
 * Main features:
 * - Dynamic generation of fruits in the grid at random locations.
 * - Control the snake's movement using the Arrows Up down left and Right keys.
 * - Real-time display of the grid, snake, and fruits.
 * - Score calculation based on the number of fruits eaten.
 * - Collision management to detect failures, especially when the snake hits a wall or its body.
 * - The snake's length increases with each fruit consumed.
 * - Display of borders, the snake ('O' for the head, 'o' for the body), and the fruits ('*').
 *
 * Instructions:
 * - Press the W, A, S, or D keys to move the snake in the grid.
 * - Press X at any time to quit the game.
 * - The score is displayed at the end of each game.
 */

#define HEIGHT 20
#define WIDTH 40

// Coordinates for the snake's tail
int snakeTailX[100], snakeTailY[100];
// Length of the snake's tail
int snakeTailLen;
// Game state variables
int gameover, key, score;
// Coordinates for snake's head and fruit
int x, y, fruitx, fruity;

void setup();
void draw();
void input();
void logic();

void setup()
{
    gameover = 0;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitx = rand() % WIDTH;
    fruity = rand() % HEIGHT;

    while (fruitx == 0)
        fruitx = rand() % WIDTH;
    while (fruity == 0)
        fruity = rand() % HEIGHT;

    score = 0;
    snakeTailLen = 0;
}

void draw()
{
    system("cls");
    for (int i = 0; i < WIDTH + 2; i++)
        printf("-");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j <= WIDTH; j++)
        {
            if (j == 0 || j == WIDTH)
                printf("#");
            else if (i == y && j == x)
                printf("O");
            else if (i == fruity && j == fruitx)
                printf("*");
            else
            {
                int printTail = 0;
                for (int k = 0; k < snakeTailLen; k++)
                {
                    if (snakeTailX[k] == j && snakeTailY[k] == i)
                    {
                        printf("o");
                        printTail = 1;
                    }
                }
                if (!printTail)
                    printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("-");
    printf("\n");

    printf("Score: %d\n", score);
    printf("Press arrow Up Down Left & Right for movement.\n");
    printf("Press X to quit the game.\n");
}

void input()
{
    if (kbhit())
    {
        // Reset the key to prevent holding the same key
        key = 0;

        // First get the "0x00" or "0xE0" byte for special keys
        switch (getch())
        {
        case 0x00:
        case 0xE0:
            // Get the actual arrow key code
            switch (getch())
            {
            // Up arrow
            case 72:
                // Prevent going back in the opposite direction
                if (key != 4)
                    key = 3;
                break;
                // Down arrow
            case 80:
                if (key != 3)
                    key = 4;
                break;
                // Left arrow
            case 75:
                if (key != 2)
                    key = 1;
                break;
                // Right arrow
            case 77:
                if (key != 1)
                    key = 2;
                break;
            }
            break;
            // Exit the game
        case 27:
            gameover = 1;
            break;
        }
    }
}

void logic()
{
    int prevX = snakeTailX[0], prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = x;
    snakeTailY[0] = y;

    for (int i = 1; i < snakeTailLen; i++)
    {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (key)
    {
    case 1:
        x--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y--;
        break;
    case 4:
        y++;
        break;
    }

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameover = 1;

    for (int i = 0; i < snakeTailLen; i++)
    {
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            gameover = 1;
    }

    if (x == fruitx && y == fruity)
    {
        fruitx = rand() % WIDTH;
        fruity = rand() % HEIGHT;

        while (fruitx == 0)
            fruitx = rand() % WIDTH;
        while (fruity == 0)
            fruity = rand() % HEIGHT;

        score += 10;
        snakeTailLen++;
    }
}

void snakeGame()
{
    setup();
    while (!gameover)
    {
        draw();
        input();
        logic();
        // Delay to control game speed
        Sleep(33);
    }

    printf("\nGame Over! Final Score: %d\n", score);
}
