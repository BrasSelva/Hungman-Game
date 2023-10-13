#include <stdio.h>
#include "Mot.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define Mot_H
#define MAX_TRIES 7// Nombre maximum d'essais

// D�clarez cette fonction au d�but de votre code pour la rendre accessible aux autres fonctions.
void Replay(void) {
    char choix;

    printf("Do you want to replay ? (Y/N) : ");
    fflush(stdin);
    scanf(" %c", &choix);

    if (choix == 'Y' || choix == 'y') {
        // Si le joueur veut rejouer, appelez la fonction Game pour d�marrer une nouvelle partie.
        Game();
    }
    else if (choix == 'N' || choix == 'n') {
        printf("Thank for playing ! Good bye.\n");
        //ExitApp(); // Vous pouvez �galement ajouter un appel � la fonction ExitApp pour quitter l'application ici.
    }
    else {
        // R�ponse non valide, redemandez.
        printf("Answer incorrect. Please answer by Y(yes) or N(no)\n");
        Replay(); // Appel r�cursif pour redemander la r�ponse.
    }
}

//Fonction d'affichage du pendu

//void afficherPendu(int tentatives) {
//    switch (tentatives) {
//    case 0:
//        printf("  +---+\n");
//        printf("  |   |\n");
//        printf("      |\n");
//        printf("      |\n");
//        printf("      |\n");
//        printf("      |\n");
//        break;
//    case 1:
//        printf("  +---+\n");
//        printf("  |   |\n");
//        printf("  O   |\n");
//        printf("      |\n");
//        printf("      |\n");
//        printf("      |\n");
//        break;
//    case 2:
//        printf("  +---+\n");
//        printf("  |   |\n");
//        printf("  O   |\n");
//        printf("  |   |\n");
//        printf("      |\n");
//        printf("      |\n");
//        break;
//    case 3:
//        printf("  +---+\n");
//        printf("  |   |\n");
//        printf("  O   |\n");
//        printf(" /|   |\n");
//        printf("      |\n");
//        printf("      |\n");
//        break;
//    case 4:
//        printf("  +---+\n");
//        printf("  |   |\n");
//        printf("  O   |\n");
//        printf(" /|\\  |\n");
//        printf("      |\n");
//        printf("      |\n");
//        break;
//    case 5:
//        printf("  +---+\n");
//        printf("  |   |\n");
//        printf("  O   |\n");
//        printf(" /|\\  |\n");
//        printf(" /    |\n");
//        printf("      |\n");
//        break;
//    case 6:
//        printf("  +---+\n");
//        printf("  |   |\n");
//        printf("  O   |\n");
//        printf(" /|\\  |\n");
//        printf(" / \\  |\n");
//        printf("      |\n");
//        break;
//    }
//}

// Liste de mots secrets
const char* motsSecrets[] = {
    "programmation",
    "informatique",
    "pendu",
    "developpeur",
    "ordinateur"
};
const int nombreDeMots = sizeof(motsSecrets) / sizeof(motsSecrets[0]);

// Fonction pour choisir un mot secret al�atoire
const char* choisirMotSecret(void) {
    srand(time(NULL));
    int indice = rand() % nombreDeMots;
    return motsSecrets[indice];
}

// Fonction pour afficher le mot partiel avec les lettres devin�es
void afficherMotPartiel(const char* motSecret, const char* lettresDevinees) {
    for (int i = 0; i < strlen(motSecret); i++) {
        if (strchr(lettresDevinees, motSecret[i]) != NULL) {
            printf("%c ", motSecret[i]);
        }
        else {
            printf("_ ");
        }
    }
    printf("\n");
}

// Fonction Start

void Startup(void) {
    printf(" \n Launche the game \n \n");

}

void Game(void) {
    const char* motSecret = choisirMotSecret();
    unsigned long int longueurMot = strlen(motSecret);
    char lettresDevinees[26]; // Tableau pour stocker les lettres devin�es
    int tries = 0;

    memset(lettresDevinees, 0, sizeof(lettresDevinees)); 
    // Initialiser le tableau de lettres devin�es

    printf("Welcome to the hungman game !\n");

    while (tries < MAX_TRIES) {
        printf("\nSecret word : ");
        afficherMotPartiel(motSecret, lettresDevinees);
        printf("Guessed letter: %s \n", lettresDevinees);
        printf("Try remaining : %d \n", MAX_TRIES - tries);
        printf("Tape 2 to quit \n");
        printf("Enter a letter : \n");

        //Affiche le pendu au fur et � mesure des essais

        //Affiche le pendu au fur et � mesure des essais

        if (tries > 0) {
            printf("Lost :\n");

            // Afficher le pendu à l'aide d'une boucle
            for (int i = 0; i < tries; i++) {
                if(i == 1){
                    printf("  +---+\n");
                }
                if (i == 2){
                    printf("  |   |\n");
                }
                if (i == 3){
                    printf("  O   |\n");
                }
                if (i == 4) {
                    printf(" /|\\  |\n");
                } else if (i >= 5) {
                    printf(" / \\  |\n");
                } else {
                    printf("      |\n");
                }
            }
        }
        // M�thode pour pouvoir quitter le jeu pendant le jeu

        int nb;
        scanf(" %d", &nb);
        if (nb == 2) {
            printf("You left the game.\n");
            //return 0; // Sortie du jeu
        }

        char lettre;
        scanf(" %c", &lettre);



        // V�rifier si la lettre a d�j� �t� devin�e
        if (strchr(lettresDevinees, lettre) != NULL) {
            printf("You've already guessed this letter. Try again.\n");
            continue;
        }

        // Ajouter la lettre aux lettres devin�es
        lettresDevinees[strlen(lettresDevinees)] = lettre;

        // V�rifier si la lettre est dans le mot secret
        if (strchr(motSecret, lettre) != NULL) {
            printf("Good letter!\n");
        }
        else {
            printf("The letter is not in the word. \n");
            tries++;
        }

        // V�rifier si le joueur a devin� le mot complet
        int motComplet = 1;
        for (int i = 0; i < longueurMot; i++) {
            if (strchr(lettresDevinees, motSecret[i]) == NULL) {
                motComplet = 0;
                break;
            }
        }

        if (motComplet) {
            printf("\n Congratulations, you've guessed the word: %s\n Thanks for playing the hangman's game! ", motSecret);
            break;
        }
    }

    // Si le nombre d'essai est � 0

    if (tries >= MAX_TRIES) {
        printf("\n You've exhausted all your attempts. The secret word was : %s\n", motSecret);
    }
    Replay(); //appelle � la fonction game
    //return 0;
}

// Fonction pour quitter le jeu
void ExitApp(void) {
    printf("See you seen. \n");
    Replay();
    exit(0);


}

// Fonction qui sert � guider le joueur

void MainMenu(void) {
    printf("-----Main Menu----- \n \n");
    printf("   [1] Start the game  \n");
    printf("          or \n");
    printf("   [2] Leave the game \n");
    printf("\n Choose an option : ");

    int MenuChoice = 2;

    enum MenuButtons {
        Start = 1,
        Quit,
    };

    enum MenuButtons MyMenuButtons = MenuChoice;
    scanf("%d", &MenuChoice);

    // Appelle � la fonction

    switch (MenuChoice)
    {
    case Start:
        Game();
        break;

    case Quit:
        ExitApp();
        break;

    default:
        printf("Good bye!");
        break;
    }

}
