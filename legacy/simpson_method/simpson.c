#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simpson.h"

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

double metodoSimpson(int n,double a1, double b1,double a2, double b2, double a3, double b3, func f)
{
    double h1=(b1-a1)/n;
    double h2=(b2-a2)/n;
    double h3=(b3-a3)/n;
    double x[n+1],y[n+1],z[n+1];

    for (int i=0;i<n+1;i++)
    {
        x[i]=-1+i*h1;
        y[i]=-1+i*h2;
        z[i]=-1+i*h3;
    }

    double suma3_par=0.0,suma3_impar=0.0;
    for (int i=1;i<n;i++){
        double suma2_par=0.0,suma2_impar=0.0;
        for (int j=1;j<n;j++){
            double suma1_par=0.0,suma1_impar=0.0;
            for (int k=1;k<n;k++){
                if (k%2==0)suma1_par+=f(x[k],y[j],z[i]);
                else suma1_impar+=f(x[k],y[j],z[i]);
            }
            if (j%2==0)suma2_par+=(h1/3)*(2*suma1_par+4*suma1_impar+(f(x[0],y[j],z[i])+f(x[n],y[j],z[i])));
            else suma2_impar+=(h1/3)*(2*suma1_par+4*suma1_impar+(f(x[0],y[j],z[i])+f(x[n],y[j],z[i])));
        }
        if (i%2==0)suma3_par+=(h2/3)*(2*suma2_par+4*suma2_impar+(f(x[0],y[0],z[i])+f(x[n],y[n],z[i])));
        else suma3_impar+=(h2/3)*(2*suma2_par+4*suma2_impar+(f(x[0],y[0],z[i])+f(x[n],y[n],z[i])));
    }
    double integral=(h3/3)*(2*suma3_par+4*suma3_impar+(f(x[0],y[0],z[0])+f(x[n],y[n],z[n])));

    return integral;
}
