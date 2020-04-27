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
csv_t *parseCSV(string_t filename, csv_t *input);

/**
 * Initialise un objet CSV a partire d'un fichier.
 * @param f le a charger.
 */
csv_t *initCSV(FILE *f);

/**
 * Libere la memoire d'un objet csv.
 * @param csv l'objet a supprimer.
 */
void deleteCSV(csv_t *csv);
/**
 * Libere la mémoire d'une donnée csv.
 * @param data la donnée a suprimmer.
 */
void deleteData(data_t *data);

/**
 * Affiche une ligne de donnée d'un fichier csv.
 * @param d la ligne de donnée.
 */
void printData(data_t *d);

/**
 * Affiche le contenu d'un fichier CSV.
 * @param csv l'objet dans le quel sont stocker les données.
 * @param printer fonction d'affichage des données.
 */
void printCSV(csv_t *csv, dataPrinter printer);

/**
 * Compte le nombre de ligne d'un fichier.
 * @param f Fichier
 */
int countLine(FILE *f);

/**
 * Permet d'afficher n fois le carater fin de ligne.
 * @param n nombre de répétition
 */
void jumpLine(int n);

#endif // __CSVLOADER_H__