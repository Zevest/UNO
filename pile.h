#include "carte.h"

#ifndef __PILE_H__
#define __PILE_H__
#define PILE_MAX 256
struct pile{
	int _TOP;
	carte_t * _DATA[PILE_MAX];
};

typedef struct pile pile_t;


extern pile_t * init_pile(void);
extern void push(pile_t *, carte_t *);
extern carte_t * pop(pile_t *);
extern int carte_remove(pile_t *, int);
extern int empty(pile_t *);
extern carte_t * get_top(pile_t * jeu);

extern void remplir_paquet(pile_t * paquet);
extern void distribuer(int, pile_t * src, pile_t * dest);
extern void melange(pile_t * paquet, pile_t * res, int premier);



#endif
