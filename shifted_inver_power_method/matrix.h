#ifndef MATRIX_H
#define MATRIX_H

double **GenerateCrouthMatrix(double **MatrixA,int n);
double* SolveTriSupMatrix(double **MatrixSup,int n,double *x,double *b);
double* SolveTriInfMatrix(double **MatrixInf,int n,double *x,double *b);
double *SolveCrouthSystem(double **MatrixA, double *b, double *x, int n);

#endif // MATRIX_H
