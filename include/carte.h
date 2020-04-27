#ifndef __CARTE_H__
#define __CARTE_H__

static char *SYMBOL[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "+2", "inverse", "passe", "joker", "+4"};

struct card
{
	char num;
	char color;
	char *symbol;
};

typedef struct card card_t;

// initialise une Carte
extern card_t *card_Init(char num, char couleur);
extern void card_Display(card_t *);

#endif // ! __CARTE_H__
