
#include "pile.h"
#ifndef __JOUEUR_H__
#define __JOUEUR_H__
 struct joueur
 {
  	int point;
 	char * nom ;
 	pile_t * carte ; 
 	int gagner;
 };
typedef struct joueur joueur_t;
joueur_t *  init_joueur( int nb , char ** noms, pile_t * paquet);

#endif

/*

bool b1 = (carte_B->num == 10) ; // +2 sur le jeu
	bool b2 = (b1||(carte_B->num == 14)); // +2 ou +4 sur le jeu
	bool a1 = ((carte_A->num == 10) && b1); // +2 dans la main et +2 sur le jeu
	bool a2 = ((carte_A->num == 14) && b2); // +2 ou +4 dans la main et +2 ou +4 sur le jeu
	bool a = (a1 || a2);
	bool b = (compte == 0) && (carte_A->num == carte_B->num || carte_A->color == carte_B->color || carte_A->num >= 13);
	
	return (a ? a : b); //(a || b) && !(a && b);
	*/
	
	
	
/*
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
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
	
	bool b1 = (carte_B->num == 10) ; // +2 sur le jeu
	bool b2 = (b1||(carte_B->num == 14)); // +2 ou +4 sur le jeu
	bool a1 = ((carte_A->num == 10) && b1); // +2 dans la main et +2 sur le jeu
	bool a2 = ((carte_A->num == 14) && b2); // +2 ou +4 dans la main et +2 ou +4 sur le jeu
	bool a = (a1 || a2);
	bool b = (compte == 0) && (carte_A->num == carte_B->num || carte_A->color == carte_B->color || carte_A->num >= 13);
	
	return (a ? a : b); //(a || b) && !(a && b);

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
		switch(g[joueur].carte->_DATA[i]->num){
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
	// declaration de variable 
	int i; char a ; 
	int tmp = 0 ;
	
	//debug
	printf("tour %d\n",tour); 
	printf("compteur : %d\n", compte);
	affiche_carte(get_top(paquets));
	printf("\n");
	// affichage des cartes du joueur
	for (i = 0; i <joueurs[joueur_1].carte->_TOP+1; ++i){

		affiche_carte(joueurs[joueur_1].carte->_DATA[i]);
	}
	printf("\nles cartes qu'on peut jouer \n");
	
	// affichages des cartes jouables
	for (i = 0; i <joueurs[joueur_1].carte->_TOP+1; ++i)
	{
		if (can_play_carte(joueurs[joueur_1].carte->_DATA[i], get_top(paquets)) == 1 )
		{ 
			tmp++ ;
			printf("(%d:", i);
			affiche_carte(joueurs[joueur_1].carte->_DATA[i]);	
			printf(") ");
		}
		
	}

	
	// cas +N posé,joueur ne peut pas jouer
	if(compte > 0 && !tmp){
		printf("\ncas 1\n");
		printf("%s pioche %d cartes!!\n", joueurs[joueur_1].nom, compte);
		distribuer(compte,pioches,joueurs[joueur_1].carte);
		compte = 0;
		
	}
	
	// cas +N ou pas, joueur peut jouer
	else if (tmp && compte >= 0){
		printf("\ncas 2\n");
		do{
			printf("\n");
			affiche_carte(get_top(paquets));
			printf("\nQuel carte jouer?\n");
			scanf("%d",&i);

		}while(i > joueurs[joueur_1].carte->_TOP || !(can_play_carte(joueurs[joueur_1].carte->_DATA[i], get_top(paquets))));
		
		// pose la carte sur le jeu
		push(paquets, joueurs[joueur_1].carte->_DATA[i]);
		carte_remove(joueurs[joueur_1].carte,i);
		
		// applicationdes règles du jeu
		switch(get_top(paquets)->num){
			default:
				printf("normal\n");
				break;
			case 10:
				compte += 2;
			case 11 : 
				inverse();
				break ; 
			case 12 :
		 		next();
		 		break ; 
		 	case 14 :
		 		compte += 4;
		 		do {
		 			a = '\0';
		 			printf("quelle couleur ? (B,J,R,V)\n");
					scanf("%c",&a);
		 		}
		 		while(!(a == 'J' || a == 'R'|| a == 'B'|| a == 'V' ));
		 			get_top(paquets)->color = a ;
		 		break; 
		 	case 13 :
		 		do {
		 			a = '\0';
		 			printf("quelle couleur ? (B,J,R,V)\n");
					scanf("%c",&a);
		 		}
		 		while(!(a == 'J' || a == 'R'|| a == 'B'|| a == 'V' ));
		 			get_top(paquets)->color = a ;
		 		break; 
		}	
	} 
	// joueur ne peut pas jouer, pas de +N carte posé
	else{
		printf("\ncas 3\n");
		printf("%s a pioché \n",joueurs[joueur_1].nom);
		distribuer(1,pioches,joueurs[joueur_1].carte);
	}
	//printf("num : %d %d\n",i, joueurs[joueur_1].carte->_DATA[i]->num);

	// tour suivant
	//next();
	sleep(2);
	
	if(tour < 0)
		tour = 4;
}


int fin_jeux(joueur_t *g , int joueur){
	int i, j=-1, s = 0 ; 

	for (i = 0; i <joueur; ++i)
	{
		if(empty(g[joueur].carte))
			j = i ;
	}
	if(j != -1 ){
		for (i = 0; i <joueur; ++i){
			if(j !=i )
				s += G_point(g,i);
		}
	g[j].point = s ; 
	}
	return s ; 
}*/
