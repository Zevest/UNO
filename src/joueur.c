#include <stdio.h>
#include <stdlib.h>
#include "pile.h"
#include "joueur.h"

#define Nombre_carte 7

/// Initialise les joueurs
player_t *player_Init(int nb, char *noms[], pile_t *deck)
{
	int i;
	player_t *joueurs = malloc(nb * sizeof *joueurs);
	for (i = 0; i < nb; ++i)
	{
		joueurs[i].name = noms[i];
		joueurs[i].cards = pile_Init();

		pile_Distribute(Nombre_carte, deck, joueurs[i].cards);
	}
	return joueurs;
}
