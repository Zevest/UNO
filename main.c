#include <stdio.h>
#include <stdlib.h>
#include "carte.h"
#include "pile.h"
#include "joueur.h"
#include "play.h"
#include <time.h>


#define W 30
#define H 15

static int sens;
static int tour;

void affiche_table(pile_t * paquet, joueur_t * joueur){
	int j,i;
	for(i = 0; i < W; ++i){
		printf("#");
	}
	printf("\n");
	for(j = 0; j < H; ++j){
		printf("\n");
	}
	
}
int main(){
	int i, j = 0;

	//srand(time(NULL));
	pile_t * paquet = init_pile();
	remplir_paquet(paquet);
	pile_t * pioche = init_pile();
	melange(paquet, pioche, 1);
	
	char * noms[] = {"Idir", "Mounir", "Karim", "Steve", "Rachid"};
	
	joueur_t * joueurs = init_joueur(5, noms, pioche);
	
	
	/*for(i = 0; i < 5; ++i){
		printf("%s\n", noms[i]);
		for(j = 0; j < joueurs[i].carte->_TOP+1;++j){
		
			affiche_carte(joueurs[i].carte->_DATA[j]);
		}
		printf("\n");
	}*/
	
	play(joueurs, paquet, pioche, 0);
	
	
	
	
	for(i = 0; i < 4; ++i){
		free(joueurs[i].carte);
	}
	free(joueurs);
	free(paquet);
	free(pioche);
	//free(jeux1);
	return 0;
}


