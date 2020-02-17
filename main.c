#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/carte.h"
#include "include/pile.h"
#include "include/joueur.h"
#include "include/play.h"

#define maxPoint 500

// Réinitialise les cartes des joueurs et distribue de nouvelle cartes aux joueurs
void reset(pile_t *pioche, player_t *joueurs, int nb)
{
	int i;
	setTour(0);
	for (i = 0; i < nb; ++i)
	{
		joueurs[i].cards = pile_Init();
		pile_Distribute(7, pioche, joueurs[i].cards);
	}
}

int main()
{
	int i, stop = 0, nb = 0, g_Tour;
	char *noms[] = {"Amstrong", "Buzz", "Boomer", "Fury", "Jester", "Merlin", "Casper", "Mountain", "Saltie", "Samara"};

	srand(time(NULL));
	pile_t *paquet = pile_Init();
	pile_FillDeck(paquet);
	pile_t *pioche = pile_Init();
	pile_Shuffle(paquet, pioche, 1);

	printf("Saisissez le nombre de joueurs entre [2 , 10] \n");
	do
	{
		scanf("%d", &nb);
	} while (nb < 2 || nb > 10);

	player_t *joueurs = player_Init(nb, noms, pioche);

	g_Tour = getTour();
	while (stop < maxPoint)
	{
		system("clear -x");
		printf("tour: %d\n\n", g_Tour);
		printf("joueur%d : %s => mes cartes: \n", g_Tour, noms[g_Tour % nb]);
		stop = play(joueurs, paquet, pioche, getTour() % nb, nb);
		if (stop)
		{
			for (i = 0; i < nb; ++i)
			{
				free(joueurs[i].cards);
			}
			free(pioche);
			free(paquet);
			pioche = pile_Init();
			paquet = pile_Init();
			pile_FillDeck(paquet);
			pile_Shuffle(paquet, pioche, 1);

			printf("Fin de la manche.\n");
			if (stop > maxPoint)
			{
				printf("Bravo  %s !!\n", noms[g_Tour]);
			}
			reset(pioche, joueurs, nb);
		}
		g_Tour = getTour();
	}

	for (i = 0; i < nb; ++i)
	{
		free(joueurs[i].cards);
	}
	free(joueurs);
	free(paquet);
	free(pioche);
	return 0;
}
