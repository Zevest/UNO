#include "carte.h"

#ifndef __PILE_H__
#define __PILE_H__
#define PILE_MAX 256
struct pile
{
	int _TOP;
	card_t *_DATA[PILE_MAX];
};

typedef enum
{
	false,
	true
} bool;

typedef struct pile pile_t;

extern pile_t *pile_Init(void);
extern void pile_Push(pile_t *, card_t *);
extern card_t *pile_Pop(pile_t *);
extern int pile_Remove(pile_t *, int);
extern int pile_Empty(pile_t *);
extern card_t *pile_GetTop(pile_t *jeu);

extern void pile_FillDeck(pile_t *paquet);
extern void pile_Distribute(int, pile_t *src, pile_t *dest);
extern void pile_Shuffle(pile_t *paquet, pile_t *res, int premier);

#endif
