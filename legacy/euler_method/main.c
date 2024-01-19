#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "difec.h"

int main()
{
    double h;

    printf("PROBLEMA 1:\n");
    printf("Valor de h: ");
    scanf("%lf",&h);
    double yi=8/358.0;
    printf("Metodo Euler:\n");
    InverseEulerMethod(yi,h,10.0,0.95);
    printf("Metodo Runge-Kutta 2 orden:\n");
    InverseRungeKutta2grade(yi,h,10.0,0.95);
    printf("Metodo Runge-Kutta 4 orden:\n");
    InverseRungeKutta4grade(yi,h,10.0,0.95);

    printf("PROBLEMA 2:\n");
    printf("Valor de h: ");
    scanf("%lf",&h);
    yi=0.0;
    printf("Metodo Euler:\n");
    EulerMethod(yi,h,0.0,0.2);
    printf("Metodo Runge-Kutta 2 orden:\n");
    RungeKutta2grade(yi,h,0.0,0.2);
    printf("Metodo Runge-Kutta 4 orden:\n");
    RungeKutta4grade(yi,h,0.0,0.2);
    return 0;
}
