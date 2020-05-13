#include "carte.h"
#ifndef __PILE_H__
#define __PILE_H__
#define PILE_MAX 256

/**
 * Structure de pile
 * Contient l'indice du sommet du paquet.
 * Un vecteur de carte_t.
 * Il sagit d'un paquet de carte utilisé comme pioche et main des joueurs.
 */
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

/**
 * Initialise la Pile.
 * @return Pile crée
 */
extern pile_t *pile_Init(void);
/**
 * Ajoute un carte ausommet de la pile.
 * @param p pile
 * @param c carte à ajouter
 */
extern void pile_Push(pile_t *p, card_t *c);

/**
 * Retire une carte du sommet de la pile.
 * @param p pile
 * @return carte retirer.
 */
extern card_t *pile_Pop(pile_t *p);

/**
 * Retire une carte d'indice i de la pile.
 * @param p pile
 * @param indice de la carte
 * @return 1 si la carte a bien été retirer 0 sinon.
 */
extern int pile_Remove(pile_t *p, int i);

/**
 * Verifie si la pile est vide.
 * @param p pile
 * @return 1 si la pile est vide, 0 sinon.
 */
extern int pile_Empty(pile_t *p);

/**
 * Recupere la carte au sommet de la pile.
 * @param p pile
 * @return carte au sommet
 */
extern card_t *pile_GetTop(pile_t *p);
/**
 * Remplie la pile deu bon nombre de chaque carte.
 * @param p pile
 */
extern void pile_FillDeck(pile_t *p);

/**
 * Déplace N carte(s) de la pile source vers la pile destination.
 * @param n nombre de carte a déplacer
 * @param src pile source
 * @param dst pile destination
 */
extern void pile_Distribute(int n, pile_t *src, pile_t *dest);

/**
 * Déplace et mélange les cartes de la pile source vers la pile destination.
 * Les cartes dont l'indice est inférieur n sont ignorées.
 * @param src pile source
 * @param dst pile destination
 * @param n nombre de carte à laisser
 */
extern void pile_Shuffle(pile_t *src, pile_t *dst, int n);

/**
 * Libère la mémoire allouée pour pour la pile
 * @param pile la pile a supprimer
 */
extern void pile_Delete(pile_t *pile);
#endif
