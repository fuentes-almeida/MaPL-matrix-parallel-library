#ifndef METHODS_H_INCLUDED
#define METHODS_H_INCLUDED

double VectorXVector(double,double *,double *,int );
double *MatrixXVector(double **, double *, double *, int );
double **MatrizXMatriz(double**A, int A_rows, int A_cols, double**B, int B_rows, int B_cols);
double *Normalize(double *, int n);

double **PerformJacobiRotation (double **A,double**Phi,int n,double tolerance, int ite_max);
void SubspaceIteration(double **A,int n,int m,double tolerance, int ite_max);

#endif // METHODS_H_INCLUDED
