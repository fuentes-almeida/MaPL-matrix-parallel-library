#ifndef FDIFF_H_INCLUDED
#define FDIFF_H_INCLUDED

double fx(double x);

double forwardLagrange(double xi,double h,int n);
double centerLagrange(double xi,double h,int n);
double backwardLagrange(double xi,double h,int n);
double forwardFD(double xi,double h, int n);
double backwardFD(double xi,double h, int n);
double centerFD(double xi, double h, int n);

#endif // FDIFF_H_INCLUDED
