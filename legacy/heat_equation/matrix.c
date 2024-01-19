#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//#include "memo.h"
#include "matrix.h"

double **GenerateCrouthMatrix(double **MatrixA,int n)
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

double *SolveTriInfTras(double **Lower,int n,double *x,double *b)
{

    int i,j;
    double sum=0;

    for(i=n-1;i>=0;i--){
            sum=0;
        for(j=i+1;j<n;j++){
            sum=sum + Lower[j][i]*x[j];}
        x[i]=(b[i]-sum)/Lower[i][i];
    }
    return x;

}
double **GenerateCholeskyMatrix(double **MatrixA,int n)
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

double *SolveDiagMatrix(double **MatrixDiag,int n,double *x,double *b)
{
    int i;


    for(i=0;i<n;i++){
        x[i]=b[i]/MatrixDiag[i][i];}

return x;

}

void FactorizeTridiag(double **MatrixA, int n)
{
double *L,*D,*U;
int i;
L=RequestVectorDoubleMem(n-1);
U=RequestVectorDoubleMem(n-1);
D=RequestVectorDoubleMem(n);

D[0]=MatrixA[0][0];

for (i=1;i<n;i++){

    L[i-1]=MatrixA[i][i-1]/D[i-1];
    U[i-1]=MatrixA[i-1][i]/D[i-1];
    D[i]=MatrixA[i][i]-L[i-1]*D[i-1]*U[i-1];
}

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

