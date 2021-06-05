#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "function.h"

int main()
{
    int n,i,j;
    scanf("%d",&n);
    double** MatrixA;
    MatrixA=RequestMatrixDoubleMem(n,n);
    double *b;

    b=RequestVectorDoubleMem(n);

    for (i=0;i<n;i++)
    for (j=0;j<n;j++)
    scanf("%lf",&MatrixA[i][j]);
    for (i=0;i<n;i++)
    scanf("%lf",&b[i]);
    double *x=RequestVectorDoubleMem(n);

    GaussianElimination(MatrixA,b,n,x);
    for (int i=0;i<n;i++)
    printf("x[%d] = %lf\n",i,x[i]);
    free(b);
    freeMatrizDouble(MatrixA,n);
    return 0;
}
