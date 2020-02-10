#include <stdio.h>
#include <stdlib.h>
#include "carte.h"
#include "pile.h"
#include "joueur.h"
#include "play.h"
#include <time.h>
#define maxPoint 500


// Réinitialise les cartes des joueurs et distribue de nouvelle cartes aux joueurs 
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
	int i, stop = 0, nb= 0, tour; 
	char * noms[] = {"Amstrong", "Buzz", "Boomer", "Fury", "Jester","Merlin","Casper","Mountain","Saltie","Samara"};
	
	srand(time(NULL));
	pile_t * paquet = init_pile();
	remplir_paquet(paquet);
	pile_t * pioche = init_pile();	
	melange(paquet, pioche, 1);
	
	printf("Saisissez le nombre de joueurs entre [2 , 10] \n");
	do{
	scanf("%d",&nb);
	}while(nb < 2 || nb > 10);
	
	joueur_t * joueurs = init_joueur(nb, noms, pioche);

	tour = getTour();
	while( stop < maxPoint){ 
		system("clear -x");
		printf("tour: %d\n\n",tour);
		printf("joueur%d : %s => mes cartes: \n",tour, noms[tour%nb]);
		stop= play(joueurs, paquet, pioche, getTour()%nb, nb);
		if(stop){
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
			if(stop > maxPoint){
				printf("Bravo  %s !!\n", noms[tour]);
			}
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


