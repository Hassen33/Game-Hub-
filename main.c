#include <stdio.h>
#include <stdlib.h>
#include "hangmanGame/hangmanGame.h"
#include "snakeGame/snakeGame.h"
#include "xoGame/xoGame.h"

// ========
// Game Hub
// ========
/**
 * @file main.c
 * @brief A simple Game Hub program that allows users to play multiple classic games.
 *
 * This program presents a menu to the user, giving them the option to play one of three games:
 * - Hangman
 * - Snake
 * - XO (Tic-Tac-Toe)
 *
 * The program will continue to display the menu and accept user input until the user selects the option to exit.
 * The option for playing the last game is a placeholder and will be added in a future update.
 *
 * @note This file is the main entry point for the Game Hub. The corresponding game logic for each game
 *       is implemented in their respective modules (`hangmanGame`, `snakeGame`, `xoGame`).
 *
 * @note New features are currently in development, stay tuned for upcoming updates!
 */


    int main()
{
    int choice;

    do
    {
        printf("\n==================================\n");
        printf("\n             Game Hub             \n");
        printf("\n==================================\n");
        printf("\n");
        printf("1. Play Hangman\n");
        printf("2. Play Snake\n");
        printf("3. Play XO \n");
        printf("4. Play last game (Coming Soon!)\n");
        printf("5. Exit\n");
        printf("\n");
        printf("===========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Call Hangman game
            playHangman();
            break;
        case 2:
            // Call Snake game
            snakeGame();
            break;
        case 3:
            // Call Xo Game
            playXo();
            break;
        case 4:
            printf("\nTic-Tac-Toe will be added soon!\n");
            break;
        case 5:
            printf("\nExiting the game hub. Goodbye!\n");
            break;
        default:
            printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
