#include <stdio.h>
#ifndef __UTIL_H__
#define __UTIL_H__
/**
 * Chaine de charactère
 */
typedef char *string_t;

typedef int (*stringValidator_t)(string_t);

typedef enum
{
	false,
	true
} bool;

/**
 * Compte le nombre de ligne d'un fichier.
 * @param f Fichier
 */
int util_CountLine(FILE *f);

/**
 * Permet d'afficher n fois le caratère fin de ligne.
 * @param n nombre de répétition
 */
void util_JumpLine(int n);

/**
 * Vérifie que la chaîne de caractère soit un nombre
 * @param buffer Chaîne de caractère
 * @return 1 si elle ne contient que des chiffres sinon 0
 */
int util_IsNumeric(const string_t buffer);

/**
 * Vérifie que la chaîne de caractère soit un mot ou une phrase
 * @param buffer Chaîne de caractère
 * @return 1 si elle ne contient que des chiffres sinon 0
 */
int util_IsAlphaWord(const string_t buffer);

/**
 * Vide le buffer stdin jusqu'à la fin de la ligne ou du buffer
 */
void util_ClearInputBuffer();

/**
 * Cherche le plus grand entier entre les deux valeurs fournies
 * @param a un entier
 * @param b un entier
 * @return la valeur la plus grande
 */
int util_Max(int a, int b);

/**
 * Affiche un message avant de récuperer la saisie de l'utilisateur tant quelle ne correspoind pas a la valeur demandé
 * @param message le message afficher avant la saisie de donnée
 * @param buffer buffer dans lequel stocker l'information
 * @param validator vérificateur de la donnée
 */
void util_Ask(const string_t message, string_t buffer, stringValidator_t validator);
#endif // !__UTIL_H__