#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "carte.h"
#include "play.h"
#include "pile.h"

int main()
{
	// Test de la fonction play_IsCardPlayable avec divers configuration
	int i;
	pile_t *deck = pile_Init();
	card_t *lastCard = card_Init(0, 'R');
	printf("Test jouabilité d'une carte sur une autre identique: ");
	for (i = 0; i < deck->_TOP; ++i)
	{
		assert(play_IsCardPlayable(deck->_DATA[i], deck->_DATA[i]) == 1);
	}
	printf("Succès\n");

	// Test de jouabilité d'un carte sur une autre de même couleur.
	printf("Test jouabilité d'une carte sur une autre de même couleur: ");
	for (i = 0; i < deck->_TOP; ++i)
	{
		lastCard->color = deck->_DATA[i]->color;
		assert(play_IsCardPlayable(deck->_DATA[i], lastCard) == 1);
	}
	printf("Succès\n");

	// Test de jouabilité d'un carte sur une autre de même symbole.
	lastCard->color = 'R';
	printf("Test jouabilité d'une carte sur une autre de même symbole: ");
	for (i = 0; i < deck->_TOP; ++i)
	{
		lastCard->num = deck->_DATA[i]->num;
		assert(play_IsCardPlayable(deck->_DATA[i], lastCard) == 1);
	}
	printf("Succès\n");

	// Test de jouabilité d'un carte sans couleur une carte de couleur.
	lastCard->color = 'R';
	printf("Test jouabilité d'une carte sans couleur une carte de couleur: ");
	for (i = 0; i < deck->_TOP; ++i)
	{
		if (deck->_DATA[i]->color != 'N')
			lastCard->color = deck->_DATA[i]->color;
		else
			assert(play_IsCardPlayable(deck->_DATA[i], lastCard) == 1);
	}
	printf("Succès\n");

	pile_Delete(deck);
	free(lastCard);
	return 0;
}