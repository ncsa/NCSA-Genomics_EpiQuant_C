#ifndef ARGS_H
#define ARGS_H

// Gets and sets user given options.
// Params:
// 		argc (int64_t) number of user arguments.
// 		argv (char *[]) user arguments.
// 		pTrans (int64_t *) option to tranpose phenotype file.
// 		sTrans (int64_t *) option to tranpose snp file.
// 		pDelim (char *) phenotype file delimiter.
// 		sDelim (char *) snp file delimiter.
void getArgs(int64_t argc, char *argv[], int64_t *pTrans, int64_t *sTrans, char *pDelim, char *sDelim, int64_t **pCol, int64_t **sCol);

#endif
