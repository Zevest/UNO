#include <stdio.h>
#include <stdlib.h>
#include "carte.h"

int main(){

	printf("Hello world!");
	printf("Yess!!");
	
	carte_t *  c = init_carte(13, 'R');
	printf("\ncarte %c %s\n", c->color, c->symbol);
	free(c);
	return 0;
}


