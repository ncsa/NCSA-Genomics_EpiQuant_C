#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "args.h"
// #include "omp.h"
// #include "mpi.h"

int main(int argc, char *argv[]) {
	int64_t pTrans = 0;
	int64_t sTrans = 0;
	char pDelim, sDelim;
	int64_t *pCol;
	int64_t *sCol;

	getArgs(argc, argv, &pTrans, &sTrans, &pDelim, &sDelim, &pCol, &sCol);
	printf("%lld:%lld\n", pTrans, sTrans);
	printf("%c:%c\n", pDelim, sDelim);

	// char * snpFile = argv[argc - 1];
	// char * phenoFile = argv[argc - 2];

	free(pCol);
	free(sCol);
	return 0;
}
