#include <stdio.h>
#include <stdlib.h>
#include "memo.h"
#include "matrix.h"
#include "methods.h"
#include <math.h>

int main()
{
    int n,p,r_max,m;
    double tolerance;
    double **MatrixA;
    double *curr_vector;

    FILE *input;
    input=fopen("A3.mat","r");
    if (input==NULL)
        printf("Imposible abrir archivo");
    fscanf(input,"%d %d",&n,&p);
    if (n!=p)
        printf("La matriz no es cuadrada");

    printf("Introduzca el numero de eigenvalores a calcular: ");
    scanf("%d",&m);
    printf("Introduzca un numero maximo de iteraciones: ");
    scanf("%d",&r_max);
    printf("Introduzca un valor de tolerancia: ");
    scanf("%lf",&tolerance);

    MatrixA=RequestMatrixDoubleMem(n,n);
    for (int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        fscanf(input,"%lf",&MatrixA[i][j]);
    fclose(input);

    curr_vector=RequestVectorDoubleMem(n);
    for (int i=0;i<n;i++)
        curr_vector[i]=1;

    PowerMethodDeflation(MatrixA,curr_vector,n,tolerance,r_max,m);

    return 0;
}
