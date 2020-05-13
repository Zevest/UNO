#include <stdio.h>
#include <stdlib.h>

#include "../include/carte.h"
#include "../include/pile.h"

/// Retroune le max de deux valeurs a et b
int util_Max(int a, int b)
{
	return a > b ? a : b;
}

/// Initialise la pile de carte
extern pile_t *pile_Init()
{
	pile_t *p = malloc(sizeof(pile_t));
	p->_TOP = -1;
	return p;
}

/// Renvoie le sommet de la pile
extern card_t *pile_GetTop(pile_t *jeu)
{
	return jeu->_DATA[jeu->_TOP];
}

/// Ajoute une carte au sommet de la pile
extern void pile_Push(pile_t *p, card_t *a)
{
	p->_DATA[++(p->_TOP)] = a;
}

/// Vérifie si la pile est vide
extern int pile_Empty(pile_t *p)
{
	return (p->_TOP < 0);
}

/// Supprime la carte avec l'indice index de la pile
extern int pile_Remove(pile_t *p, int index)
{
	int i;
	if (index >= 0 && index < PILE_MAX)
	{
		if (p->_DATA[index] == NULL)
		{
			return 0;
		}
		for (i = index; i < p->_TOP; ++i)
		{
			p->_DATA[i] = p->_DATA[i + 1];
		}
		p->_TOP = p->_TOP - 1;
		return 1;
	}
	return 0;
}

/// Renvoie le premier element de la pile
extern card_t *pile_Pop(pile_t *p)
{
	if (!pile_Empty(p))
		return p->_DATA[p->_TOP--];
	return 0;
}

/// Mélange les cartes d'un paquets sources vers un paquets destination
extern void pile_Shuffle(pile_t *paquet, pile_t *res, int premier)
{
	int i;
	if (!pile_Empty(res))
	{
		// Vide le paquet res
		while (!pile_Empty(res))
		{
			pile_Pop(res);
		}
	}
	else
	{
		int mx = paquet->_TOP - premier;
		for (i = 0; i <= mx; ++i)
		{

			int index = rand() % (util_Max(0, (paquet->_TOP) + 1));

			pile_Push(res, paquet->_DATA[index]);
			pile_Remove(paquet, index);
		}

		for (i = 0; i < res->_TOP; ++i)
		{
			if (res->_DATA[i]->num <= 10)
			{
				pile_Push(paquet, res->_DATA[i]);
				pile_Remove(res, i);
				break;
			}
		}
	}
	if (pile_GetTop(paquet)->num > 9)
	{
		for (i = 0; i < res->_TOP; ++i)
		{
			if (res->_DATA[i]->num < 10)
			{
				pile_Push(paquet, res->_DATA[i]);
				pile_Remove(res, i);
				break;
			}
		}
	}
}

// Fonction à tester
/// distribue n cartes
extern void
pile_Distribute(int n, pile_t *paquet_src, pile_t *paquet_dest)
{
	int i;
	if (paquet_dest == NULL || paquet_src == NULL || n > paquet_src->_TOP)
	{
		printf("Il n'y a pas assez de cartes dans le paquet\n");
		return;
	}
	for (i = 0; i < n; ++i)
	{
		pile_Push(paquet_dest, pile_Pop(paquet_src));
	}
}

/// initialiser le paquet
extern void pile_FillDeck(pile_t *paquet)
{
	int i;
	if (paquet == NULL)
		return;
	for (i = 0; i <= 12; ++i)
	{
		if (i != 0)
		{
			pile_Push(paquet, card_Init(i, 'R'));
			pile_Push(paquet, card_Init(i, 'B'));
			pile_Push(paquet, card_Init(i, 'J'));
			pile_Push(paquet, card_Init(i, 'V'));
		}
		pile_Push(paquet, card_Init(i, 'R'));
		pile_Push(paquet, card_Init(i, 'B'));
		pile_Push(paquet, card_Init(i, 'J'));
		pile_Push(paquet, card_Init(i, 'V'));
	}
	for (i = 13; i < 15; ++i)
	{
		pile_Push(paquet, card_Init(i, 'N'));
		pile_Push(paquet, card_Init(i, 'N'));
		pile_Push(paquet, card_Init(i, 'N'));
		pile_Push(paquet, card_Init(i, 'N'));
	}
}

/// libère la mémoire
extern void pile_Delete(pile_t *pile)
{
	if (pile == NULL)
		return;
	while (!pile_Empty(pile))
	{
		free(pile_Pop(pile));
	}
	free(pile);
}
