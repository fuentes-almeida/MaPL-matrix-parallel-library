#include <stdio.h>
#include <stdlib.h>
#include "memo.h"
#include "methods.h"
#include <math.h>
#include "matrix.h"

int main()
{
    int n,m,r_max;
    double tolerance;
    double **MatrixA;
    double *curr_vector;

    printf("Introduzca un numero maximo de iteraciones: ");
    scanf("%d",&r_max);
    printf("Introduzca un valor de tolerancia: ");
    scanf("%lf",&tolerance);

    FILE *input;
    input=fopen("A2.mat","r");
    if (input==NULL)
        printf("Imposible abrir archivo");
    fscanf(input,"%d %d",&n,&m);
    if (n!=m){
        printf("La matriz no es cuadrada");
        return 0;}

    MatrixA=RequestMatrixDoubleMem(n,n);
    for (int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        fscanf(input,"%lf",&MatrixA[i][j]);
    fclose(input);

    curr_vector=RequestVectorDoubleMem(n);
    curr_vector[0]=8;
    for (int i=1;i<n;i++)
        curr_vector[i]=1;

    InversePowerMethod(MatrixA,curr_vector,n,tolerance,r_max);

    freeMatrizDouble(MatrixA,n);
    free(curr_vector);

    return 0;
}
