#ifndef __CSVLOADER_H__
#define __CSVLOADER_H__

#define __CSV_BUFFER_SIZE__ 256

typedef char *string_t;
/**
 * Structure d'une lingne de donnée d'un fichier csv.
 * Ici l'index est n'utilisé Le message correspond à l'affichage durant la partie.
 */
typedef struct data
{
	int index;
	char message[__CSV_BUFFER_SIZE__];
} data_t;

/**
 * Structure d'un fichier csv.
 * Il s'agit simplement d'un vecteur de donnée et avec le nombre d'éléments.
 */
typedef struct csv
{
	int length;
	data_t *data;
} csv_t;

typedef void (*dataPrinter)(data_t *);

/**
 * Traite les données du fichier csv et les stocke dans la structure.
 * @param filename nom du fichier.
 * @param input object concerner.
 * @return l'objet creer si input est null, sinon input.
 */
csv_t *csv_ParseCSV(string_t filename, csv_t *input);

/**
 * Initialise un objet CSV a partire d'un fichier.
 * @param f le a charger.
 */
csv_t *csv_InitCSV(FILE *f);

/**
 * Libere la memoire d'un objet csv.
 * @param csv l'objet a supprimer.
 */
void csv_DeleteCSV(csv_t *csv);
/**
 * Libere la mémoire d'une donnée csv.
 * @param data la donnée a suprimmer.
 */
void csv_DeleteData(data_t *data);

/**
 * Affiche une ligne de donnée d'un fichier csv.
 * @param d la ligne de donnée.
 */
void csv_PrintData(data_t *d);

/**
 * Affiche le contenu d'un fichier CSV.
 * @param csv l'objet dans le quel sont stocker les données.
 * @param printer fonction d'affichage des données.
 */
void csv_PrintCSV(csv_t *csv, dataPrinter printer);

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
#endif // __CSVLOADER_H__