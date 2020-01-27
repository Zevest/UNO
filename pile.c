#include <stdio.h>
#include <stdlib.h>

#include "carte.h"
#include "pile.h"


int max(int a, int b){
	return a > b ? a: b;
}

extern pile_t * init_pile(){
	pile_t * p = malloc(sizeof (pile_t));
	p->_TOP = -1;
	return p;
}
extern carte_t * get_top(pile_t * jeu){
	return jeu->_DATA[jeu->_TOP];
}

extern void push(pile_t * p, carte_t * a){
	p->_DATA[++(p->_TOP)] = a;
}

extern int empty(pile_t * p){
	return (p->_TOP < 0);
}

extern int carte_remove(pile_t *p, int index){
	int i;
	if(index >= 0 && index < PILE_MAX){
		if(p->_DATA[index] == NULL){
			return 0;
		}
		for(i = index; i < p->_TOP; ++i){
			p->_DATA[i] = p->_DATA[i+1];
		}
		p->_TOP = p->_TOP - 1;
		return 1;
	}
	return 0;
}

extern carte_t * pop(pile_t * p){
	if(!empty(p))
		return p->_DATA[p->_TOP--];
	return 0;
}


extern void melange(pile_t * paquet, pile_t * res, int premier){
	int i;
	if(!empty(res)){
		// Vider le paquet res
		while(!empty(res)){
			pop(res);
		}
	}else{
		int mx = paquet->_TOP;
		for(i = 0; i <= mx; ++i){
 		
			int index = rand() % max(1, (paquet->_TOP));
		
			push(res, paquet->_DATA[index]);
			carte_remove(paquet, index);
		}
		
		for(i = 0; i < res->_TOP; ++i){
			if(res->_DATA[i]->num <= 10){
				push(paquet, res->_DATA[i]);
				carte_remove(res, i);
				break;
			}
		}		
	}
}


extern void distribuer(int n, pile_t * paquet_src, pile_t * paquet_dest){
	int i;
	if(paquet_dest == NULL || paquet_src == NULL || n > paquet_src->_TOP){
		printf("Il n'y a pas assé de cartes dans le paquet\n");
		return;
	}
	for(i = 0; i < n; ++i){
		push(paquet_dest, pop(paquet_src));
	}
}

extern void remplir_paquet(pile_t * paquet){
	int i;
	if(paquet == NULL)
		return;
	for(i = 0; i <= 12; ++i){
		if(i != 0){
			push(paquet,init_carte(i, 'R'));
			push(paquet,init_carte(i, 'B'));
			push(paquet,init_carte(i, 'J'));
			push(paquet,init_carte(i, 'V'));
		}
		push(paquet,init_carte(i, 'R'));
		push(paquet,init_carte(i, 'B'));
		push(paquet,init_carte(i, 'J'));
		push(paquet,init_carte(i, 'V'));
	}
	for(i = 13; i < 15; ++i){
		push(paquet,init_carte(i, 'N'));
		push(paquet,init_carte(i, 'N'));
		push(paquet,init_carte(i, 'N'));
		push(paquet,init_carte(i, 'N'));
	}
}

