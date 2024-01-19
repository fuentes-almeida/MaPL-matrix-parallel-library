#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "methods.h"
#include "memo.h"


int main()
{
    int n,m,max_count;
    double tolerance;
    printf("Introduzca un numero maximo de iteraciones: ");
    scanf("%d",&max_count);
    printf("Introduzca un valor de tolerancia: ");
    scanf("%d",&tolerance);


    FILE *input;
    input=fopen("A2.mat","r");
    if (input==NULL)
        printf("Imposible abrir archivo");
    fscanf(input,"%d %d",&n,&m);
    if (n!=m)
        printf("La matriz no es cuadrada");

    double **MatrixA;
    double *b;
    MatrixA=RequestMatrixDoubleMem(n,n);
    b=RequestVectorDoubleMem(n);
    for (int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        fscanf(input,"%lf",&MatrixA[i][j]);

    fclose(input);

    input=fopen("b2.vec","r");
        if (input==NULL)
        printf("Imposible abrir archivo");
    fscanf(input,"%d",&n);
    for (int k=0;k<n;k++)
        fscanf(input,"%lf",&b[k]);

    fclose(input);

    SolveJacobiSystem(MatrixA,b,n,max_count,tolerance);
    return 0;
}
