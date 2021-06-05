#ifndef DIFEC_H_INCLUDED
#define DIFEC_H_INCLUDED

double g(double x);
double f(double y);
void InverseEulerMethod(double yi,double h,double a,double ymax);
void InverseRungeKutta2grade(double yi,double h,double a,double ymax);
void InverseRungeKutta4grade(double yi,double h,double a,double ymax);
void EulerMethod(double yi,double h,double a,double b);
void RungeKutta2grade(double yi,double h,double a,double b);
void RungeKutta4grade(double yi,double h,double a,double b);

#endif // DIFEC_H_INCLUDED
