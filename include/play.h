#include "carte.h"
#include "pile.h"
#include "joueur.h"
#include "csvloader.h"
#ifndef __PLAY_H__
#define __PLAY_H__

/**
 * Increment la variable global comptant le numero du tour.
 */
void play_Next();

/**
 * Inverse la valeur de la varaiable global d'incémentation du tour.
 */
void play_Inverse();

/**
 * Recupere la variable global du numero tour.
 * @return numero du tour
 */
int play_GetTour();

/**
 * Definie le numero du tour.
 * @param n nouvelle valeur du numero du tour.
 */
void play_SetTour(int n);

/**
 * Vérifie si la carte peut être jouée.
 * @param carte_A carte a comparer
 * @param carte_b dernière carte poser
 * @return 1 si la carte peut etre jouer,  0 sinon.
 */
int play_IsCardPlayable(card_t *carte_A, card_t *carte_B);

/**
 * Vérifie si un joueur possède une carte jouable.
 * @param main pile des carte d'un joueur.
 * @param carte_b dernière carte poser
 * @return 1 si le joueur peu jouer,  0 sinon.
 */
int play_CanPlay(pile_t *main, card_t *carte);

/**
 * Fonction principlale du jeu
 * Fait jouer un joueur et effectue tous les tests.
 * @param joueurs vecteur contenent les joueurs.
 * @param paquets pile sur laquel les joueurs posent leur carte.
 * @param pioche pile : la pioche
 * @param numt indice du joueur
 * @param nbj nombre de joueur
 * @param csv ensemble des messages a afficher
 * @return le nombre de point remporté ou 0 si la manche n'est pas terminée
 */
int play_Play(player_t *joueurs, pile_t *paquets, pile_t *pioches, int numt, int nbj, csv_t *csv);

//int ask(int *v, char *message, char *message2);

#endif // !__PLAY_H__
