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

// Gets phenotype data from phenotype file.
// Params:
//      pTrans (int64_t) tranpose phenotype data.
//      pDelim (int64_t) phenotype data delimiter.
//      pCol (int64_t *) phenotype data columns to ignore.
//      phenoFile (char *) phenotype file name.
struct Data * getPhenotype(int64_t pTrans, 
                  char pDelim, 
                  int64_t *pCol, 
                  char *phenoFile);

// Gets snp data from snp file.
// Params:
//      sTrans (int64_t) tranpose snp data.
//      sDelim (int64_t) snp data delimiter.
//      sCol (int64_t *) snp data columns to ignore.
//      snpFile (char *) snp file name.
struct Data * getSNP(int64_t sTrans, 
            char sDelim, 
            int64_t *sCol, 
            char *snpFile);

void printData(struct Data *data);

#endif