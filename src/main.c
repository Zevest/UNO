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

#define maxPoint 500

/// Réinitialise les cartes des joueurs et distribue de nouvelle cartes aux joueurs
void g_Reset(pile_t *pioche, player_t *joueurs, int nb)
{
	int i;
	play_SetTour(0);
	for (i = 0; i < nb; ++i)
	{
		joueurs[i].cards = pile_Init();
		pile_Distribute(7, pioche, joueurs[i].cards);
	}
}

int main(int argc, char **argv)
{
	int i, stop = 0, nb = 0, g_Tour;
	char *noms[] = {"Amstrong", "Buzz", "Boomer", "Fury", "Jester", "Merlin", "Casper", "Mountain", "Saltie", "Samara"};
	pile_t *paquet, *pioche;
	player_t *joueurs;
	csv_t *csv;
	if (argc > 1)
	{
		csv = csv_ParseCSV(argv[1], NULL);
	}
	else
	{
		csv = csv_ParseCSV("res/Message.csv", NULL);
	}
	if (csv == NULL)
	{
		printf("Essayez de retourner dans le répertoire parent\npuis d'utiliser la commande 'make run' pour executer le programme.\n");
		printf("Sinon, essaye ceci:\n");
		printf("%s %s\n", argv[0], "../res/Message.csv");
		exit(EXIT_FAILURE);
	}

	paquet = pile_Init();
	pioche = pile_Init();

	pile_FillDeck(paquet);
	pile_Shuffle(paquet, pioche, 1);

	srand(time(NULL));
	printf(csv->data[0].message, NULL);
	util_JumpLine(1);

	do
	{
		scanf("%d", &nb);
	} while (nb < 2 || nb > 10);
	util_ClearInputBuffer();
	joueurs = player_Init(nb, noms, pioche);

	g_Tour = play_GetTour();
	while (stop < maxPoint)
	{
		system("clear -x");
		printf(csv->data[1].message, g_Tour);
		util_JumpLine(2);
		printf(csv->data[2].message, g_Tour, joueurs[g_Tour % nb].name);
		util_JumpLine(1);

		stop = play_Play(joueurs, paquet, pioche, play_GetTour() % nb, nb, csv);
		if (stop)
		{
			system("clear -x");
			printf(csv->data[4].message, noms[g_Tour]);
			util_JumpLine(1);
			printf(csv->data[13].message, joueurs[g_Tour % nb].name, stop);
			util_JumpLine(1);
			printf(csv->data[15].message, NULL);
			util_JumpLine(1);
			for (int i = 0; i < nb; ++i)
			{
				printf(csv->data[14].message, joueurs[i].name, joueurs[i].score);
				util_JumpLine(1);
			}
			sleep(5);
			for (i = 0; i < nb; ++i)
			{
				pile_Delete(joueurs[i].cards);
			}
			pile_Delete(pioche);
			pile_Delete(paquet);
			pioche = pile_Init();
			paquet = pile_Init();
			pile_FillDeck(paquet);
			pile_Shuffle(paquet, pioche, 1);

			util_JumpLine(1);
			if (stop >= maxPoint)
			{
				printf(csv->data[4].message, noms[g_Tour]);
				sleep(2);
			}

			g_Reset(pioche, joueurs, nb);
		}
		g_Tour = play_GetTour();
	}

	for (i = 0; i < nb; ++i)
	{
		pile_Delete(joueurs[i].cards);
	}
	free(joueurs);
	pile_Delete(paquet);
	pile_Delete(pioche);
	csv_DeleteCSV(csv);
	return 0;
}
