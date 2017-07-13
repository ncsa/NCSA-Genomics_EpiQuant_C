#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "args.h"
#include "parser.h"
#include "clean.h"
// #include "omp.h"
// #include "mpi.h"

// Gets the user given arguments.
// Params:
// 		argc (int) number of arguments passed to sems-c.
// 		argv (char *[]) arguments passed to sems-c.
int main(int argc, char *argv[]) {
	// Set default values.
	int64_t pTrans = 0;
	int64_t sTrans = 0;
	int64_t *pCol = (int64_t *) malloc(sizeof(int64_t));
	pCol[0] = 0;
	int64_t *sCol = (int64_t *) malloc(sizeof(int64_t));
	sCol[0] = 0;
	double alpha1 = 0.05;
	double alpha2 = 0.05;
	char *outFile = "sems-c.o";
	char pDelim = 't';
	char sDelim = 't';
	char *snpFile = argv[argc - 1];
	char *phenoFile = argv[argc - 2];

	// Get user passed arguments
	getArgs(argc, argv, &pTrans, &sTrans, &pDelim, &sDelim, &pCol, &sCol, &alpha1, &alpha2, 
	        &outFile);

	// Gather data from phenotype and snp files.
	struct Data *phenoData = getData(pTrans, pDelim, pCol, phenoFile);
	struct Data *snpData = getData(sTrans, sDelim, sCol, snpFile);

	// printData(phenoData);
	printData(snpData);
	printUValues(pTrans, sTrans, pDelim, sDelim, pCol, sCol, phenoFile, snpFile, alpha1, alpha2, 
	             outFile);

	// Clean up allocated memory.
	clean(phenoData);
	clean(snpData);
	free(pCol);
	free(sCol);
	return 0;
}