#include <carte.h>

carte_t initCarte(char num, char color){
	if(num >= 0  && num < 15){
		carte_t * c = malloc(sizeof carte_t);
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

