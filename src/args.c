#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include "args.h"

// #define TRY do{ jmp_buf ex_buf__; if( !setjmp(ex_buf__) ){
// #define CATCH } else {
// #define ETRY } }while(0)
// #define THROW longjmp(ex_buf__, 1)

// Prints help text.
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
Examples:\n\
\n\
    sems-c -c p=1:2:3 pheno.txt snp.txt  # Delete columns 1, 2, and 3.\n\
    sems-c -d c,t pheno.txt snp.txt      # Set delimiter to commas and tabs.\n\
    sems-c -t p,s pheno.txt snp.txt      # Tranpose data from both files.\n\
\n\
Options:\n\
\n\
    -c    Delete Columns        Signals SEMS-C to delete certain columns. These\n\
                                options should be passed in in the form:\n\
\n\
                                -c p=#:#:#,s=#:#:#\n\
\n\
                                where '#' are the columns to delete and ':'\n\
                                delimit different column numbers. By default\n\
                                no columns are deleted.\n\
\n\
    -d    File Delimiters       Asserts that the phenotype and snp file are\n\
                                delimited by the given delimiter. Expects the\n\
                                form:\n\
\n\
                                -d [c/s/t,c/s/t]\n\
\n\
                                where 'c' is comma, 's' is space, and 't' is\n\
                                tab. Allows multiple delimiters. First is for\n\
                                phenotype and second is SNP. Defaults to comma\n\
                                delimited.\n\
\n\
    -t    Transpose Data        Transpose data from phenotype and/or snp file.\n\
\n\
                                -t [p/s,p/s]\n\
\n\
\n");
}

// Print usage text.
void printUsage() {
	printf("\n\
Usage: sems-c [OPTION...] [PHENOTYPE_FILE] [SNP_FILE]\n\
\n\
Options:\n\
    [-c <p=...,s=...>]          # Delete columns.\n\
    [-d <delimiter,delimiter>]  # File delimiters.\n\
    [-h]                        # Print help text.\n\
    [-t <file,file>]            # Tranpose file data.\n\
    [-u]                        # Print usage information.\n\
\n");
}

// Gets user given columsn to ignore.
// Params:
// 		arg (char *) user given argument to parse.
// 		pCol (int64_t ***) phenotype columns to ignore.
// 		sCol (int64_t ***) snp columns to ignore.
void getColumns(char *arg, int64_t ***pCol, int64_t ***sCol) {
	int64_t argSize = 0;
	int64_t p = 0;
	int64_t s = 0;
	int64_t pSize = 0;
	int64_t sSize = 0;

	// Get number of phenotype and snp column arguments.
	while (arg[argSize] != '\0') {
		if (arg[argSize] == 'p') {
			p = 1;
			s = 0;
			pSize = 1;
		} else if (arg[argSize] == 's') {
			p = 0;
			s = 1;
			sSize = 1;
		} else if (arg[argSize] == ':') {
			if (p == 1) {
				++pSize;
			} else {
				++sSize;
			}
		}
		++argSize;
	}

	// printf("argSize = %lld\n", argSize);
	// printf("pSize = %lld\n", pSize);
	// printf("sSize = %lld\n", sSize);
	**pCol = (int64_t *) malloc(sizeof(int64_t) * pSize);
	**sCol = (int64_t *) malloc(sizeof(int64_t) * sSize);
	p = 0;
	s = 0;
	int64_t pIdx = 0;
	int64_t sIdx = 0;
	int64_t partial = 0;

	// Build and store phenotype and snp columns.
	for (int64_t i = 0; i < argSize; i++) {
		// Build partial columns.
		if (arg[i] == 'p') {
			p = 1;
			s = 0;
		} else if (arg[i] == 's') {
			p = 0;
			s = 1;
		} else if (arg[i] != '=' && arg[i] != ':' && arg[i] != ',') {
			partial *= 10;
			partial += arg[i] - '0';
		}
		
		// Assign columns to column arrays.
		if (arg[i] == ':' || arg[i] == ',' || argSize - 1 == i) {
			// printf("parial = %lld, p = %lld, s = %lld\n", partial, p, s);
			if (p == 1) {
				(**pCol)[pIdx] = partial;
				++pIdx;
			} else {
				(**sCol)[sIdx] = partial;
				++sIdx;
			}
			partial = 0;
		}
	}
}

