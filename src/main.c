#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "carte.h"
#include "pile.h"
#include "joueur.h"
#include "play.h"
#include "csvloader.h"
#include "util.h"

#define maxPoint 50

/// Réinitialise les cartes des joueurs et distribue de nouvelle cartes aux joueurs
void g_Reset(pile_t *pioche, player_t *players, int nb)
{
	int i;
	play_SetTour(0);
	for (i = 0; i < nb; ++i)
	{
		players[i].cards = pile_Init();
		pile_Distribute(7, pioche, players[i].cards);
	}
}

// Affiche le tour et le noms du joueur
void showStatus(csv_t *csv, player_t *players, int turn, int realTurn, int playerCount)
{
	system("clear -x");
	printf(csv->data[1].message, realTurn);
	util_JumpLine(2);
	printf(csv->data[2].message, turn % playerCount, players[turn % playerCount].name);
	util_JumpLine(1);
}

// Affiche le scores des joueur et reinitialise la partie
void endRound(int playerCount, int turn, player_t *players, pile_t **package, pile_t **deck, string_t names[], csv_t *csv, int score)
{
	int i = 0;
	system("clear -x");
	printf(csv->data[4].message, names[turn % playerCount]);
	util_JumpLine(1);
	printf(csv->data[13].message, players[turn % playerCount].name, score);
	util_JumpLine(1);

	// Affichage du tableau des scores
	printf(csv->data[15].message, NULL);
	util_JumpLine(1);
	for (i = 0; i < playerCount; ++i)
	{
		printf(csv->data[14].message, players[i].name, players[i].score);
		util_JumpLine(1);
	}
	sleep(5);
	for (i = 0; i < playerCount; ++i)
		pile_Delete(players[i].cards);

	// Réinitialisation de la pioche
	pile_Delete(*deck);
	pile_Delete(*package);
	*deck = pile_Init();
	*package = pile_Init();
	pile_FillDeck(*package);
	pile_Shuffle(*package, *deck, 1);

	util_JumpLine(1);
	if (score >= maxPoint)
	{
		printf(csv->data[4].message, names[turn % playerCount]);
		sleep(2);
	}

	g_Reset(*deck, players, playerCount);
}

int main(int argc, char **argv)
{
	int i, stop = 0, playerCount = 0, turn, realTurn = 0;
	char *names[] = {"Amstrong", "Buzz", "Boomer", "Fury", "Jester", "Merlin", "Casper", "Mountain", "Saltie", "Samara"};
	pile_t *cardPackage, *deck;
	player_t *players;
	csv_t *csv;
	char buf[30] = {};

	if (argc > 1) // Quand on lance le programme avec un ficher de message passé par argument
		csv = csv_ParseCSV(argv[1], NULL);
	else
		csv = csv_ParseCSV("res/Message.csv", NULL);

	if (csv == NULL)
	{
		printf("Essayez de retourner dans le répertoire parent\npuis d'utiliser la commande 'make run' pour executer le programme.\n");
		printf("Sinon, essayez ceci:\n");
		printf("%s %s\n", argv[0], "../res/Message.csv");
		exit(EXIT_FAILURE);
	}
	// Initiallisation et mélange de la pioche
	srand(time(NULL));

	cardPackage = pile_Init();
	deck = pile_Init();

	pile_FillDeck(cardPackage);
	pile_Shuffle(cardPackage, deck, 1);

	do
	{
		util_Ask(csv->data[0].message, buf, util_IsNumeric);
		playerCount = atoi(buf);
	} while (playerCount < 2 || playerCount > 10);
	players = player_Init(playerCount, names, deck);

	// Boucle Principale
	while (stop < maxPoint)
	{
		turn = play_GetTour();
		realTurn++;
		showStatus(csv, players, turn, realTurn, playerCount);
		stop = play_Play(players, cardPackage, deck, play_GetTour() % playerCount, playerCount, csv);
		if (stop)
		{
			endRound(playerCount, turn, players, &cardPackage, &deck, names, csv, stop);
			realTurn = 0;
		}
	}
	printf(csv->data[16].message, names[turn % playerCount]);
	util_JumpLine(1);
	// Liberation de la memoire
	for (i = 0; i < playerCount; ++i)
		pile_Delete(players[i].cards);
	free(players);
	pile_Delete(cardPackage);
	pile_Delete(deck);
	csv_DeleteCSV(csv);
	return 0;
}
