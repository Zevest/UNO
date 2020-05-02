#include <stdio.h>
#include <stdlib.h>
#include "include/carte.h"

/// Liste des symboles des cartes.
static char *SYMBOL[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "+2", "inverse", "passe", "joker", "+4"};

/**
 * Escape sequence :\033
 *
 * Code couleurs
 * [0;31m	Red
 * [1;31m	Bold Red
 * [0;32m	Green
 * [1;32m	Bold Green
 * [0;33m	Yellow
 * [01;33m	Bold Yellow
 * [0;34m	Blue
 * [1;34m	Bold Blue
 * [0;35m	Magenta
 * [1;35m	Bold Magenta
 * [0;36m	Cyan
 * [1;36m	Bold Cyan
 * [0m	Reset
 */

static inline void red() { printf("\033[0;31m"); }
static inline void boldRed() { printf("\033[1;31m"); }
static inline void green() { printf("\033[0;32m"); }
static inline void boldGreen() { printf("\033[1;32m"); }
static inline void blue() { printf("\033[0;34m"); }
static inline void boldBlue() { printf("\033[1;34m"); }
static inline void yellow() { printf("\033[0;33m"); }
static inline void boldYellow() { printf("\033[1;33m"); }
static inline void resetColor() { printf("\033[0m"); }
static inline void bold() { printf("\033[1;0m"); }

/// Initialise une carte
card_t *card_Init(char num, char color)
{
	if (num >= 0 && num < 15)
	{
		card_t *c = malloc(sizeof(card_t));
		c->num = num;
		if (num > 12)
			c->color = 'N';
		else
			c->color = color;
		c->symbol = *(SYMBOL + num);
		return c;
	}
	return NULL;
}

/// Afficche une carte
void card_Display(card_t *c)
{
	switch (c->color)
	{
	case 'R':
		boldRed();
		break;
	case 'V':
		boldGreen();
		break;
	case 'B':
		boldBlue();
		break;
	case 'J':
		boldYellow();
		break;
	default:
		bold();
	}
	printf("[%s %c]", c->symbol, c->color);
	resetColor();
}
