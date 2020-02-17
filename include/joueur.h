#include "pile.h"
#ifndef __JOUEUR_H__
#define __JOUEUR_H__
struct player
{
	int score;
	char *name;
	pile_t *cards;
	//int gagner;
};
typedef struct player player_t;
player_t *player_Init(int nb, char **noms, pile_t *paquet);

#endif
