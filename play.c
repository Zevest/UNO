#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include"pile.h"
#include"carte.h"
#include"joueur.h"
#include "play.h"
#define N 13 

static int sens = 1; // Sens du deroulement de la partie
static int tour = 0; // Le nombre de mains passé
static int compte = 0; // Comptabilise le nombre de cartes a piocher apres le +2 ou/et +4 

void next(){    // passe au tour suivant
	tour += sens;
}

int getTour(){  // renvoie la valeur des tours jouer
	return tour;
}

void setTour(int n){  // modifie la valeur de tour
	tour = n;
}

void inverse(){  // change de sens
	sens *= -1;
}
int can_play_carte(carte_t * carte_A , carte_t * carte_B){  // verifie si la carte peut etre jouer
	
	bool b1 = (carte_B->num == 10) ; // +2 sur le jeu
	bool b2 = (b1||(carte_B->num == 14)); // +2 ou +4 sur le jeu
	bool a1 = ((carte_A->num == 10) && b1); // +2 dans la main et +2 sur le jeu
	bool a2 = ((carte_A->num == 14) && b2); // +2 ou +4 dans la main et +2 ou +4 sur le jeu
	bool a = (a1 || a2);
	bool b = (compte == 0) && (carte_A->num == carte_B->num || carte_A->color == carte_B->color || carte_A->num >= 13);
	
	return (a ? a : b); 

}


int can_play(pile_t * main , carte_t * carte){  // verifie si un joueur peut jouer
	int i ;

	for (i = 0; i < main->_TOP + 1 ; ++i)
	{
		if(can_play_carte( main->_DATA[i], carte))
			return 1 ;
	}
	return 0 ;
}
 
int G_point(joueur_t *g, int joueur){  // compte le nombre de points d'un joueur
	int i ; 
	int s =  0; 

	for (i = 0; i < g[joueur].carte->_TOP+1; i++)	{
		switch(g[joueur].carte->_DATA[i]->num){
			default : 
				s += g[joueur].carte->_DATA[i]->num ; 
				break;
			case 10 : 
			case 11 : 
			case 12 : 
				s += 20 ;
				break;
			case 13 :
			case 14 : 
				s += 50 ; 
				break;  
		}
	
	}
	return s ;
}
int fin_jeux(joueur_t *g , int joueur){  //additionne les points des perdant pour les atribuer au gagnant 
	int i, j=-1, s = 0 ; 

	for (i = 0; i <joueur; ++i)
	{
		if(empty(g[i].carte))
			j = i;
	}
	if(j != -1 ){
		
		for (i = 0; i <joueur; ++i){
			if(j !=i )
				s += G_point(g,i);
		}
		g[j].point += s ; 
	}
	return g[j].point; 
}
// boucle principale du jeu
int play(joueur_t *joueurs , pile_t * paquets , pile_t * pioches, int joueur_1, int nb){  
	int i; char a ; 
	int tmp = 0 ;
	
	
	// affiche les cartes du joueur
	for (i = 0; i <joueurs[joueur_1].carte->_TOP+1; ++i){

		affiche_carte(joueurs[joueur_1].carte->_DATA[i]);
		printf(" ");
	}
	printf("\n\nTable :");
	affiche_carte(get_top(paquets));

	
	printf("\n\nles cartes qu'on peut jouer => ");
	
	// affiche les cartes jouables
	for (i = 0; i <joueurs[joueur_1].carte->_TOP+1; ++i)
	{
		if (can_play_carte(joueurs[joueur_1].carte->_DATA[i], get_top(paquets)) == 1 )
		{ 
			tmp++ ;
			printf("(%d: ", i);
			affiche_carte(joueurs[joueur_1].carte->_DATA[i]);	
			printf(") ");
		}
		
	}

	
    // +2 ou/et +4 et le joueur n'a pas de +2 ni de +4 donc il est obligé de piocher  
	if(compte > 0 && !tmp){
		printf("%s pioche %d cartes!!\n", joueurs[joueur_1].nom, compte);
		distribuer(compte,pioches,joueurs[joueur_1].carte);
		compte = 0;
		
	}
	
    // +2 ou/et +4 et le joueur possède +2/+4 donc il peut jouer 
	else if (tmp && compte >= 0){
		do{

			printf("\n\nQuel carte jouer?\n");
			scanf("%d",&i);

		}while(i > joueurs[joueur_1].carte->_TOP || !(can_play_carte(joueurs[joueur_1].carte->_DATA[i], get_top(paquets))));
		
		// pose la carte sur le jeu
		push(paquets, joueurs[joueur_1].carte->_DATA[i]);
		carte_remove(joueurs[joueur_1].carte,i);
		
		// applicationdes règles du jeu
		switch(get_top(paquets)->num){
			default:
				break;
			case 10:
				compte += 2;
			case 11 : 
				inverse();
				break ; 
			case 12 :
				printf("oups ton tour est passé \n");
		 		next();
		 		sleep(1);
		 		break ; 
		 	case 14 :
		 		compte += 4;
		 		printf("quelle couleur ? (B,J,R,V)\n");
		 		do {
		 		
		 			a = '\0';
		 		
					scanf("%c",&a);
		 		}
		 		while(!(a == 'J' || a == 'R'|| a == 'B'|| a == 'V' ));
		 			get_top(paquets)->color = a ;
		 		break; 
		 	case 13 :
		 		printf("quelle couleur ? (B,J,R,V)\n");
		 		do {
		 			a = '\0';
		 			
					scanf("%c",&a);
		 		}
		 		while(!(a == 'J' || a == 'R'|| a == 'B'|| a == 'V' ));
		 			get_top(paquets)->color = a ;
		 		break; 
		}	
	} 
	// le joueur n'a pas de cartes a joué, il doit piocher
	else{
		printf("%s a pioché \n",joueurs[joueur_1].nom);
		distribuer(1,pioches,joueurs[joueur_1].carte);
		sleep(1);
	}

	// tour suivant
	if(empty(joueurs[joueur_1].carte)){
		printf("point %d\n", fin_jeux(joueurs, nb));
		return joueurs[joueur_1].point;
	}
	
	next();
	
	if(tour < 0)
		tour = 4;
	return 0;
}



