#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "memo.h"
#include "matrix.h"

double *SolveDiagMatrix(double **MatrixDiag,int n,double *x,double *b)
{
    int i;
    for(i=0;i<n;i++){
        x[i]=b[i]/MatrixDiag[i][i];}

return x;

}

double* SolveTriInfMatrix(double **MatrixInf,int n,double *x,double *b)
{
    int i,j;
    double sum=0;

    x[0]=b[0]/MatrixInf[0][0];
    for(j=1;j<n;j++){
             sum=0;
        for(i=0;i<=j-1;i++){
            sum=sum + MatrixInf[j][i]*x[i];}
        x[j]=(b[j]-sum)/MatrixInf[j][j];
    }
    return x;
}



double* SolveTriSupMatrix(double **MatrixSup,int n,double *x,double *b)
{
    int i,j;
    double sum=0;

    x[n-1]=b[n-1];
    for(j=n-2;j>=0;j--){
                sum=0;
        for(i=j+1;i<n;i++){
            sum=sum + MatrixSup[j][i]*x[i];
        }
        x[j]=b[j]-sum;
    }
    return x;
}

double **FactorizeCrouthMatrix(double **MatrixA,int n)
{
 int i,j,k;
 double sum;

    for (i=0;i<n;i++){
    sum=0;
    for(k=0;k<i;k++)
        sum=sum+MatrixA[i][k]*MatrixA[k][i];
    MatrixA[i][i]=MatrixA[i][i]-sum;

    for(j=i+1;j<n;j++){
            sum=0;
        for(k=0;k<i;k++)
            sum=sum+MatrixA[j][k]*MatrixA[k][i];
    MatrixA[j][i]=MatrixA[j][i]-sum;}

    for(j=i+1;j<n;j++){
            sum=0;
        for (k=0;k<i;k++)
            sum=sum+MatrixA[i][k]*MatrixA[k][j];
    MatrixA[i][j]=(MatrixA[i][j]-sum)/MatrixA[i][i];}
    }

    return MatrixA;
}

double *SolveCrouthSystem(double **CrouthMatrix, double *b, double *x, int n)
{
    double *y;
    y=RequestVectorDoubleMem(n);
    y=SolveTriInfMatrix(CrouthMatrix,n,y,b);
    x=SolveTriSupMatrix(CrouthMatrix,n,x,y);
    free(y);
    return x;
}

double **FactorizeCholeskyMatrix(double **MatrixA,int n)
{
    int i,j,k;
    double sum=0;

    for (i=0;i<n;i++){
    sum=0;
    for(k=0;k<i;k++)
        sum=sum+MatrixA[i][k]*MatrixA[i][k]*MatrixA[k][k];
    MatrixA[i][i]=MatrixA[i][i]-sum;
    for(j=i+1;j<n;j++){
            sum=0;

        for(k=0;k<i;k++)
            sum=sum+MatrixA[i][k]*MatrixA[j][k]*MatrixA[k][k];
    MatrixA[j][i]=(MatrixA[j][i]-sum)/MatrixA[i][i];
    MatrixA[i][j]=MatrixA[j][i];
    }}

return MatrixA;
}

double* SolveCholeskySupMatrix(double **MatrixSup,int n,double *x,double *b)
{
    int i,j;
    double sum=0;

    x[n-1]=b[n-1];
    for(j=n-2;j>=0;j--){
                sum=0;
        for(i=j+1;i<n;i++){
            sum=sum + MatrixSup[j][i]*x[i];
        }
        x[j]=b[j]-sum;
    }

    return x;
}

double* SolveCholeskyInfMatrix(double **MatrixInf,int n,double *x,double *b)
{
    int i,j;
    double sum=0;

    x[0]=b[0];
    for(j=1;j<n;j++){
             sum=0;
        for(i=0;i<=j-1;i++){
            sum=sum + MatrixInf[j][i]*x[i];}
        x[j]=b[j]-sum;
    }
    return x;
}

double *SolveCholeskySystem(double **A,double *b,double *x,int n)
{
    x=SolveCholeskyInfMatrix(A,n,x,b);
    x=SolveDiagMatrix(A,n,x,x);
    x=SolveCholeskySupMatrix(A,n,x,x);
    return x;
}


