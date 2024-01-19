#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "memo.h"
#include "gauss.h"


double fxyz1(double x, double y, double z)
{
    return x*x+y*y+z*z;
}

double fxyz2(double x, double y, double z)
{
    return x*x+y*y-z*z;
}

double fxyz3(double x, double y, double z)
{
    return ((1-sqrt(x*x+y*y))*(1-sqrt(x*x+y*y))+z*z);
}

void Get_weights(int n, double *x, double *w)
{
    FILE *input;
    input=fopen("weigths.dat","r");

    double aux;
    while (aux!=n)
        fscanf(input,"%lf",&aux);

    for (int i=0;i<n;i++){
        fscanf(input,"%lf",&x[i]);
        fscanf(input,"%lf",&w[i]);
        fscanf(input,"%lf",&aux);
    }
    fclose(input);
}

double GaussQuadrature(int n,double a1, double b1,double a2, double b2, double a3, double b3, func f)
{
    double *x=RequestVectorDoubleMem(n);
    double *w=RequestVectorDoubleMem(n);
    Get_weights(n,x,w);

    double h1=(b1-a1)/2;
    double h2=(b2-a2)/2;
    double h3=(b3-a3)/2;
    double p1=(b1+a1)/2;
    double p2=(b2+a2)/2;
    double p3=(b3+a3)/2;

    double integral=0.0;
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            for (int k=0;k<n;k++)
                integral+=h1*h2*h3*w[k]*w[j]*w[i]*f(h1*x[k]+p1,h2*x[j]+p2,h3*x[i]+p3);

    free(x);
    free(w);
    return integral;

}
