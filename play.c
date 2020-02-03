#include<stdio.h>
#include<stdlib.h>
#include"pile.h"
#include"carte.h"
#include"joueur.h"
#include "play.h"
#define N 13 

static int sens = 1;
static int tour = 0;

void next(){
	printf("\nnext !!! \n");
	tour += sens;
}
int getTour(){
	return tour;
}

void setTour(int n){
	tour = n;
}

void inverse(){
	sens *= -1;
}

int can_play_carte(carte_t * carte_A , carte_t * carte_B){
	
	return (carte_A->num == carte_B->num || carte_A->color == carte_B->color || carte_A->num > 13) ;

}



int can_play(pile_t * main , carte_t * carte){
	int i ;

	for (i = 0; i < main->_TOP + 1 ; ++i)
	{
		if(can_play_carte( main->_DATA[i], carte))
			return 1 ;
	}
	return 0 ;
}


void play(joueur_t *joueurs , pile_t * paquets , pile_t * pioches, int joueur_1){
	int i,a ; 
	affiche_carte(get_top(paquets));
	printf("\n");
	for (int i = 0; i <joueurs[joueur_1].carte->_TOP; ++i){
		affiche_carte(joueurs[joueur_1].carte->_DATA[i]);
	}
	printf("\nles cartes qu'on peut jouer \n");
	for (int i = 0; i <joueurs[joueur_1].carte->_TOP; ++i)
	{
		if (can_play_carte(joueurs[joueur_1].carte->_DATA[i], get_top(paquets)) == 1 )
		{ 
			printf("(%d:", i);
			affiche_carte(joueurs[joueur_1].carte->_DATA[i]);	
			printf(") ");
		}
		
	}
	do{
		printf("\n");
		affiche_carte(get_top(paquets));
		printf("\nQuel carte jouer?\n");
		scanf("%d",&i);

	}while(!(can_play_carte(joueurs[joueur_1].carte->_DATA[i], get_top(paquets))));
		push(paquets, joueurs[joueur_1].carte->_DATA[i]);//push(paquet, joueurs[joueur_1].carte->_DATA[i]);
		carte_remove(joueurs[joueur_1].carte,i);
	printf("num : %d %d\n",i, joueurs[joueur_1].carte->_DATA[i]->num);
	switch(get_top(paquets)->num){
		
		default:
			printf("normal\n");
			break;
		case 11 : 
			inverse();
			break ; 
		case 12 :
	 		next();
	 		break ; 
	 	case 13 :
	 		do {
	 			printf("bug\n");
				scanf("%d",&a);
	 		}
	 		while(!(a == 'j' || a =='j' || a == 'R'|| a == 'r' || a == 'B'|| a == 'b' || a == 'V'|| a == 'v' ));
	 			joueurs[joueur_1].carte->_DATA[i]->color = a ;
	 		break; 
	}	
	/*if (joueurs[joueur_1].carte->_DATA[i]->num == 13)
	{
		next();
	}*/
	next();
	printf("tour %d\n",tour); 
	if(tour < 0)
		tour = 4;
}
