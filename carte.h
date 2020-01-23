#ifndef __CARTE_H__
#define __CARTE_H__

static char ** SYMBOL {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "+2", "inverse", "passe", "joker", "+4"};

struct carte {
	char num;
	char color;
	char * symbol;
}

typedef carte carte_t;

// initialise une Carte
carte_t initCarte(char num, char couleur);


#endif // ! __CARTE_H__

