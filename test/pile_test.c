#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "carte.h"
#include "pile.h"

/// Copie une carte
void card_Copy(card_t *dest, card_t *src)
{
	if (dest == NULL || src == NULL)
		return;
	dest->num = src->num;
	dest->color = src->color;
	dest->symbol = src->symbol;
}

/// Compare deux cartes
int card_Comp(card_t *cardA, card_t *cardB)
{
	if (cardA == NULL || cardB == NULL)
		return 0;
	return (cardA->num == cardB->num &&
			cardA->color == cardB->color &&
			cardA->symbol == cardB->symbol);
}

int main()
{
	// Initialisation d'un paquet
	// Initialisation de distribution de 1 carte;
	pile_t *paquetSrc;
	pile_t *paquetDest;
	card_t before;
	int i, j;

	for (j = 1; j < 11; ++j)
	{
		paquetSrc = pile_Init();
		paquetDest = pile_Init();
		pile_FillDeck(paquetSrc);
		printf("Test de distribution de %d carte(s): ", j);
		for (i = 0; i < 10; ++i)
		{
			card_Copy(&before, paquetSrc->_DATA[paquetSrc->_TOP - (j - 1)]);
			pile_Distribute(j, paquetSrc, paquetDest);
			assert(card_Comp(&before, pile_GetTop(paquetDest)));
		}
		printf("Succès\n");
		pile_Delete(paquetDest);
		pile_Delete(paquetSrc);
	}
	return 0;
}