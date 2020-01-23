#include "carte.h"
#include "pile.h"
#include <stdlib.h>

extern pile_t * init_pile(){
	pile_t * p = malloc(sizeof (pile_t));
	p->_TOP = -1;
	return p;
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


