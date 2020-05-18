#include "carte.h"
#include "pile.h"
#include "joueur.h"
#include "csvloader.h"
#include "util.h"
#ifndef __PLAY_H__
#define __PLAY_H__

/**
 * Incrément la variable global comptant le numero du tour.
 */
void play_Next();

/**
 * Inverse la valeur de la variable global d'incrémentation du tour.
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
 * @return 1 si la carte peut être jouer,  0 sinon.
 */
bool play_IsCardPlayable(card_t *carte_A, card_t *carte_B);

/**
 * Vérifie si un joueur possède une carte jouable.
 * @param main pile des cartes d'un joueur.
 * @param carte_b dernière carte posée
 * @return 1 si le joueur peu jouer,  0 sinon.
 */
bool play_CanPlay(pile_t *main, card_t *carte);

/**
 * Fonction principlale du jeu
 * Fait jouer un joueur et effectue tous les tests.
 * @param joueurs vecteur contenent les joueurs.
 * @param paquets pile sur laquelle les joueurs posent leurs cartes.
 * @param pioche pile : la pioche
 * @param numt indice du joueur
 * @param nbj nombre de joueur
 * @param csv ensemble des messages à afficher
 * @return le nombre de point remporté ou 0 si la manche n'est pas terminée
 */
int play_Play(player_t *joueurs, pile_t *paquets, pile_t *pioches, int numt, int nbj, csv_t *csv);

#endif // !__PLAY_H__
