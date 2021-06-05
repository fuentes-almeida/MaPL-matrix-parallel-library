#ifndef MATRIX_H
#define MATRIX_H

double *SolveDiagMatrix(double**,int ,double*,double*);
double* SolveTriSupMatrix(double**,int,double*,double*);
double* SolveTriInfMatrix(double**,int ,double*,double*);

double **FactorizeCrouthMatrix(double**,int );
double *SolveCrouthSystem(double**, double*, double*, int );
double **FactorizeCholeskyMatrix(double**,int );
double* SolveCholeskySupMatrix(double**,int ,double*,double*);
double* SolveCholeskyInfMatrix(double**,int ,double*,double*);
double *SolveCholeskySystem(double **A,double *b,double *x,int n);

#endif // MATRIX_H
