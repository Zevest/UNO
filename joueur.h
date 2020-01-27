
#include "pile.h"
#ifndef __JOUEUR_H__
#define __JOUEUR_H__
 struct joueur
 {
 	char nom ;
 	pile_t * carte ; 
 };
typedef struct joueur joueur_t;
void  init_joueur(joueur_t * joueurs, int nb , char ** noms, pile_t * paquet);

#endif
