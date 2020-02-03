
#include "pile.h"
#ifndef __JOUEUR_H__
#define __JOUEUR_H__
 struct joueur
 {
 	char nom ;
 	pile_t * carte ; 
 };
typedef struct joueur joueur_t;
joueur_t *  init_joueur( int nb , char ** noms, pile_t * paquet);

#endif
