#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

// Frees all allocated data from data structures.
// Params:
//      data (struct Data *) phenotype and snp data.
void clean(struct Data *data) {
    for (int i = 0; i < *(data->columns) - 1; ++i) {
        free(data->headers[i]);
    }
    free(data->headers);
    for (int i = 0; i < *(data->rows) - 1; ++i) {
        free(data->labels[i]);
    }
    free(data->labels);
    for (int i = 0; i < *(data->rows) - 1; ++i) {
        free(data->dataPoints[i]);
    }
    free(data->dataPoints);
    free(data->rows);
    free(data->columns);
    free(data->name);
    free(data);
}