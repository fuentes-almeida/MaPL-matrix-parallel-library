#ifndef METHODS_H_INCLUDED
#define METHODS_H_INCLUDED

void SolveJacobiSystem(double**, double*, int ,int ,double );
void SolveGaussSeidelSystem(double **, double *, int ,int ,double );
double VectorXVector(double esca,double *A,double *B,int n);
double *MatrixXVector(double **matrix, double *vector, double *product, int n);
double *Normalize(double *vector, int n);
void GetMaxEigenVectorEigenValue(double **matrix,double *curr_vector,int n, double tolerance, int r_max);


#endif // METHODS_H_INCLUDED
