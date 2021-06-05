#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "methods.h"
#include "memo.h"
#include <omp.h>

int main()
{
    int n,m,max_count=10000;
    double tolerance=1e-10;
    printf("Numero maximo de iteraciones: ");
    //scanf("%d",&max_count);
    printf("%d\n",max_count);
    printf("Valor de tolerancia: ");
    //scanf("%lf",&tolerance);
    printf("%lf\n",tolerance);

    FILE *input;
    input=fopen("A.txt","r");
    if (input==NULL)
        printf("Imposible abrir archivo");
    fscanf(input,"%d %d",&n,&m);
    if (n!=m)
        printf("La matriz no es cuadrada");

    double **MatrixA;
    MatrixA=RequestMatrixDoubleMem(n,n);
    for (int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        fscanf(input,"%lf",&MatrixA[i][j]);

    fclose(input);

    input=fopen("b.txt","r");
        if (input==NULL)
        printf("Imposible abrir archivo");
    fscanf(input,"%d",&n);
    double *b;
    b=RequestVectorDoubleMem(n);
    for (int k=0;k<n;k++)
        fscanf(input,"%lf",&b[k]);

    fclose(input);


    SolveJacobiSystem(MatrixA,b,n,max_count,tolerance);

    return 0;
}
