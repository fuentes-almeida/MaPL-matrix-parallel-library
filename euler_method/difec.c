#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "difec.h"

double g(double x)
{
    double c=6.22*1e-19;
    double n1=2000;
    double n2=2000;
    double n3=3000;
    double r=c*pow(n1-0.5*x,2)*pow(n2-0.5*x,2)*pow(n3-0.75*x,3);
    return r;
}

double f(double y)
{
    double k=0.94462290;
    return (k*y*(1-y));
}

void InverseEulerMethod(double yi,double h,double a,double ymax)
{
    int i=1;
    while(yi<ymax){
      yi=yi+h*f(yi);
        i++;
    }
    printf("t = %lf hrs: %lf\n",a+h*i,yi);
}

void InverseRungeKutta2grade(double yi,double h,double a,double ymax)
{
    int i=1;
    while(yi<ymax){
        double k1=h*f(yi);
        double k2=h*f(yi+k1);
        yi=yi+(k1+k2)/2;
        i++;
    }
    printf("t = %lf hrs: %lf\n",a+h*i,yi);
}

void InverseRungeKutta4grade(double yi,double h,double a,double ymax)
{
    int i=1;
    while(yi<ymax){
        double k1=h*f(yi);
        double k2=h*f(yi+k1/2);
        double k3=h*f(yi+k2/2);
        double k4=h*f(yi+k3);
        yi=yi+(k1+2*k2+2*k3+k4)/6;
        i++;
    }
    printf("t = %lf hrs: %lf\n",a+h*i,yi);
}

void EulerMethod(double yi,double h,double a,double b)
{
    int i=1;
    double t=a;
    while(t<b){
      yi=yi+h*g(yi);
      t=a+h*i;
        i++;
    }
    printf("t = %lf seg: %lf\n",a+h*i,yi);
}

void RungeKutta2grade(double yi,double h,double a,double b)
{
    int i=1;
    double t=a;
    while(t<b){
        double k1=h*g(yi);
        double k2=h*g(yi+k1);
        yi=yi+(k1+k2)/2;
        t=a+h*i;
        i++;
    }
    printf("t = %lf seg: %lf\n",a+h*i,yi);
}

void RungeKutta4grade(double yi,double h,double a,double b)
{
    int i=1;
    double t=a;
    while(t<b){
        double k1=h*g(yi);
        double k2=h*g(yi+k1/2);
        double k3=h*g(yi+k2/2);
        double k4=h*g(yi+k3);
        yi=yi+(k1+2*k2+2*k3+k4)/6;
        t=a+h*i;
        i++;
    }
    printf("t = %lf seg: %lf\n",a+h*i,yi);
}
