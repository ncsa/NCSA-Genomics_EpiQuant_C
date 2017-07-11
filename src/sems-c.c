#include <stdio.h>
#include "args.h"
// #include "omp.h"
// #include "mpi.h"

int main(int argc, char *argv[]) {
	int pTrans = 0;
	int sTrans = 0;
	char pDelim, sDelim;

	getArgs(argc, argv, &pTrans, &sTrans, &pDelim, &sDelim);
	printf("%d:%d\n", pTrans, sTrans);
	printf("%c:%c\n", pDelim, sDelim);

	char * snpFile = argv[argc - 1];
	char * phenoFile = argv[argc - 2];

	return 0;
}
