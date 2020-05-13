#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "util.h"

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

/// Affiche n fois le caractere de fin de ligne
void util_JumpLine(int n)
{
	while (n-- > 0)
		printf("\n");
}

/// Vérifie si une chaîne de caratère est un nombre
int util_IsNumeric(const char *line, int l)
{
	while (l-- >= 0)
		if (isdigit(line[l - 1]))
			return 0;
	return 1;
}

/// Vérifie si une chaîne de caratère ne contient que des lettres
int util_IsAlphaWord(const char *line, int l)
{
	while (l-- >= 0)
		if (!isalpha(line[l - 1]))
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

/// Retroune le max de deux valeurs a et b
int util_Max(int a, int b)
{
	return a > b ? a : b;
}