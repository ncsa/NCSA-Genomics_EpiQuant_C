#ifndef PARSER_H
#define PARSER_H

struct Data {
    int64_t *rows;
    int64_t *columns;
    char *name;
    char **headers;
    char **labels;
    double **dataPoints;
};

// Gets data from phenotype and snp files.
// Params:
//      trans (int64_t) tranpose data.
//      delim (int64_t)  data delimiter.
//      col (int64_t *)  data columns to ignore.
//      file (char *)  file name.
struct Data * getData(int64_t trans, char delim, int64_t *col, char *file);

// Prints the data in a Data struct.
// Params:
//      data (struct Data *) struct that contains phenotype or snp data.
void printData(struct Data *data);

#endif