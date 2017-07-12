#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "args.h"
#include "parser.h"
// #include "omp.h"
// #include "mpi.h"

// Gets the user given arguments.
// Params:
// 		argc (int) number of arguments passed to sems-c.
// 		argv (char *[]) arguments passed to sems-c.
int main(int argc, char *argv[]) {
	int64_t pTrans = 0;
	int64_t sTrans = 0;
	char pDelim, sDelim;
	int64_t *pCol;
	int64_t *sCol;

	getArgs(argc, argv, &pTrans, &sTrans, &pDelim, &sDelim, &pCol, &sCol);
	char *snpFile = argv[argc - 1];
	char *phenoFile = argv[argc - 2];

	getPhenotype(pTrans, pDelim, pCol, phenoFile);
	getSNP(sTrans, sDelim, sCol, snpFile);

	// printf("%lld:%lld\n", pTrans, sTrans);
	// printf("%c:%c\n", pDelim, sDelim);
	// printf("%lld:%lld\n", pCol[0], sCol[0]);
	printf("%s:%s\n", phenoFile, snpFile);

	free(pCol);
	free(sCol);
	return 0;
}
