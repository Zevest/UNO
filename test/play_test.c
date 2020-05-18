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
	pile_FillDeck(deck);
	printf("\nTest: jouabilité des cartes (play.c)\n");
	printf("Test jouabilité d'une carte sur une autre identique:\n");
	for (i = 0; i < deck->_TOP; ++i)
	{
		printf("playing ::: ");
		card_Display(deck->_DATA[i]);
		printf("   on   ");
		card_Display(deck->_DATA[i]);
		assert(play_IsCardPlayable(deck->_DATA[i], deck->_DATA[i]) == 1);
		printf(" :::: Succès\n");
	}
	printf("Succès du Test 1\n");

	// Test de jouabilité d'un carte sur une autre de même couleur.
	printf("Test jouabilité d'une carte sur une autre de même couleur:\n");
	for (i = 0; i < deck->_TOP; ++i)
	{

		lastCard->color = deck->_DATA[i]->color;
		printf("playing ::: ");
		card_Display(deck->_DATA[i]);
		printf("   on   ");
		card_Display(lastCard);
		assert(play_IsCardPlayable(deck->_DATA[i], lastCard) == 1);
		printf(" :::: Succès\n");
	}
	printf("Succès du Test 2\n");

	// Test de jouabilité d'un carte sur une autre de même symbole.
	lastCard->color = 'R';
	printf("Test jouabilité d'une carte sur une autre de même symbole:\n");
	for (i = 0; i < deck->_TOP; ++i)
	{
		lastCard->num = deck->_DATA[i]->num;
		printf("playing ::: ");
		card_Display(deck->_DATA[i]);
		printf("   on   ");
		card_Display(lastCard);
		assert(play_IsCardPlayable(deck->_DATA[i], lastCard) == 1);
		printf(" :::: Succès\n");
	}
	printf("Succès du Test 3\n");

	// Test de jouabilité d'un carte sans couleur une carte de couleur.
	lastCard->color = 'R';
	printf("Test jouabilité d'une carte sans couleur une carte de couleur:\n");
	for (i = 0; i < deck->_TOP; ++i)
	{
		if (deck->_DATA[i]->color != 'N')
			lastCard->color = deck->_DATA[i]->color;
		else
		{
			printf("playing ::: ");
			card_Display(deck->_DATA[i]);
			printf("   on   ");
			card_Display(lastCard);
			assert(play_IsCardPlayable(deck->_DATA[i], lastCard) == 1);
			printf(" :::: Succès\n");
		}
	}
	printf("Succès du Test 4\n");

	pile_Delete(deck);
	free(lastCard);
	return 0;
}