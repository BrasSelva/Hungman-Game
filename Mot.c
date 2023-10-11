#include <stdio.h>
#include "Mot.h"
#define Mot_H
#define MAX_TRIES 7// Nombre maximum d'essais

// Déclarez cette fonction au début de votre code pour la rendre accessible aux autres fonctions.
void Replay() {
	char choix;

	printf("Do you want to replay ? (O/N) : ");
	fflush(stdin);
	scanf_s(" %c", &choix);

	if (choix == 'O' || choix == 'o') {
		// Si le joueur veut rejouer, appelez la fonction Game pour démarrer une nouvelle partie.
		Game();
	}
	else if (choix == 'N' || choix == 'n') {
		printf("Thank for playing ! Good bye.\n");
		//ExitApp(); // Vous pouvez également ajouter un appel à la fonction ExitApp pour quitter l'application ici.
	}
	else {
		// Réponse non valide, redemandez.
		printf("Answer incorrect. Please answer by Y(yes) or N(no)\n");
		Replay(); // Appel récursif pour redemander la réponse.
	}
}

//Fonction d'affichage du pendu

void afficherPendu(int tentatives) {
	switch (tentatives) {
	case 0:
		printf("  +---+\n");
		printf("  |   |\n");
		printf("      |\n");
		printf("      |\n");
		printf("      |\n");
		printf("      |\n");
		break;
	case 1:
		printf("  +---+\n");
		printf("  |   |\n");
		printf("  O   |\n");
		printf("      |\n");
		printf("      |\n");
		printf("      |\n");
		break;
	case 2:
		printf("  +---+\n");
		printf("  |   |\n");
		printf("  O   |\n");
		printf("  |   |\n");
		printf("      |\n");
		printf("      |\n");
		break;
	case 3:
		printf("  +---+\n");
		printf("  |   |\n");
		printf("  O   |\n");
		printf(" /|   |\n");
		printf("      |\n");
		printf("      |\n");
		break;
	case 4:
		printf("  +---+\n");
		printf("  |   |\n");
		printf("  O   |\n");
		printf(" /|\\  |\n");
		printf("      |\n");
		printf("      |\n");
		break;
	case 5:
		printf("  +---+\n");
		printf("  |   |\n");
		printf("  O   |\n");
		printf(" /|\\  |\n");
		printf(" /    |\n");
		printf("      |\n");
		break;
	case 6:
		printf("  +---+\n");
		printf("  |   |\n");
		printf("  O   |\n");
		printf(" /|\\  |\n");
		printf(" / \\  |\n");
		printf("      |\n");
		break;
	}
}

// Liste de mots secrets
const char* motsSecrets[] = {
	"programmation",
	"informatique",
	"pendu",
	"developpeur",
	"ordinateur"
};
const int nombreDeMots = sizeof(motsSecrets) / sizeof(motsSecrets[0]);

// Fonction pour choisir un mot secret aléatoire
const char* choisirMotSecret() {
	srand(time(NULL));
	int indice = rand() % nombreDeMots;
	return motsSecrets[indice];
}

// Fonction pour afficher le mot partiel avec les lettres devinées
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

void Startup() {
	printf(" \n Launche the game \n \n");

}

void Game() {
	const char* motSecret = choisirMotSecret();
	int longueurMot = strlen(motSecret);
	char lettresDevinees[26]; // Tableau pour stocker les lettres devinées
	int tries = 0;

	memset(lettresDevinees, 0, sizeof(lettresDevinees)); // Initialiser le tableau de lettres devinées

	printf("Welcome to the hungman game !\n");

	while (tries < MAX_TRIES) {
		printf("\nSecret word : ");
		afficherMotPartiel(motSecret, lettresDevinees);
		printf("Guessed letter: %s \n", lettresDevinees);
		printf("Try remaining : %d \n", MAX_TRIES - tries);
		printf("Tape 2 to quit \n");
		printf("Enter a letter : \n");

		//Affiche le pendu au fur et à mesure des essais

		if (tries > 0) {
			printf("Lost :\n");
			afficherPendu(tries);
		}
		// Méthode pour pouvoir quitter le jeu pendant le jeu 

		int nb;
		scanf_s(" %d", &nb);
		if (nb == 2) {
			printf("You left the game.\n");
			return 0; // Sortie du jeu
		}

		char lettre;
		scanf_s(" %c", &lettre);



		// Vérifier si la lettre a déjà été devinée
		if (strchr(lettresDevinees, lettre) != NULL) {
			printf("You've already guessed this letter. Try again.\n");
			continue;
		}

		// Ajouter la lettre aux lettres devinées
		lettresDevinees[strlen(lettresDevinees)] = lettre;

		// Vérifier si la lettre est dans le mot secret
		if (strchr(motSecret, lettre) != NULL) {
			printf("Good letter!\n");
		}
		else {
			printf("The letter is not in the word. \n");
			tries++;
		}

		// Vérifier si le joueur a deviné le mot complet
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

	// Si le nombre d'essai est à 0

	if (tries >= MAX_TRIES) {
		printf("\n You've exhausted all your attempts. The secret word was : %s\n", motSecret);
	}
	Replay(); //appelle à la fonction game
	return 0;
}

// Fonction pour quitter le jeu
void ExitApp() {
	printf("See you seen. \n");
	Replay();
	exit(0);


}

// Fonction qui sert à guider le joueur

void MainMenu() {
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







