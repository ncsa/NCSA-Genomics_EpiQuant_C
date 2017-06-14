#include <stdio.h>
#include "args.h"
#include "omp.h"
#include "mpi.h"

int main(int argc, char *argv[]) {
	bool pTrans = false;
	bool sTrans = false;
	char pDelim, sDelim;

	getArgs(argc, argv, &pTrans, &sTrans);
	printf("%d:%d\n", pTrans, sTrans);

	char * snpFile = argv[argc - 1];
	char * phenoFile = argv[argc - 2];

	return 0;
}
