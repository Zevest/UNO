#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "include/csvloader.h"

/// Charge un fichier csv
csv_t *initCSV(FILE *f)
{
	csv_t *input;
	if (f == NULL)
	{
		fprintf(stderr, "File Not found\n");
		exit(EXIT_FAILURE);
	}
	int lines = countLine(f);
	input = (csv_t *)malloc(sizeof(*input));
	input->length = lines;
	input->data = (data_t *)malloc(lines * sizeof(input->data[0]));
}

/// Libere la memoire
void deleteCSV(csv_t *csv)
{
	free(csv->data);
	csv->data = NULL;
	free(csv);
}

/// Compte le nombre de ligne dans un ficher
int countLine(FILE *f)
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
/// Sépare les données du ficher et les stocke dans un objet
csv_t *parseCSV(const string_t filename, csv_t *input)
{
	csv_t *tmp = NULL;
	string_t token = "";
	char buf[__CSV_BUFFER_SIZE__] = "";
	FILE *stream = fopen(filename, "r");
	if (!stream)
	{
		fclose(stream);
		return NULL;
	}

	tmp = initCSV(stream);

	for (int i = 0; i < tmp->length; ++i)
	{
		fgets(buf, sizeof(buf), stream);
		token = strtok(buf, ",");
		tmp->data[i].index = atoi(token);
		token = strtok(NULL, "£");
		strcpy(tmp->data[i].message, token);
	}

	fclose(stream);

	if (input == NULL)
		return tmp;

	input = tmp;
	return tmp;
}

/// Affiche le contenue d'une donnée (ligne d'un fichier csv)
void printData(data_t *d)
{
	if (d != NULL)
		printf("%d:%s", d->index, d->message);
	else
		printf("%p", d);
}

/// Affiche les donnée stocker dans l'objet
void printCSV(csv_t *csv, dataPrinter printer)
{
	if (csv != NULL)
	{
		printf("{\n");
		for (int i = 0; i < csv->length; ++i)
		{
			printf("	");
			printer((csv->data + i));
			printf(",\n");
		}
		printf("}\n");
	}
}

/// Affiche n fois le caractere de fin de ligne
void jumpLine(int n)
{
	while (n-- > 0)
		printf("\n");
}

#ifdef DEBUG
int main()
{
	csv_t *csv = parseCSV("Message.csv", NULL);
	printData(&csv->data[0]);
	deleteCSV(csv);
}
#endif // DEBUG
