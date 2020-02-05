#include "carte.h"
#include "pile.h"
#include "joueur.h"



void next();
void inverse();

int getTour();
void setTour(int n);

int can_play_cart(carte_t * carte_A , carte_t * carte_B);

int can_play(pile_t * main , carte_t * carte);

int play(joueur_t *joueurs , pile_t * paquets , pile_t * pioches, int, int);

int ask(int * v, char * message, char* message2);
