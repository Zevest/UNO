#include <stdio.h>
#ifndef __UTIL_H__
#define __UTIL_H__

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
 * @param line Chaîne de caractère
 * @param l Longueure de la chaîne de caractère
 * @return 1 si elle ne contient que des chiffres sinon 0
 */
int util_IsNumeric(const char *line, int l);

/**
 * Vérifie que la chaîne de caractère soit un mot ou une phrase
 * @param line Chaîne de caractère
 * @param l Longueure de la chaîne de caractère
 * @return 1 si elle ne contient que des chiffres sinon 0
 */
int util_IsAlphaWord(const char *line, int l);

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
#endif // !__UTIL_H__