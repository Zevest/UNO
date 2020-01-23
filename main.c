#include <stdio.h>
#include <stdlib.h>
#include "carte.h"
#include "pile.h"


int max(int a, int b){
	return a > b ? a: b;
}

void melange(pile_t * paquet, pile_t * res, int premier){
	int useless;
	if(!empty(res)){
		//vider le paquet res
		while(!empty(res)){
			pop(res);
		}
	}else{
		int mx = paquet->_TOP;
		for(useless = 0; useless <= mx; ++useless){

			int index = rand() % max(1, (paquet->_TOP-premier));
			push(res, paquet->_DATA[index]);
			carte_remove(paquet, index);
		}
	}
}

int main(){
	pile_t * paquet = init_pile();
	int i, j = 0;
	for(i = 0; i <= 12; ++i){
		if(i != 0){
			push(paquet,init_carte(i, 'R'));
			j++;
			push(paquet,init_carte(i, 'B'));
			j++;
			push(paquet,init_carte(i, 'J'));
			j++;
			push(paquet,init_carte(i, 'V'));
			j++;
		}
		push(paquet,init_carte(i, 'R'));
		j++;
		push(paquet,init_carte(i, 'B'));
		j++;
		push(paquet,init_carte(i, 'J'));
		j++;
		push(paquet,init_carte(i, 'V'));
		j++;
	}
	for(i = 13; i < 15; ++i){
		push(paquet,init_carte(i, 'N'));
		j++;
		push(paquet,init_carte(i, 'N'));
		j++;
		push(paquet,init_carte(i, 'N'));
		j++;
		push(paquet,init_carte(i, 'N'));
		j++;
	}
	
	pile_t * pioche = init_pile();
	melange(paquet, pioche, 0);
	
	printf("\n\n%d  paquet\n", j);
	for(i = 0; i < paquet->_TOP+1; ++i){
		printf("%s %c\n", paquet->_DATA[i]->symbol, paquet->_DATA[i]->color);
	}
	printf("\npioche\n");
	for(i = 0; i < pioche->_TOP-3; ++i){
		printf("%s %c\n", pioche->_DATA[i]->symbol, pioche->_DATA[i]->color);
	}
	
	//carte_t *  c = init_carte(13, 'R');
	//printf("\ncarte %c %s\n", c->color, c->symbol);
	//free(c);
	return 0;
}


