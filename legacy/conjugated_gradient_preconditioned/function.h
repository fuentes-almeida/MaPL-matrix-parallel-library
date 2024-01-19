#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

double VectorXVector(double*,double*,int);
double *MatrixXVector(double**, double*, double*, int);
double *GradienteConjugado(double**, double*, double*,int,double, int);

#endif // FUNCTION_H_INCLUDED
