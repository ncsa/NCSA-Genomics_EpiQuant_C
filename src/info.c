#include <stdio.h>

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
    -a    Forward Alpha         Sets alpha threshold for forward step. By\n\
                                default foward alpha is 0.05.\n\
\n\
    -A    Backward Alpha        Sets alpha threshold for backward step. By\n\
                                default backward alpha is 0.05.\n\
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
    -o    Output File           Sets the output file to write results to. By\n\
                                default output file is set to sems-c.o.\n\
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
    [ -a <#> ]                    # Set forward alpha.\n\
    [ -A <#> ]                    # Set backward alpha.\n\
    [ -c <p=...,s=...> ]          # Delete columns.\n\
    [ -d <delimiter,delimiter> ]  # File delimiters.\n\
    [ -h ]                        # Print help text.\n\
    [ -o <path/to/file> ]         # Set output file.\n\
    [ -t <file,file> ]            # Tranpose file data.\n\
    [ -u ]                        # Print usage information.\n\
\n");
}