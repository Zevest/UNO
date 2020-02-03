#include<stdio.h>
#include<stdlib.h>
#include"pile.h"
#include"carte.h"
#include"joueur.h"
#define N 13 
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
	for (int i = 0; i <joueurs[joueur_1].carte->_TOP; ++i){
		affiche_carte(joueurs[joueur_1].carte->_DATA[i]);
	}
	printf("les cartes qu'on peut jouer \n");
	for (int i = 0; i <joueurs[joueur_1].carte->_TOP; ++i)
	{
		if (can_play_carte(joueurs[joueur_1].carte->_DATA[i], get_top(paquets)) == 1 )
		{ 
			affiche_carte(joueurs[joueur_1].carte->_DATA[i]);	
		}
	}
	do{
		printf("bug\n");
		scanf("%d",&i);

	}while(!(can_play_carte(joueurs[joueur_1].carte->_DATA[i], get_top(paquets))));
		push(paquets, joueurs[joueur_1].carte->_DATA[i]);//push(paquet, joueurs[joueur_1].carte->_DATA[i]);
		carte_remove(joueurs[joueur_1].carte,i);
	switch(joueurs[joueur_1].carte->_DATA[i]->num){
		case 12 : 
			//next();
			break ; 
		case 11 :
	 		//inverse();
	 		break ; 
	 	case 13 :
	 		do {
	 			printf("bug\n");
				scanf("%d",&a);
	 		}
	 		while(!(a == 'j' || a =='j' || a == 'R'|| a == 'r' || a == 'B'|| a == 'b' || a == 'V'|| a == 'v' ));
	 			joueurs[joueur_1].carte->_DATA[i]->color = a ; 
	}	
	if (joueurs[joueur_1].carte->_DATA[i]->num == 13)
	{
	//	next();
	}
}