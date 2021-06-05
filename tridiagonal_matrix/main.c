#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void FactorizeTridiag(double **MatrixA, int n,double *D, double *U, double *L)
{
    D[0]=MatrixA[0][0];

    for (int i=1;i<n;i++){
    L[i-1]=MatrixA[i][i-1]/D[i-1];
    U[i-1]=MatrixA[i-1][i]/D[i-1];
    D[i]=MatrixA[i][i]-L[i-1]*D[i-1]*U[i-1];
    }
}

double *SolveTriDiagMatrix(double *D, double *U, double *L, double *b,int n,double *x)
{
    int i;
    for(i=0;i<n;i++)
    x[i]=b[i]-x[i-1]*L[i-1];

    for (i=0;i<n;i++)
    x[i]=x[i]/D[i];

    for (i=n-1;i>=0;i--)
    x[i]=x[i]-U[i]*x[i+1];

    return x;
}

int main()
{
    int n,i,j;
    scanf("%d",&n);
    double **MatrixA;
    double *b;
    MatrixA=RequestMatrixDoubleMem(n,n);
    b=RequestVectorDoubleMem(n);
    for (i=0;i<n;i++)
    for (j=0;j<n;j++)
    scanf("%lf",&MatrixA[i][j]);

    for (i=0;i<n;i++)
     scanf("%lf",&b[i]);
     double *L,*D,*U;

    L=RequestVectorDoubleMem(n-1);
    U=RequestVectorDoubleMem(n-1);
    D=RequestVectorDoubleMem(n);

    FactorizeTridiag(MatrixA,n,D,U,L);


    printf("Vector Diag = ");
    for (i=0;i<n;i++)
        printf("%lf ",D[i]);
    printf("\n");

    printf("Vector L = ");
    for (i=0;i<n-1;i++)
           printf("%lf ",L[i]);
    printf("\n");

    printf("Vector U = ");
    for (i=0;i<n-1;i++)
           printf("%lf ",U[i]);
    printf("\n");

    free(b);
    free(D);
    free(U);
    free(L);
    freeMatrizDouble(MatrixA,n);

    return 0;
}
