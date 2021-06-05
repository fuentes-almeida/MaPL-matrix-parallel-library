#include <stdio.h>
#include <stdlib.h>
#include "memo.h"
#include <math.h>
#include "function.h"

int main()
{
    int n, ite_max;
    double tolerance;

    FILE *input;
    input=fopen("A.txt","r");
    if (!input) {
        printf("imposible abrir archivo");
        return 0;}

    fscanf(input,"%d %d",&n, &n);
    double **A=RequestMatrixDoubleMem(n,n);
    double *b=RequestVectorDoubleMem(n);
    double *x=RequestVectorDoubleMem(n);

    for (int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            fscanf(input,"%lf",&A[i][j]);

    fclose(input);
    input=fopen("b.txt","r");
    if (!input) {
        printf("imposible abrir archivo");
        return 0;}

    fscanf(input,"%d",&n);
    for (int i=0;i<n;i++)
        fscanf(input,"%lf",&b[i]);
    fclose(input);

    printf("Tolerancia: ");
    scanf("%lf",&tolerance);
    printf("Iteraciones maximas : ");
    scanf("%d",&ite_max);

    x=GradienteConjugado(A,b,x,n,tolerance,ite_max);

    if (x){
    input=fopen("X.txt","w");
    for (int i=0;i<n;i++)
        fprintf(input,"x[%d] = %lf\n",i,x[i]);
    fclose(input);
    }

    freeMatrizDouble(A,n);
    free(b);
    free(x);

    return 0;
}
