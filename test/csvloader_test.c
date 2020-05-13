#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "csvloader.h"
#include "util.h"

int main(int argc, char **argv)
{

	FILE *stream;

	csv_t *csv;
	int index[] = {0, 1, 150, 3, 4}, i;
	char *messages[] = {
		"ceci est un example contenant une longue phrase afin de conaitre les limite",
		"test2",
		" test avec grand nombre",
		"test avec \\n retour a la ligne",
		"test avec argument 5 + 5 = %d !"};
	if (argc < 2)
		stream = fopen("res/test.csv", "r");
	else
		stream = fopen(argv[1], "r");
	// Test de chargement de fichier non existant
	printf("Test de chargement de fichier non existant: ");
	csv = csv_InitCSV(NULL);
	assert(csv == NULL);
	printf("Succès\n");
	// Test de chargement de fichier existant
	printf("Test de chargement de fichier existant: ");
	csv = csv_InitCSV(stream);
	assert(csv != NULL);
	printf("Succès\n");

	// Test du compte du nombre de ligne du fichier
	printf("Test du compte de nombre de ligne d'un fichier: ");
	assert(util_CountLine(stream) == 5);
	assert(csv->length == 5);
	printf("Succès\n");

	fclose(stream);
	csv_DeleteCSV(csv);

	// Test traitement du fichier test.csv
	printf("Test de traitement du fichier text.csv: ");
	csv = csv_ParseCSV("res/test.csv", NULL);
	printf("Succès\n");

	// Test de validité des données chargé
	// Indices
	printf("Test de validité des indices chargés: ");
	for (i = 0; i < 5; ++i)
	{
		assert(csv->data[i].index == index[i]);
	}
	printf("Succès\n");
	// Messages
	printf("Test de validité des messages chargés: ");
	for (i = 0; i < 5; ++i)
	{
		assert(strcmp(csv->data[i].message, messages[i]) == 0);
	}
	printf("Succès\n");
	csv_DeleteCSV(csv);
	return 0;
}