// Prints delimiter error text.
void delimError() {
	fprintf(stderr, "\
sems-c: The delimiter option must be c, s, or t.\n\
        Try 'sems-c -h' or 'sems-c -u' for more information.\n");
	exit(1);
}

// Gets user given delimiters.
// Params:
// 		arg (char *) the delimiter argument.
// 		pDelim (char *) holds phenotype delimiter.
// 		sDelim (char *) holds the snp delimiter.
void getDelimiters(char *arg, char *pDelim, char *sDelim) {
	if (arg[0] != 'c' && arg[0] != 't' && arg[0] != 's') {
		delimError();
	} else if (arg[2] != 'c' && arg[2] != 't' && arg[2] != 's') {
		delimError();
	}
	*pDelim = arg[0];
	*sDelim = arg[2];
}

// Prints transpose error text.
void transError() {
	fprintf(stderr, "\
sems-c: The transpose option must be p or s.\n\
        Try 'sems-c -h' or 'sems-c -u' for more information.\n");
	exit(1);
}

// Gets user given transpose options.
// Params:
// 		arg (char *) the tranpose options.
// 		pTrans (int64_t *) option to tranpose phenotype file.
// 		strans (int64_t *) option to tranpose snp file.
void getTranpose(char *arg, int64_t *pTrans, int64_t *sTrans) {
	char * token = strtok(arg, ",");
	if (*token != 'p' && *token != 's') {
		transError();
	}
	if (*token == 'p') {
		*pTrans = 1;
	} else if (*token == 's'){
		*sTrans = 1;
	}
	while ((token = strtok(NULL, ",")) != NULL) {
		if (*token != 'p' && *token != 's') {
			transError();
		}
		if (*token == 's') {
			*sTrans = 1;
		} else if (*token == 'p') {
			*pTrans = 1;
		}
	}
}

// Gets and sets user given options.
// Params:
// 		argc (int64_t) number of user arguments.
// 		argv (char *[]) user arguments.
// 		pTrans (int64_t *) option to tranpose phenotype file.
// 		sTrans (int64_t *) option to tranpose snp file.
// 		pDelim (char *) phenotype file delimiter.
// 		sDelim (char *) snp file delimiter.
void getArgs(int64_t argc, char *argv[], int64_t *pTrans, int64_t *sTrans, char *pDelim, char *sDelim, int64_t **pCol, int64_t **sCol) {
	if (argc == 2) {
		if (strcmp(argv[1], "-h") == 0) {
			printHelp();
			exit(1);
		} else if (strcmp(argv[1], "-u") == 0) {
			printUsage();
			exit(1);
		}
	} else if (argc == 1 || argc - 2 <= 0) {
		fprintf(stderr,"\
sems-c: You must at least provide a phenotype file and snp file.\n\
        Try 'sems-c -h' or 'sems-c -u' for more information.\n");
		exit(1);
	} else {
		int64_t delimSet = 0;
		for (int64_t i = 1; i < argc - 2; ++i) {
			printf("%s\n", argv[i]);
			switch(argv[i][1]) {
				case 'c':
					++i;
					getColumns(argv[i], &pCol, &sCol);
					break;
				case 'd':
					++i;
					getDelimiters(argv[i], pDelim, sDelim);
					delimSet = 1;
					break;
				case 't':
					++i;
					getTranpose(argv[i], pTrans, sTrans);
					break;
				default:
					fprintf(stderr, "\
sems-c: An invalid option was given to sems-c.\n\
        Try 'sems-c -h' or 'sems-c -u' for more information.\n");
					exit(1);
			}
		}
		if (!delimSet) {
			*pDelim = 'c';
			*sDelim = 'c';
		}
	}
}
