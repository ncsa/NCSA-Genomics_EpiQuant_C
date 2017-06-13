#include <stdio.h>
#include "args.h"
#include "omp.h"
#include "mpi.h"

int main(int argc, char *argv[]) {
	getArgs(argc, argv);

	char * snpFile = argv[argc - 1];
	char * phenoFile = argv[argc - 2];

	return 0;
}
