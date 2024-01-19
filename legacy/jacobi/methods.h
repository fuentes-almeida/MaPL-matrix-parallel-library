#ifndef METHODS_H_INCLUDED
#define METHODS_H_INCLUDED

void FindMaxAbsValue(double**A,int n,int *max_row, int *max_col,double *valor);
void PerformJacobiRotation (double **A,double**Phi,int n,double tolerance, int ite_max);

#endif // METHODS_H_INCLUDED
