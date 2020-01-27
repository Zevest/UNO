#include <stdio.h>
#include <stdlib.h>
#include "pile.h"
//#include "carte.h"
#define Nombre_carte 7
 struct joueur
 {
 	char nom ;
 	pile_t * carte ; 
 };
typedef struct joueur joueur_t;

void  init_joueur(joueur_t * joueurs, int nb , char ** noms, pile_t * paquet){
	int i ; 
	joueurs = malloc(nb * sizeof * joueurs);
	for (i = 0; i < nb; ++i)
	{
		joueurs[i].nom = noms[i]; 
		distribuer(Nombre_carte, paquet, joueurs[i].carte); 
	}
}
