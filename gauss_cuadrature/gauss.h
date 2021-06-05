#ifndef GAUSS_H_INCLUDED
#define GAUSS_H_INCLUDED

typedef double(*func)(double,double,double);

double fxyz1(double x, double y, double z);
double fxyz2(double x, double y, double z);
double fxyz3(double x, double y, double z);
void Get_weights(int n, double *x, double *w);
double GaussQuadrature(int n,double a1, double b1,double a2, double b2, double a3, double b3, func f);

#endif // GAUSS_H_INCLUDED
