# SEMS-C -- Step-Wise Epistatic Model Selection in C

    SEMS-C is a program developed at the National Center for Supercomputing
    Applications in collaboration with the Center for Computational
    Biotechnology and Genomic Medicine to map epistatic gene interactions. It
    uses step-wise linear regression model selection to build a cumulative
    statistical model of epistatic interactions between SNP's and phenotypes.

## Usage
    sems-c [OPTION...] [PHENOTYPE_FILE] [SNP_FILE]

    [ -a <#> ]                    # Set forward alpha.
    [ -A <#> ]                    # Set backward alpha.
    [ -c <p=...,s=...> ]          # Delete columns.
    [ -d <delimiter,delimiter> ]  # File delimiters.
    [ -h ]                        # Print help text.
    [ -o <path/to/file> ]         # Set output file.
    [ -t <file,file> ]            # Tranpose file data.
    [ -u ]                        # Print usage information.

## Examples

    sems-c -c p=1:2:3 pheno.txt snp.txt  # Delete columns 1, 2, and 3.
    sems-c -d c,t pheno.txt snp.txt      # Set delimiter to commas and tabs.
    sems-c -t p,s pheno.txt snp.txt      # Tranpose data from both files.

## Options

    -a    Forward Alpha         Sets alpha threshold for forward step. By
                                default foward alpha is 0.05.

    -A    Backward Alpha        Sets alpha threshold for backward step. By
                                default backward alpha is 0.05.

    -c    Delete Columns        Signals SEMS-C to delete certain columns. These
                                options should be passed in in the form:

                                -c p=#:#:#,s=#:#:#

                                where '#' are the columns to delete and ':'
                                delimit different column numbers. By default
                                no columns are deleted.

    -d    File Delimiters       Asserts that the phenotype and snp file are
                                delimited by the given delimiter. Expects the
                                form:

                                -d [c/s/t,c/s/t]

                                where 'c' is comma, 's' is space, and 't' is
                                tab. Allows multiple delimiters. First is for
                                phenotype and second is SNP. Defaults to tab
                                delimited.

    -o    Output File           Sets the output file to write results to. By
                                default output file is set to sems-c.o.

    -t    Transpose Data        Transpose data from phenotype and/or snp file.

                                -t [p/s,p/s]