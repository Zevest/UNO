#include<stdio.h>
#include<stdlib.h>
#include"pile.h"
#include"carte.h"
#include"joueur.h"
#define N 13 
int can_play_cart(carte_t * carte_A , carte_t * carte_B){
	
	return (carte_A->num == carte_B->num || carte_A->color == carte_B->color || carte_A->num > 13) ;

}



int can_play(pile_t * main , carte_t * carte){
	int i ;

	for (i = 0; i < main->_TOP + 1 ; ++i)
	{
		if(can_play_cart( main->_DATA[i]->num , carte))
			return 1 ;
	}
	return 0 ;
}


void play(joueur_t *joueurs , pile_t * paquets , pile_t * pioches, int joueur_1){
	int i ; 
	affiche_carte(get_top(paquets));
	for (int i = 0; i <joueurs[joueur_1]->carte->_TOP; ++i){
		affiche_carte(joueurs[joueur_1]->carte->_DATA[i]);
		if (can_play_carte == 1 )
		{
			
		}
	}

			push(paquet, joueurs[joueur_1]->carte->_DATA[i]);
			carte_remove(paquet, index);
}
