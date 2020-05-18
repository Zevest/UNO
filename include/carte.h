#ifndef __CARTE_H__
#define __CARTE_H__

/**
 * Structure d'une carte
 * Une carte contient un numero, une couleur et un symbole. 
 */
struct card
{
	/// Indice du symbole
	char num;
	/// Couleur de la carte
	char color;
	/// Symbole
	char *symbol;
};

typedef struct card card_t;

/**
 * Initialise une carte
 * @param num symbol de la carte
 * @param couleur couleur de la carte
 * @return la carte crée
 */
extern card_t *card_Init(char num, char couleur);

/**
 * Affiche une carte
 * @param carte la carte à afficher
 */
extern void card_Display(card_t *carte);

#endif // ! __CARTE_H__
