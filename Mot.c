#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRIES 7

struct HangmanGame {
    const char* motSecret;
    int longueurMot;
    char lettresDevinees[26];
    int tries;
};

//void Replay() {
//    char choix;
//
//    printf("Do you want to replay ? (O/N) : ");
//    fflush(stdin);
//    scanf_s(" %c", &choix);
//
//    if (choix == 'O' || choix == 'o') {
//        // Si le joueur veut rejouer, appelez la fonction Game pour démarrer une nouvelle partie.
//        Game();
//    }
//    else if (choix == 'N' || choix == 'n') {
//        printf("Thank for playing ! Good bye.\n");
//        //ExitApp(); // Vous pouvez également ajouter un appel à la fonction ExitApp pour quitter l'application ici.
//    }
//    else {
//        // Réponse non valide, redemandez.
//        printf("Answer incorrect. Please answer by Y(yes) or N(no)\n");
//        Replay(); // Appel récursif pour redemander la réponse.
//    }
//}

void afficherMotPartiel(const struct HangmanGame* game) {
    for (int i = 0; i < game->longueurMot; i++) {
        if (strchr(game->lettresDevinees, game->motSecret[i]) != NULL) {
            printf("%c ", game->motSecret[i]);
        }
        else {
            printf("_ ");
        }
    }
    printf("\n");
}

const char* choisirMotSecret(const char* motsSecrets[], int nombreDeMots) {
    srand((unsigned int)time(NULL));
    int indice = rand() % nombreDeMots;
    return motsSecrets[indice];
}

void initialiserPartie(struct HangmanGame* game, const char* motsSecrets[], int nombreDeMots) {
    game->motSecret = choisirMotSecret(motsSecrets, nombreDeMots);
    game->longueurMot = strlen(game->motSecret);
    memset(game->lettresDevinees, 0, sizeof(game->lettresDevinees));
    game->tries = 0;
}

void ExitApp() {
    printf("See you soon.\n");
}

void Game() {
    struct HangmanGame game;
    const char* motsSecrets[] = {
        "programmation",
        "informatique",
        "pendu",
        "developpeur",
        "ordinateur"
    };
    const int nombreDeMots = sizeof(motsSecrets) / sizeof(motsSecrets[0]);

    initialiserPartie(&game, motsSecrets, nombreDeMots);

    while (game.tries < MAX_TRIES) {
        printf("\nSecret word: ");
        afficherMotPartiel(&game);
        printf("Guessed letter: %s\n", game.lettresDevinees);
        printf("Tries remaining: %d\n", MAX_TRIES - game.tries);
        printf("Press 2 to quit\n");
        printf("Enter a letter: ");

        //Affiche le pendu au fur et à mesure des essais
        if (game.tries > 0) {
            printf("Pendu :\n");

            // Afficher le pendu à l'aide d'une boucle
            for (int i = 0; i < game.tries; i++) {
                if (i == 0) {
                    printf("  +---+\n");
                }
                else if (i == 1) {
                    printf("  |   |\n");
                }
                else if (i == 2) {
                    printf("  O   |\n");
                }
                else if (i == 3) {
                    printf(" /|");
                }
                else if (i == 4) {
                    printf("\\  | \n");
                }
                else if (i >= 5) {
                    printf(" / \\  |\n");
                }

            }
        }

        int nb;
        scanf_s(" %d", &nb);
        if (nb == 2) {
            printf("You left the game.\n");
            return;
        }

        char lettre;
        scanf_s(" %c", &lettre);

        if (strchr(game.lettresDevinees, lettre) != NULL) {
            printf("You've already guessed this letter. Try again.\n");
            continue;
        }

        game.lettresDevinees[strlen(game.lettresDevinees)] = lettre;

        if (strchr(game.motSecret, lettre) != NULL) {
            printf("Good letter!\n");
        }
        else {
            printf("The letter is not in the word.\n");
            game.tries++;
        }

        int motComplet = 1;
        for (int i = 0; i < game.longueurMot; i++) {
            if (strchr(game.lettresDevinees, game.motSecret[i]) == NULL) {
                motComplet = 0;
                break;
            }
        }

        if (motComplet) {
            printf("\nCongratulations, you've guessed the word: %s\nThanks for playing the hangman's game!\n", game.motSecret);
            break;
        }
    }

    if (game.tries >= MAX_TRIES) {
        printf("\nYou've exhausted all your attempts. The secret word was: %s\n", game.motSecret);
    }
}

void MainMenu() {
    printf("Welcome to the hangman game!\n");

        printf("-----Main Menu-----\n\n");
        printf("[1] Start the game\n");
        printf("or\n");
        printf("[2] Leave the game\n");
        printf("\nChoose an option: ");
        

        int MenuChoice = 2;

        enum MenuButtons {
            Start = 1,
            Quit,
        };

        enum MenuButtons MyMenuButtons = MenuChoice;
        scanf_s("%d", &MenuChoice);

        // Appelle à la fonction 

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

