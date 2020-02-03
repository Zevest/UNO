#include <stdio.h>
#include <stdlib.h>
#include "pile.h"
//#include "carte.h"
#define Nombre_carte 7
 struct joueur
 {
 	char * nom ;
 	pile_t * carte ; 
 };
typedef struct joueur joueur_t;

joueur_t *  init_joueur(int nb , char * noms[], pile_t * paquet){
	int i,j ; 
	joueur_t * joueurs = malloc(nb * sizeof *joueurs);
	for (i = 0; i < nb; ++i)
	{
		joueurs[i].nom = noms[i]; 
		joueurs[i].carte = init_pile();
		//printf("%s\n", noms[i]);
		
		distribuer(Nombre_carte, paquet, joueurs[i].carte); 
		//printf("nb cartes restante : %d ",  paquet->_TOP+1);
		/*for(j = 0; j < joueurs[i].carte->_TOP+1;++j){
			printf("%s\n", SYMBOL[joueurs[i].carte->_DATA[j]->num]);
		}*/
	}
	return joueurs;
}
