#include "carte.h"
#include "pile.h"
#include "joueur.h"
#include "csvloader.h"
#ifndef __PLAY_H__
#define __PLAY_H__

/**
 * Increment la variable global comptant le numero du tour.
 */
void next();

/**
 * Inverse la valeur de la varaiable global d'incémentation du tour.
 */
void inverse();

/**
 * Recupere la variable global du numero tour.
 * @return numero du tour
 */
int getTour();

/**
 * Definie le numero du tour.
 * @param n nouvelle valeur du numero du tour.
 */
void setTour(int n);

/**
 * Vérifie si la carte peut être jouée.
 * @param carte_A carte a comparer
 * @param carte_b dernière carte poser
 * @return 1 si la carte peut etre jouer,  0 sinon.
 */
int can_play_cart(card_t *carte_A, card_t *carte_B);

/**
 * Vérifie si un joueur possède une carte jouable.
 * @param main pile des carte d'un joueur.
 * @param carte_b dernière carte poser
 * @return 1 si le joueur peu jouer,  0 sinon.
 */
int can_play(pile_t *main, card_t *carte);

/**
 * Fonction principlale du jeu
 * Fait jouer un joueur et effectue tous les tests.
 * @param joueurs vecteur contenent les joueurs.
 * @param paquets pile sur laquel les joueurs posent leur carte.
 * @param pioche pile : la pioche
 * @param numt indice du joueur
 * @param nbj nombre de joueur
 * @param csv ensemble des messages a afficher
 */
int play(player_t *joueurs, pile_t *paquets, pile_t *pioches, int numt, int nbj, csv_t *csv);

int ask(int *v, char *message, char *message2);

#endif // !__PLAY_H__
