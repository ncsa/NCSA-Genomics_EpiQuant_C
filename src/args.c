#include <stdio.h>
#include <stdlib.h>
#include "args.h"

void printHelp() {
	printf("\n\
SEMS-C -- Step-Wise Epistatic Model Selection in C\n\
\n\
    SEMS-C is a program developed at the National Center for Supercomputing\n\
    Applications in collaboration with the Center for Computational\n\
    Biotechnology and Genomic Medicine to map epistatic gene interactions. It\n\
    uses step-wise linear regression model selection to build a cumulative\n\
    statistical model of epistatic interactions between SNP's and phenotypes.\n\
\n\
Usage: sems-c [OPTION...] [PHENOTYPE_FILE] [SNP_FILE]\n\
\n\
Options:\n\
\n");
}

void printUsage() {
	printf("\n\
Usage: sems-c [OPTION...] [PHENOTYPE_FILE] [SNP_FILE]\n\
\n\
Options: [-h] # Print help text.\n\
         [-u] # Print usage information.\n\
\n");
}

void getArgs(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stderr,"\
sems-c: You must at least provide a phenotype file and snp file.\n\
        Try 'sems-c -h' or 'sems-c -u' for more information.\n");
		exit(1);
	} else {
		for (int i = 1; i < argc; ++i) {
			switch(argv[i][1]) {
				case 'h':
					printHelp();
					break;
				case 'u':
					printUsage();
					break;
				default:
					fprintf(stderr, "\
sems-c: An invalid option was given to sems-c.\n\
        Try 'sems-c -h' or 'sems-c -u' for more information.\n");
					exit(1);
			}
		}
	}
}
