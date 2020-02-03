#include "carte.h"
#include "pile.h"
#include "joueur.h"

int can_play_cart(carte_t * carte_A , carte_t * carte_B);

int can_play(pile_t * main , carte_t * carte);

void play(joueur_t *joueurs , pile_t * paquets , pile_t * pioches, int joueur_1);
