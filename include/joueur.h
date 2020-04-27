#include "pile.h"
#ifndef __JOUEUR_H__
#define __JOUEUR_H__

/**
 * Structure d'un joueur
 * Elle contient le score le nom et les cartes d'un joueur.
 */
struct player
{
	int score;
	char *name;
	pile_t *cards;
	//int gagner;
};
typedef struct player player_t;

/**
 * Cree et initialise un nombre de joueurs.
 * @param nb nombre de joueur.
 * @param noms noms des joueurs.
 * @param paquet paquet de carte à distribuer.
 * @return un vecteur contenant les joueurs crées
 */
player_t *player_Init(int nb, char **noms, pile_t *paquet);

#endif
