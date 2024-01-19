#ifndef SIMPSON_H_INCLUDED
#define SIMPSON_H_INCLUDED

typedef double(*func)(double,double,double);

double fxyz1(double x, double y, double z);
double fxyz2(double x, double y, double z);
double fxyz3(double x, double y, double z);
double metodoSimpson(int n,double a1, double b1,double a2, double b2, double a3, double b3, func f);

#endif // SIMPSON_H_INCLUDED
