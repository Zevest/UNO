#include<stdio.h>
#include<stdlib.h>
#include"pile.h"
#include"carte.h"
#include"joueur.h"
#include "play.h"
#define N 13 

static int sens = 1;
static int tour = 0;
static int compte = 0 ; 
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
	
	return (carte_A->num == carte_B->num || carte_A->color == carte_B->color || carte_A->num >= 13) ;

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
 
int G_point(joueur_t *g, int joueur){
	int i ; 
	int s =  0; 

	for (i = 0; i < g[joueur].carte->_TOP+1; i++)	{
		switch(g[joueur].carte->__DATA[i]->num){
			default : 
				s += g[joueur].carte->_DATA[i]->num ; 
			case 10 : 
				case 11 : 
					case 12 : 
						s += 20 ;
			case 13 :
				case 14 : 
					s += 50 ;   
		}

	}
	return s ;
}
void play(joueur_t *joueurs , pile_t * paquets , pile_t * pioches, int joueur_1){
	int i; char a ; 
	int tmp = 0 ;
	printf("RIEN\n");
	affiche_carte(get_top(paquets));
	printf("\n");
	printf("%d\n",joueur_1);
	for (int i = 0; i <joueurs[joueur_1].carte->_TOP+1; ++i){

		affiche_carte(joueurs[joueur_1].carte->_DATA[i]);
	}
	printf("\nles cartes qu'on peut jouer \n");
	for (int i = 0; i <joueurs[joueur_1].carte->_TOP+1; ++i)
	{
		if (can_play_carte(joueurs[joueur_1].carte->_DATA[i], get_top(paquets)) == 1 )
		{ 
			tmp++ ;
			printf("(%d:", i);
			affiche_carte(joueurs[joueur_1].carte->_DATA[i]);	
			printf(") ");
		}
		
	}

	if(compte > 0){
		for (int i = 0; i < joueurs[joueur_1].carte->_TOP+1; ++i)
		{
			if (joueurs[joueur_1].carte->_DATA[i]->num == 10 || joueurs[joueur_1].carte->_DATA[i]->num == 14){
				
			}
		}
	}
	else if (tmp){
	do{
		printf("\n");
		affiche_carte(get_top(paquets));
		printf("\nQuel carte jouer?\n");
		scanf("%d",&i);

	}while(i > joueurs[joueur_1].carte->_TOP || !(can_play_carte(joueurs[joueur_1].carte->_DATA[i], get_top(paquets))));
		push(paquets, joueurs[joueur_1].carte->_DATA[i]);
		carte_remove(joueurs[joueur_1].carte,i);
	}
	else{
		printf("%s a pioché \n",joueurs[joueur_1].nom);
		distribuer(1,pioches,joueurs[joueur_1].carte);
	}
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
	 			a = '\0';
	 			printf("quelle coleur \n");
				scanf("%c",&a);
	 		}
	 		while(!(a == 'J' || a == 'R'|| a == 'B'|| a == 'V' ));
	 			get_top(paquets)->color = a ;
	 		break; 
	}	
	/*switch(empty(joueurs[joueur_1].carte->_TOP)){
		default : 
			joueurs[joueur_1].point += joueurs[joueur_1].carte->_DATA
	//}
	/*if (joueurs[joueur_1].carte->_DATA[i]->num == 13)
	{
		next();
	}*/
	next();
	printf("tour %d\n",tour); 
	if(tour < 0)
		tour = 4;
}
int fin_jeux(joueur_t *g , int joueur){
	int i, j=-1, s = 0 ; 

	for (i = 0; i <joueur; ++i)
	{
		if(empty(joueurs[joueur_1].carte))
			j = i ;
	}
	if(j != -1 ){
		for (i = 0; i <joueur; ++i){
			if(j !=i )
				s += G_point(g,i)
		}
	g[j].point = s ; 
	}
	return s ; 
}