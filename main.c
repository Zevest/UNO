#include <stdio.h>
#include <stdlib.h>
#include "carte.h"
#include "pile.h"
#include "joueur.h"
#include "play.h"
#include <time.h>


#define W 30
#define H 15

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

void reset(){

}

int main(){
	int i, j = 0;
	srand(time(NULL));
	pile_t * paquet = init_pile();
	remplir_paquet(paquet);
	pile_t * pioche = init_pile();	
	melange(paquet, pioche, 1);
	
	int nb = 3;


	char * noms[] = {"Idir", "Mounir", "Karim", "Steve", "Rachid","ridi","rinuom","mirak","Zevest","dichar"};
	
	joueur_t * joueurs = init_joueur(nb, noms, pioche);

	int tour;
	tour = getTour();
	while( tour * tour < 9999999){ 
		printf("%d joueur : %s\n",tour, noms[tour%nb]);
		if(play(joueurs, paquet, pioche, getTour()%nb, nb)){
			reset();
		}
		tour = getTour();
	}
	
	
	
	
	for(i = 0; i < nb; ++i){
		free(joueurs[i].carte);
	}
	free(joueurs);
	free(paquet);
	free(pioche);
	return 0;
}


