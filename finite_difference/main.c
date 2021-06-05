#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fdiff.h"

int main()
{
    printf("Calculo de la derivada de la funcion sin(x)\n");

    double h,x;
    printf("Valor del incremento: ");
    scanf("%lf",&h);

    printf("Punto a evaluar: ");
    scanf("%lf",&x);
    printf("\n");

    for (int i=1;i<=7;i++){
    printf("Derivada de orden %d\n",i);

    printf("Forward FD: \t\t%lf\n",forwardFD(x,h,i));
    printf("Backward FD: \t\t%lf\n",backwardFD(x,h,i));
    printf("Centered FD: \t\t%lf\n",centerFD(x,h,i));

    printf("Forward Lagrange: \t%lf\n",forwardLagrange(x,h,i));
    printf("Backward Lagrange: \t%lf\n",backwardLagrange(x,h,i));
    printf("Centered Lagrange: \t%lf\n",centerLagrange(x,h,i));

    printf("\n");
    }

    return 0;
}
