#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct Data {
    char *name;
    char *(*headers)[];
    char *(*labels)[];
    double (*dataPoints)[];
};

void printFiles(FILE *storage, int64_t rows, int64_t columns, char buff[]);

// Gets phenotype data from phenotype file.
// Params:
//      pTrans (int64_t) tranpose phenotype data.
//      pDelim (int64_t) phenotype data delimiter.
//      pCol (int64_t *) phenotype data columns to ignore.
//      phenoFile (char *) phenotype file name.
void getPhenotype(int64_t pTrans, char pDelim, int64_t *pCol, char *phenoFile) {
    FILE *counter, *storage;
    char buff[255];
    char ch;

    if((counter = fopen(phenoFile, "r")) == NULL) {
        printf("File failed to open.\n");
    }
    if((storage = fopen(phenoFile, "r")) == NULL) {
        printf("File failed to open.\n");
    }  

    int64_t rows = 0;
    int firstRow = 1;
    int64_t columns = 0;

    // Scan file element by element until EOF is reached.
    while (fscanf(counter, "%s%c", buff, &ch) != EOF) {
        if (firstRow) {
            ++columns;
        }
        if (ch == '\n') {
            ++rows;
            firstRow = 0;
        }
    }
    fclose(counter);
    printf("rows: %lld, columns: %lld\n", rows, columns);
    // printFiles(storage, rows, columns, buff);
}

// Gets snp data from snp file.
// Params:
//      sTrans (int64_t) tranpose snp data.
//      sDelim (int64_t) snp data delimiter.
//      sCol (int64_t *) snp data columns to ignore.
//      snpFile (char *) snp file name.
void getSNP(int64_t sTrans, char sDelim, int64_t *sCol, char *snpFile) {
    FILE *counter, *storage;
    char buff[255];
    char ch;

    // Open file.
    if((counter = fopen(snpFile, "r")) == NULL) {
        printf("File failed to open.\n");
    }
    if((storage = fopen(snpFile, "r")) == NULL) {
        printf("File failed to open.\n");
    }

    int64_t rows = 0;
    int firstRow = 1;
    int64_t columns = 0;

    // Scan file element by element until EOF is reached.
    while (fscanf(counter, "%s%c", buff, &ch) != EOF) {
        if (firstRow) {
            ++columns;
        }
        if (ch == '\n') {
            ++rows;
            firstRow = 0;
        }
    }
    fclose(counter);
    printf("rows: %lld, columns: %lld\n", rows, columns);
    // printFiles(storage, rows, columns, buff);

    struct Data snpData;
    char *(*headers)[columns - 1];
    char *(*labels)[rows - 1];
    double (*dataPoints)[columns - 1] = malloc(sizeof(double) * (rows - 1));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            fscanf(storage, "%s%c", buff, &ch);
            if (i == 0 && j == 0) {
                snpData.name = strdup((const char *) buff);
            } else if (i == 0) {
                (*headers)[j - 1] = strdup((const char *) buff);
            } else if (j == 0) {
                (*labels)[i - 1] = strdup((const char *) buff);
            } else {
                dataPoints[i - 1][j - 1] = atof((const char *) buff);
            }
        }
    }
    snpData.headers = headers;
    snpData.labels = labels;
    snpData.dataPoints = dataPoints;

    printf("snpData.name = %s\n", snpData.name);
    for (int i = 0; i < columns - 1; ++i) {
        printf("header[%d] = %s\n", i, (*headers)[i]);
    }
    for (int i = 0; i < rows - 1; ++i) {
        printf("labels[%d] = %s\n", i, (*labels)[i]);
    }
    for (int i = 0; i < rows - 1; ++i) {
        for (int j = 0; j < columns - 1; ++j) {
            printf("dataPoints[%d][%d] = %f\n", i, j, dataPoints[i][j]);
        }
    }

    free(snpData.name);
    for (int i = 0; i < columns - 1; ++i) {
        free(headers[i]);
    }
    for (int i = 0; i < rows - 1; ++i) {
        free(labels[i]);
    }
    free(dataPoints);
}

// Prints data in files.
// Params:
//      storage (FILE *) file to print.
//      rows (int64_t) number of rows to print.
//      columns (int64_t) number of columns to print.
//      buff (char []) token storage buffer.
void printFiles(FILE *storage, int64_t rows, int64_t columns, char buff[]) {
    for (int64_t i = 0; i < rows; ++i) {
        for (int64_t j = 0; j < columns; ++j) {
            fscanf(storage, "%s", buff);
            printf("%s\t", buff);
        }
        printf("\n");
    }
}