#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fdiff.h"

double fx(double x)
{
    return sin(x);
}

double forwardLagrange(double xi,double h,int n)
{
    if (n==1)
    return (fx(xi-2*h)-4*fx(xi-h)+3*fx(xi))/(2*h);
    else return (forwardLagrange(xi-2*h,h,n-1)-4*forwardLagrange(xi-h,h,n-1)+3*forwardLagrange(xi,h,n-1))/(2*h);

}

double centerLagrange(double xi,double h,int n)
{
    if (n==1)
    return (fx(xi+h)-fx(xi-h))/(2*h);
    else return (centerLagrange(xi+h,h,n-1)-centerLagrange(xi-h,h,n-1))/(2*h);

}

double backwardLagrange(double xi,double h,int n)
{
    if (n==1)
    return (-3*fx(xi)+4*fx(xi+h)-fx(xi+2*h))/(2*h);
    else return (-3*backwardLagrange(xi,h,n-1)+4*backwardLagrange(xi+h,h,n-1)-backwardLagrange(xi+2*h,h,n-1))/(2*h);
}

double forwardFD(double xi,double h, int n)
{
    if (n==1)
        return (fx(xi+h)-fx(xi))/h;
    else return (forwardFD(xi+h,h,n-1)-forwardFD(xi,h,n-1))/h;

}

double backwardFD(double xi,double h, int n)
{
    if (n==1)
        return (fx(xi)-fx(xi-h))/h;
    else return (backwardFD(xi,h,n-1)-backwardFD(xi-h,h,n-1))/h;

}

double centerFD(double xi, double h, int n)
{
    if (n==1)
    return (fx(xi+h)-fx(xi-h))/(2*h);
    else return (centerFD(xi+h,h,n-1)-centerFD(xi-h,h,n-1))/(2*h);
}
