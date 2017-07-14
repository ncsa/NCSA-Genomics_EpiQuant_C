#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct Data {
    int64_t *rows;
    int64_t *columns;
    char *name;
    char **headers;
    char **labels;
    double **dataPoints;
};

void printData(struct Data *data);
int ignoreColumn(int64_t index, int64_t *col);
void transposeData(struct Data *data);
void printFiles(char *name, int64_t rows, int64_t columns, char buff[]);

// Gets data from phenotype and snp files.
// Params:
//      trans (int64_t) tranpose data.
//      delim (int64_t)  data delimiter.
//      col (int64_t *)  data columns to ignore.
//      file (char *)  file name.
struct Data * getData(int64_t trans, char delim, int64_t *col, char *file) {
    FILE *size, *counter, *storage;
    int64_t buffSize = 10;
    char ch;
    int64_t rows = 0;
    int firstRow = 1;
    int64_t columns = 0;

    if((size = fopen(file, "r")) == NULL) {
        printf("File failed to open.\n");
    }
    if((counter = fopen(file, "r")) == NULL) {
        printf("File failed to open.\n");
    }
    if((storage = fopen(file, "r")) == NULL) {
        printf("File failed to open.\n");
    }

    // Get buffer size that will fit an entire line.
    // Compare the header line to a data line.
    int c;
    int64_t count1 = 0;
    int64_t count2 = 0;
    do {
        c = fgetc(size);
        ++count1;
    } while (c != EOF && c != '\n');
    do {
        c = fgetc(size);
        ++count2;
    } while (c != EOF && c != '\n');
    char buff[(count1 > count2 ? count1 : count2) * 2];
    fclose(size);

    // Scan file element by element until EOF is reached.
    if (delim == 't' || delim == 's') {
        while (fscanf(counter, "%s%c", buff, &ch) != EOF) {
            if (firstRow) {
                ++columns;
            }
            if (ch == '\n') {
                ++rows;
                firstRow = 0;
            }
        }
    } else {
        // NOTE: Can't deal with spaces in the file.
        while (fscanf(counter, "%s", buff) != EOF) {
            ++rows;
            // printf("%s\n", buff);
            if (firstRow) {
                char *token;
                if ((token = strtok(buff, ",")) != NULL) {
                    ++columns;
                }
                while ((token = strtok(NULL, ",")) != NULL) {
                    ++columns;
                }
                firstRow = 0;
            }
        }
    }
    fclose(counter);
    // printf("rows: %lld, columns: %lld\n", rows, columns);
    // printFiles(phenoFile, rows, columns, buff);

    // Allocate memory for Data struct.
    struct Data *data = malloc(sizeof(struct Data));
    data->rows = (int64_t *) malloc(sizeof(int64_t));
    *(data->rows) = rows;
    data->columns = (int64_t *) malloc(sizeof(int64_t));
    *(data->columns) = columns - col[0];
    data->headers = malloc(sizeof(char *) * (columns - 1 - col[0]));
    data->labels = malloc(sizeof(char *) * (rows - 1));
    data->dataPoints = malloc(sizeof(double *) * (rows - 1));
    for (int64_t i = 0; i < rows; ++i) {
        data->dataPoints[i] = malloc(sizeof(double) * (columns - 1 - col[0]));
    }

