#ifndef ARGS_H
#define ARGS_H

// Gets and sets user given options.
// Params:
// 		argc (int) number of user arguments.
// 		argv (char *[]) user arguments.
// 		pTrans (int *) option to tranpose phenotype file.
// 		sTrans (int *) option to tranpose snp file.
// 		pDelim (char *) phenotype file delimiter.
// 		sDelim (char *) snp file delimiter.
void getArgs(int argc, char *argv[], int *pTrans, int *sTrans, char *pDelim, char *sDelim);

#endif
