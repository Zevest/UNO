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

void reset(pile_t * pioche, joueur_t * joueurs, int nb){
	int i;
	setTour(0);
	for (i = 0; i < nb; ++i)
	{
		joueurs[i].carte = init_pile();
		distribuer(7, pioche, joueurs[i].carte); 

	}
}

int main(){
	int i, stop = 0, nb= 3, tour; 
	char * noms[] = {"Idir", "Mounir", "Karim", "Steve", "Rachid","ridi","rinuom","mirak","Zevest","dichar"};
	
	srand(time(NULL));
	pile_t * paquet = init_pile();
	remplir_paquet(paquet);
	pile_t * pioche = init_pile();	
	melange(paquet, pioche, 1);
	
	
	
	joueur_t * joueurs = init_joueur(nb, noms, pioche);


	tour = getTour();
	while( stop < 500){ 
		//printf("////////////////////////////////////////////////////// \n");
		system("clear -x");
		printf("tour: %d\n\n",tour);
		printf("joueur%d : %s => mes cartes: \n",tour, noms[tour%nb]);
		stop= play(joueurs, paquet, pioche, getTour()%nb, nb);
		if(stop){
			//reset(paquet,pioche, joueurs, nb);
			
			for(i = 0; i < nb; ++i){
				free(joueurs[i].carte);
			}
			free(pioche);
			free(paquet);
			pioche = init_pile();
			paquet = init_pile();
			remplir_paquet(paquet);
			melange(paquet, pioche, 1);
			
			printf("Fin de la manche.\n");
			reset(pioche, joueurs, nb);
			
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


