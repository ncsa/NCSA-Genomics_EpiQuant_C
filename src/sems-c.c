#include <stdio.h>
#include "args.h"
#include "omp.h"
#include "mpi.h"

int main(int argc, char *argv[])
{
	getSettings(argc, argv);
	return 0;
}
