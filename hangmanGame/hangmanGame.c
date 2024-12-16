#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "hangmanGame.h"

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

#define MAX_WORDS 10

typedef struct
{
    int id;
    char word[20];
} Word;

// Fonction pour afficher le mot avec les lettres trouvées
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

// Fonction pour initialiser les mots
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

// Fonction pour initialiser les indices
void wordsIndice(Word wordsIndice[])
{
    strcpy(wordsIndice[0].word, "Langage de programmation");
    strcpy(wordsIndice[1].word, "Machine utilisée pour coder");
    strcpy(wordsIndice[2].word, "Périphérique pour taper");
    strcpy(wordsIndice[3].word, "Affiche les informations");
    strcpy(wordsIndice[4].word, "Périphérique pour pointer");
    strcpy(wordsIndice[5].word, "Réseau mondial");
    strcpy(wordsIndice[6].word, "Programme informatique");
    strcpy(wordsIndice[7].word, "Activité ludique");
    strcpy(wordsIndice[8].word, "Stocke des données");
    strcpy(wordsIndice[9].word, "Document informatique");

    for (int i = 0; i < MAX_WORDS; i++)
    {
        wordsIndice[i].id = i + 1;
    }
}

// Fonction pour jouer au jeu du pendu
void jeuPendu(char mot[])
{
    int lettresTrouvees[strlen(mot)];
    memset(lettresTrouvees, 0, sizeof(lettresTrouvees));
    int essaisRestants = 6;

    printf("Bienvenue dans le jeu du pendu !\n");

    while (essaisRestants > 0)
    {
        printf("\nMot à deviner : ");
        afficherMot(mot, lettresTrouvees);
        printf("Essais restants : %d\n", essaisRestants);

        printf("Entrez une lettre : ");
        char lettre;
        scanf(" %c", &lettre);
        lettre = toupper(lettre); // Convertir en majuscule

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
            printf("Lettre incorrecte !\n");
        }

        // Vérifier si le mot est entièrement trouvé
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
            printf("\nFélicitations ! Vous avez deviné le mot : %s\n", mot);
            return;
        }
    }

    printf("\nVous avez perdu ! Le mot était : %s\n", mot);
}

// Fonction pour démarrer le jeu et demander un mot à l'utilisateur
void playHangman()
{
    Word words[MAX_WORDS];
    Word indices[MAX_WORDS];
    initializeWords(words);
    wordsIndice(indices);

    printf("Choisissez un entier [1..9] pour sélectionner un mot :\n");

    for (int i = 0; i < MAX_WORDS; i++)
    {
        printf("%d : %s\n", i + 1, indices[i].word);
    }

    int choice;
    printf("Entrez votre choix (1 à %d) : ", MAX_WORDS);
    scanf("%d", &choice);

    if (choice < 1 || choice > MAX_WORDS)
    {
        printf("Choix invalide. Fin du programme.\n");
        return;
    }

    // Jouer avec le mot sélectionné
    printf("L'indice est : %s\n", indices[choice - 1].word); // Afficher l'indice
    jeuPendu(words[choice - 1].word);                        // Lancer le jeu avec le mot sélectionné
}

