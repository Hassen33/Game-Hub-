
// ============
// Hangman Game
// ============
/*
 * Description:
 * This program implements the famous Hangman game in C.
 * The player must guess a word by entering letters one by one.
 * Each word is associated with a hint, and the player can select
 * a word by entering a number. The program manages the remaining attempts
 * and displays the partially revealed word after each guess.
 *
 * Main features:
 * - Select a word from a predefined list based on an integer.
 * - Display the letters found and hide those that have not been guessed yet.
 * - Decrease the number of available attempts for each incorrect guess.
 * - Win if the word is fully guessed or lose if the attempts are exhausted.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "hangmanGame.h"

#define MAX_WORDS 10

typedef struct
{
    int id;
    char word[20];
} Word;

// Function prototypes
void initializeWords(Word words[]);
void afficherMot(char mot[], int lettresTrouvees[]);
void jeuPendu(char mot[]);

// Function to encapsulate the Hangman game
void playHangman()
{
    Word words[MAX_WORDS];
    initializeWords(words);

    printf("\n--- Welcome to the Hangman Game! ---\n");
    printf("Choose a number to select a word:\n");

    for (int i = 0; i < MAX_WORDS; i++)
    {
        // Placeholder for word choices
        printf("%d. Word %d\n", i + 1, i + 1);
    }

    int choice;
    printf("Enter your choice (1 to %d): ", MAX_WORDS);
    scanf("%d", &choice);

    if (choice < 1 || choice > MAX_WORDS)
    {
        printf("Invalid choice. Exiting the game.\n");
        return;
    }
    // Placeholder
    printf("\nThe word to guess is: %s\n", words[choice - 1].word);
    jeuPendu(words[choice - 1].word);
}

// Function to initialize the words
void initializeWords(Word words[])
{
    strcpy(words[0].word, "PROGRAMMATION");
    strcpy(words[1].word, "ORDINATEUR");
    strcpy(words[2].word, "CLAVIER");
    strcpy(words[3].word, "ECRAN");
    strcpy(words[4].word, "SOURIS");
    strcpy(words[5].word, "INTERNET");
    strcpy(words[6].word, "LOGICIEL");
    strcpy(words[7].word, "JEU");
    strcpy(words[8].word, "MEMOIRE");
    strcpy(words[9].word, "FICHIER");

    for (int i = 0; i < MAX_WORDS; i++)
    {
        words[i].id = i + 1;
    }
}

// Function to display the word with guessed letters
void afficherMot(char mot[], int lettresTrouvees[])
{
    for (int i = 0; i < strlen(mot); i++)
    {
        if (lettresTrouvees[i])
            printf("%c ", mot[i]);
        else
            printf("_ ");
    }
    printf("\n");
}

// Core Hangman game logic
void jeuPendu(char mot[])
{
    int lettresTrouvees[strlen(mot)];
    memset(lettresTrouvees, 0, sizeof(lettresTrouvees));
    int essaisRestants = 6;

    while (essaisRestants > 0)
    {
        printf("\nWord to guess: ");
        afficherMot(mot, lettresTrouvees);
        printf("Remaining attempts: %d\n", essaisRestants);

        printf("Enter a letter: ");
        char lettre;
        scanf(" %c", &lettre);
        lettre = toupper(lettre);

        int trouve = 0;
        for (int i = 0; i < strlen(mot); i++)
        {
            if (mot[i] == lettre)
            {
                lettresTrouvees[i] = 1;
                trouve = 1;
            }
        }

        if (!trouve)
        {
            essaisRestants--;
            printf("Incorrect letter!\n");
        }

        // Check if the word is fully guessed
        int gagne = 1;
        for (int i = 0; i < strlen(mot); i++)
        {
            if (!lettresTrouvees[i])
            {
                gagne = 0;
                break;
            }
        }

        if (gagne)
        {
            printf("\nCongratulations! You guessed the word: %s\n", mot);
            return;
        }
    }

    printf("\nYou lost! The word was: %s\n", mot);
}
