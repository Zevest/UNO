	#include <stdio.h>
#include <stdlib.h>
#include "carte.h"

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

char * affiche_carte(carte_t * c){
	char * text;
	sprintf(text, "[%s %c]", c->symbol, c->color);
	return text;
}
