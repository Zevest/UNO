#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "util.h"
#include "csvloader.h"

/*A TESTER*/
/// Charge un fichier csv
csv_t *csv_InitCSV(FILE *f)
{
	csv_t *input;
	if (f == NULL)
	{
		fprintf(stderr, "File Not found\n");
		//exit(EXIT_FAILURE);
		return NULL;
	}
	int lines = util_CountLine(f);
	input = (csv_t *)malloc(sizeof(*input));
	input->length = lines;
	input->data = (data_t *)malloc(lines * sizeof(input->data[0]));
	return input;
}

/// Libère la memoire
void csv_DeleteCSV(csv_t *csv)
{
	if (csv == NULL)
		return;
	if (csv->data != NULL)
		free(csv->data);
	csv->data = NULL;
	free(csv);
}

/*A TESTER*/
/// Sépare les données du fichier et les stocke dans un objet
csv_t *csv_ParseCSV(const string_t filename, csv_t *input)
{
	csv_t *tmp = NULL;
	string_t token = "";
	char buf[__CSV_BUFFER_SIZE__] = "";
	FILE *stream = fopen(filename, "r");
	if (stream == NULL)
	{
		fprintf(stderr, "Impossible de trouver le fichier %s.\n", filename);
		return NULL;
	}

	tmp = csv_InitCSV(stream);

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

/// Affiche le contenu d'une donnée (ligne d'un fichier csv)
void csv_PrintData(data_t *d)
{
	if (d != NULL)
		printf("%d:%s", d->index, d->message);
	else
		printf("%p", d);
}

/// Affiche les données stockées dans l'objet
void csv_PrintCSV(csv_t *csv, dataPrinter printer)
{
	if (csv == NULL)
		return;
	printf("{\n");
	for (int i = 0; i < csv->length; ++i)
	{
		printf("	");
		printer((csv->data + i));
		printf(",\n");
	}
	printf("}\n");
}

#ifdef DEBUG
int main()
{
	csv_t *csv = csv_ParseCSV("Message.csv", NULL);
	csv_PrintData(&csv->data[0]);
	csv_DeleteCSV(csv);
}
#endif // DEBUG
