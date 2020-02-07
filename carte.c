#include <stdio.h>
#include <stdlib.h>
#include "carte.h"



// Initialise une carte
carte_t * init_carte(char num, char color){	
	if(num >= 0  && num < 15){
		carte_t * c = malloc(sizeof (carte_t));
		c->num = num;
		if(num > 12)
			c->color = 'N';
		else
			c->color = color;
		c->symbol = SYMBOL[num];
		return c;
	}
	return NULL;
}

void affiche_carte(carte_t * c){
	printf("[%s %c]", c->symbol, c->color);

}
