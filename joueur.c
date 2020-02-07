#include <stdio.h>
#include <stdlib.h>
#include "pile.h"
#include "joueur.h"

#define Nombre_carte 7



// Initialise les joueurs 
joueur_t *  init_joueur(int nb , char * noms[], pile_t * paquet){
	int i,j ; 
	joueur_t * joueurs = malloc(nb * sizeof *joueurs);
	for (i = 0; i < nb; ++i)
	{
		joueurs[i].nom = noms[i]; 
		joueurs[i].carte = init_pile();
		
		
		distribuer(Nombre_carte, paquet, joueurs[i].carte); 
	
	}
	return joueurs;
}
