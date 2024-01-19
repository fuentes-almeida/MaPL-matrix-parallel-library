#ifndef MATRIX_H
#define MATRIX_H

void GenerateCrouthMatrix(double **MatrixA,int n);
double* SolveTriSupMatrix(double **MatrixSup,int n,double *x,double *b);
double* SolveTriInfMatrix(double **MatrixInf,int n,double *x,double *b);
double *SolveCrouthSystem(double **A, double *b, double *x, int n);

#endif // MATRIX_H
