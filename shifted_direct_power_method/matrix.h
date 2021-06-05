#ifndef MATRIX_H
#define MATRIX_H

double **GenerateCrouthMatrix(double **MatrixA,int n);
double* SolveTriSupMatrix(double **MatrixSup,int n,double *x,double *b);
double* SolveTriInfMatrix(double **MatrixInf,int n,double *x,double *b);
double *SolveTriInfTras(double **Lower,int n,double *x,double *b);
double **GenerateCholeskyMatrix(double **MatrixA,int n);
double* SolveCholeskySupMatrix(double **MatrixSup,int n,double *x,double *b);
double* SolveCholeskyInfMatrix(double **MatrixInf,int n,double *x,double *b);
double *SolveDiagMatrix(double **MatrixDiag,int n,double *x,double *b);
void FactorizeTridiag(double **MatrixA, int n);
double *SolveTriDiagMatrix(double *D, double *U, double *L, double *b,int n,double *x);
double *SolveCrouthSystem(double **MatrixA, double *b, double *x, int n);



#endif // MATRIX_H
