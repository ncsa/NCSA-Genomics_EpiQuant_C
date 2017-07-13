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
// 		pCol (int64_t **) phenotype columns to ignore.
// 		sCol (int64_t **) snp columns to ignore.
// 		alpha (double *) threshold value.
// 		outFile (char **) output results file name.
void getArgs(int64_t argc,
            char *argv[], 
            int64_t *pTrans, 
            int64_t *sTrans, 
            char *pDelim, 
            char *sDelim, 
            int64_t **pCol, 
            int64_t **sCol, 
            double *alpha1,
            double *alpha2, 
            char **outFile);

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
                  char *outFile);

#endif
