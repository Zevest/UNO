#ifndef __CSVLOADER_H__
#define __CSVLOADER_H__

#define __CSV_BUFFER_SIZE__ 256

typedef char *string_t;
typedef struct data
{
	int index;
	char message[__CSV_BUFFER_SIZE__];
} data_t;

typedef struct csv
{
	int length;
	data_t *data;
} csv_t;

typedef void (*dataPrinter)(data_t *);

csv_t *parseCSV(string_t filename, csv_t *input);
csv_t *initCSV(FILE *f);
void deleteCSV(csv_t *csv);
void deleteData(data_t *data);
void printData(data_t *d);
void printCSV(csv_t *csv, dataPrinter);
int countLine(FILE *f);
void jumpLine(int n);

#endif // __CSVLOADER_H__