    int64_t ignored = 0;
    // Scan file by token and store values.
    if (delim == 't' || delim == 's') {
        for (int64_t i = 0; i < rows; ++i) {
            for (int64_t j = 0; j < columns; ++j) {
                fscanf(storage, "%s", buff);
                if (!ignoreColumn(j, col)) {
                    // printf("%d,%d: %s\n", i, j, buff);
                    if (i == 0 && j == 0) {
                        data->name = strdup((const char *) buff);
                    } else if (i == 0) {
                        data->headers[j - 1 - ignored] = strdup((const char *) buff);
                    } else if (j == 0) {
                        data->labels[i - 1] = strdup((const char *) buff);
                    } else {
                        data->dataPoints[i - 1][j - 1 - ignored] = atof((const char *) buff);
                    }
                } else {
                    ++ignored;
                }
            }
            ignored = 0;
        }
    } else {
        int64_t iRow = 0;
        int64_t jColumn = 0;
        while (fscanf(storage, "%s", buff) != EOF) {
            // printf("%s\n", buff);
            char *token;
            if ((token = strtok(buff, ",")) != NULL) {
                do {
                    if (!ignoreColumn(jColumn, col)) {
                        if (iRow == 0 && jColumn == 0) {
                            data->name = strdup((const char *) token);
                        } else if (iRow == 0) {
                            data->headers[jColumn - 1 - ignored] = strdup((const char *) token);
                        } else if (jColumn == 0) {
                            data->labels[iRow - 1] = strdup((const char *) token);
                        } else {
                            data->dataPoints[iRow - 1][jColumn - 1 - ignored] = atof((const char *) token);
                        }
                    } else {
                        ++ignored;
                    }
                    ++jColumn;
                } while ((token = strtok(NULL, ",")) != NULL);
            } else {
                perror("Unable to tokenize string.\n");
                exit(1);
            }
            ++iRow;
            jColumn = 0;
        }
    }
    fclose(storage);

    // Transpose data.
    if (trans) {
        transposeData(data);
    }
    return data;
}

// Determines whether a columns should be ignored or not.
// Params:
//      index (int64_t) column number.
//      col (int64_t *) columns to ignore.
int ignoreColumn(int64_t index, int64_t *col) {
    for (int64_t i = 0; i < col[0]; ++i) {
        if (index == col[i + 1]) {
            return 1;
        }
    }
    return 0;
}

// Tranpose the data.
// Params:
//      data (struct Data *) phenotype and snp data.
void transposeData(struct Data *data) {
    // Swap rows and columns.
    int64_t *rows = data->rows;
    data->rows = data->columns;
    data->columns = rows;
    double **dataPoints = data->dataPoints;
    // Swap headers and labels.
    char **headers = data->headers;
    data->headers = data->labels;
    data->labels = headers;
    
    // Allocate new memory space.
    data->dataPoints = malloc(sizeof(double) * (*(data->rows) - 1));
    for (int64_t i = 0; i < *(data->rows); ++i) {
        data->dataPoints[i] = malloc(sizeof(double) * (*(data->columns) - 1));
    }

    // Transpose data.
    for (int64_t i = 0; i < *(data->rows) - 1; ++i) {
        for (int64_t j = 0; j < *(data->columns) - 1; ++j) {
            data->dataPoints[i][j] = dataPoints[j][i];
        }
    }

    // Deallocate old memory space.
    for (int64_t i = 0; i < *(data->columns); ++i) {
        free(dataPoints[i]);
    }
    free(dataPoints);
}

// Prints the data in a Data struct.
// Params:
//      data (struct Data *) struct that contains phenotype or snp data.
void printData(struct Data *data) {
    int64_t rows = *(data->rows);
    int64_t columns = *(data->columns);
    printf("data->name = %s\n", data->name);
    printf("data->rows = %lld\n", rows);
    printf("data->columns = %lld\n", columns);
    for (int64_t i = 0; i < columns - 1; ++i) {
        printf("%s  ", data->headers[i]);
    }
    printf("\n");
    for (int64_t i = 0; i < rows - 1; ++i) {
        printf("%s:   ", data->labels[i]);
        for (int64_t j = 0; j < columns - 1; ++j) {
            printf("%f    ", data->dataPoints[i][j]);
        }
        printf("\n");
    }
}

// Prints data in files.
// Params:
//      storage (FILE *) file to print.
//      rows (int64_t) number of rows to print.
//      columns (int64_t) number of columns to print.
//      buff (char []) token storage buffer.
void printFiles(char *name, int64_t rows, int64_t columns, char buff[]) {
    FILE *file;
    if ((file = fopen(name, "r")) == NULL) {
        printf("File failed to open.\n");
    }
    for (int64_t i = 0; i < rows; ++i) {
        for (int64_t j = 0; j < columns; ++j) {
            fscanf(file, "%s", buff);
            printf("%s\t", buff);
        }
        printf("\n");
    }
    fclose(file);
}