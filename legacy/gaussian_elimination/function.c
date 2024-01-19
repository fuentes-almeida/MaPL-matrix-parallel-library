#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "function.h"

void GaussianElimination(double **A,double *b, int n,double *x)
{
    for (int k =0;k<n-1;k++){
        for (int i=k+1;i<n;i++){
            double m=A[i][k]/A[k][k];
            for (int j=k+1;j<n;j++)
                A[i][j]=A[i][j]-m*A[k][j];
            A[i][k]=0;
            b[i]=b[i]-m*b[k];
        }
    }

    for (int i=n-1; i>=0;i--){
        double suma=0;
        for (int j=i+1;j<n;j++)
            suma+=A[i][j]*x[j];
        x[i]=(b[i]-suma)/A[i][i];
    }
}
