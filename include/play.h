#include "carte.h"
#include "pile.h"
#include "joueur.h"
#include "csvloader.h"
#ifndef __PLAY_H__
#define __PLAY_H__

void next();
void inverse();

int getTour();
void setTour(int n);

int can_play_cart(card_t *carte_A, card_t *carte_B);

int can_play(pile_t *main, card_t *carte);

int play(player_t *joueurs, pile_t *paquets, pile_t *pioches, int, int, csv_t *);

int ask(int *v, char *message, char *message2);

#endif // !__PLAY_H__
