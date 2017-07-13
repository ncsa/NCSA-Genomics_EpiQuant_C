#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include "info.h"

void getColumns(char *arg, int64_t ***pCol, int64_t ***sCol);
void delimError();
void getDelimiters(char *arg, char *pDelim, char *sDelim);
void transError();
void getTranpose(char *arg, int64_t *pTrans, int64_t *sTrans);

// Gets and sets user given options.
// Params:
// 		argc (int64_t) number of user arguments.
// 		argv (char *[]) user arguments.
// 		pTrans (int64_t *) option to tranpose phenotype file.
// 		sTrans (int64_t *) option to tranpose snp file.
// 		pDelim (char *) phenotype file delimiter.
// 		sDelim (char *) snp file delimiter.
// 		pCol (int64_t **) phenotype columns to ignore.
// 		sCol (int64_t **) snp columns to ignore.
// 		alpha (double *) threshold value.
// 		outFile (char **) output results file name.
void getArgs(int64_t argc, char *argv[], int64_t *pTrans, int64_t *sTrans, char *pDelim, 
             char *sDelim, int64_t **pCol, int64_t **sCol, double *alpha1, double *alpha2, 
			 char **outFile) {
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
		for (int64_t i = 1; i < argc - 2; ++i) {
			// printf("%s\n", argv[i]);
			switch(argv[i][1]) {
				case 'a': // alpha1
					++i;
					*alpha1 = atof(argv[i]);
					break;
				case 'A': // alpha2
					++i;
					*alpha2 = atof(argv[i]);
					break;
				case 'c': // columns
					++i;
					getColumns(argv[i], &pCol, &sCol);
					break;
				case 'd': // delimiters
					++i;
					getDelimiters(argv[i], pDelim, sDelim);
					break;
				case 'o': // output file
					++i;
					*outFile = argv[i];
					break;
				case 't': // tranpose
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
	}
}

// Gets user given columsn to ignore.
// Params:
// 		arg (char *) user given argument to parse.
// 		pCol (int64_t ***) phenotype columns to ignore.
// 		sCol (int64_t ***) snp columns to ignore.
void getColumns(char *arg, int64_t ***pCol, int64_t ***sCol) {
	free(**pCol);
	free(**sCol);
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
	**pCol = (int64_t *) malloc(sizeof(int64_t) * (pSize + 1));
	(**pCol)[0] = pSize;
	**sCol = (int64_t *) malloc(sizeof(int64_t) * (sSize + 1));
	(**sCol)[0] = sSize;
	
	p = 0;
	s = 0;
	int64_t pIdx = 1;
	int64_t sIdx = 1;
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
				(**pCol)[pIdx] = partial - 1;
				++pIdx;
			} else {
				(**sCol)[sIdx] = partial - 1;
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
// 		pTrans (int64_t *) option to tranpose phenotype file.
// 		sTrans (int64_t *) option to tranpose snp file.
// 		pDelim (char *) phenotype file delimiter.
// 		sDelim (char *) snp file delimiter.
// 		pCol (int64_t **) phenotype columns to ignore.
// 		sCol (int64_t **) snp columns to ignore.
// 		alpha (double *) threshold value.
// 		outFile (char **) output results file name.
void printUValues(int64_t pTrans, int64_t sTrans, char pDelim, char sDelim, int64_t *pCol, 
                  int64_t *sCol, char *phenoFile, char *snpFile, double alpha1, double alpha2,  
				  char *outFile) {
	printf("Tranpose = %lld:%lld\n", pTrans, sTrans);
	printf("Delimit = %c:%c\n", pDelim, sDelim);
	printf("Columns = %lld:%lld\n", pCol[0], sCol[0]);
	printf("iFiles = %s:%s\n", phenoFile, snpFile);
	printf("Alpha1 = %f\n", alpha1);
	printf("Alpha2 = %f\n", alpha2);
	printf("oFile = %s\n", outFile);
}
