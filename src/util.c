#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "util.h"

/*A TESTER*/
/// Compte le nombre de ligne dans un ficher
int util_CountLine(FILE *f)
{
	if (f == NULL)
		return 0;
	int lines = 0;
	char c;
	while (!feof(f))
	{
		c = fgetc(f);
		if (c == '\n')
		{
			++lines;
		}
	}
	rewind(f);
	return lines;
}

/// Affiche n fois le caractère de fin de ligne
void util_JumpLine(int n)
{
	while (n-- > 0)
		printf("\n");
}

/// Vérifie si une chaîne de caratère est un nombre
int util_IsNumeric(const string_t buffer)
{
	char *ptr = buffer;
	while (ptr && *ptr != '\n')
		if (!isdigit(*ptr++))
			return 0;
	return 1;
}

/// Vérifie si une chaîne de caratère ne contient que des lettres
int util_IsAlphaWord(const string_t buffer)
{
	char *ptr = buffer;
	while (ptr && *ptr != '\n')
		if (!isalpha(*ptr++))
			return 0;
	return 1;
}

/// Vide le buffer stdin
void util_ClearInputBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
}

/// Retroune la valeur maximum entre deux valeurs a et b
int util_Max(int a, int b)
{
	return a > b ? a : b;
}

/// Affiche un message et attend la saisie d'une donnée conforme à une condition
void util_Ask(const string_t message, string_t buffer, stringValidator_t validator)
{
	do
	{
		printf(message, NULL);
		fgets(buffer, sizeof(buffer), stdin);
	} while (!validator(buffer));
}