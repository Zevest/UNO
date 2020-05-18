#include <stdio.h>
#include <stdlib.h>

#include "carte.h"
#include "pile.h"
#include "util.h"

/// Initialise la pile de carte
extern pile_t *pile_Init()
{
	pile_t *p = malloc(sizeof(pile_t));
	p->_TOP = -1;
	return p;
}

/// Renvoie la carte au sommet de la pile
extern card_t *pile_GetTop(pile_t *p)
{
	return p->_DATA[p->_TOP];
}

/// Ajoute une carte au sommet de la pile
extern void pile_Push(pile_t *p, card_t *a)
{
	p->_DATA[++(p->_TOP)] = a;
}

/// Vérifie si la pile est vide
extern bool pile_Empty(pile_t *p)
{
	return (p->_TOP < 0);
}

/// Supprime la carte avec l'indice index de la pile
extern bool pile_Remove(pile_t *p, int index)
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
		return true;
	}
	return false;
}

/// Renvoie le premier élement de la pile
extern card_t *pile_Pop(pile_t *p)
{
	if (!pile_Empty(p))
		return p->_DATA[p->_TOP--];
	return 0;
}

/// Mélange les cartes d'un paquet source vers un paquet destination
extern void pile_Shuffle(pile_t *package, pile_t *res, int cardToSkip)
{
	int i;
	if (!pile_Empty(res))
	{
		// Vide le paquet res
		while (!pile_Empty(res))
		{
			free(pile_Pop(res));
		}
	}
	else
	{
		int mx = package->_TOP - cardToSkip;
		for (i = 0; i <= mx; ++i)
		{

			int index = rand() % (util_Max(0, (package->_TOP) + 1));

			pile_Push(res, package->_DATA[index]);
			pile_Remove(package, index);
		}

		for (i = 0; i < res->_TOP; ++i)
		{
			if (res->_DATA[i]->num <= 10)
			{
				pile_Push(package, res->_DATA[i]);
				pile_Remove(res, i);
				break;
			}
		}
	}
	if (pile_GetTop(package)->num > 9)
	{
		for (i = 0; i < res->_TOP; ++i)
		{
			if (res->_DATA[i]->num < 10)
			{
				pile_Push(package, res->_DATA[i]);
				pile_Remove(res, i);
				break;
			}
		}
	}
}

/*A TESTER*/
/// Distribue n cartes
extern bool pile_Distribute(int n, pile_t *paquet_src, pile_t *paquet_dest)
{
	int i;
	if (paquet_dest == NULL || paquet_src == NULL || n > paquet_src->_TOP)
	{
		//printf("Il n'y a pas assez de cartes dans le paquet\n");
		return true;
	}
	for (i = 0; i < n; ++i)
	{
		pile_Push(paquet_dest, pile_Pop(paquet_src));
	}
	return false;
}

/// Initialise le paquet
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

/// Libère la mémoire
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
