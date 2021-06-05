#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "methods.h"
#include "memo.h"
#include "matrix.h"

double VectorXVector(double esca,double *A,double *B,int n)
{
    esca=0;
    for (int i=0;i<n;i++)
        esca+=A[i]*B[i];
    return esca;
}

double *MatrixXVector(double **matrix, double *vector, double *product, int n)
{
    for (int i=0;i<n;i++){
            double suma=0;
        for(int j=0;j<n;j++){
            suma+=matrix[i][j]*vector[j];
        }
        product[i]=suma;
    }
    return product;

}

double **MatrizXMatriz(double**A, int A_rows, int A_cols, double**B, int B_rows, int B_cols)
{

    double**C;
    C=RequestMatrixDoubleMem(A_rows,B_cols);

    for (int i = 0; i < A_rows; ++i)
    {
        for (int j = 0; j < B_cols; ++j)
        {
            double sum = 0;
            for (int k = 0; k < A_cols; ++k)
            {
                sum+=A[i][k]*B[k][j];
            }
            C[i][j] = sum;
            }
            }
    return C;
}

double *Normalize(double *vector, int n)
{
    double product=0;
    product=VectorXVector(product,vector,vector,n);
    if (product<0)
        printf("Error, operation cannot be computed");

    product=sqrt(product);
        for (int i=0;i<n;i++)
            vector[i]=vector[i]/product;
    return vector;
}

void FindMaxAbsValue(double**A,int n,int *max_row, int *max_col,double *valor)
{
    *valor=0.0;
    for (int i=0;i<n;i++)
        for (int j=i+1;j<n;j++)
            if (fabs(A[i][j])>=*valor)
                {
                    *valor=fabs(A[i][j]);
                    *max_row=i; *max_col=j;
                }
}



double **PerformJacobiRotation (double **A,double**Phi,int n,double tolerance, int ite_max)
{
    double valor=1e6;
    int i,j,count=0;
    for (int k=0;k<n;k++)
        for (int p=0;p<n;p++)
        Phi[k][p]=0;
    for (int k=0;k<n;k++)
        Phi[k][k]=1;

    while (valor>tolerance&&count<ite_max)
        {
        count++;
        FindMaxAbsValue(A,n,&i,&j,&valor);
        double theta =0.5*atan2 (2*A[i][j],A[i][i]-A[j][j]);
        for (int k=0;k<n;k++)
            {
            double temp1=A[k][i]*cos(theta)+A[k][j]*sin(theta);
            double temp2=A[k][j]*cos(theta)-A[k][i]*sin(theta);
            A[k][i]=temp1;
            A[k][j]=temp2;
            temp1=Phi[k][i]*cos(theta)+Phi[k][j]*sin(theta);
            temp2=Phi[k][j]*cos(theta)-Phi[k][i]*sin(theta);
            Phi[k][i]=temp1;
            Phi[k][j]=temp2;
            }

        for (int k=0;k<n;k++)
            {
            double temp1=A[i][k]*cos(theta)+A[j][k]*sin(theta);
            double temp2=A[j][k]*cos(theta)-A[i][k]*sin(theta);
            A[i][k]=temp1;
            A[j][k]=temp2;
            }
        }
    return Phi;
}

void SubspaceIteration(double **A,int n,int m,double tolerance, int ite_max)
{
    double **Acholesky=RequestMatrixDoubleMem(n,n);
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            Acholesky[i][j]=A[i][j];
    Acholesky=FactorizeCholeskyMatrix(Acholesky,n);
    double **LambdaNM0=RequestMatrixDoubleMem(n,m);
    double **LambdaNM1=RequestMatrixDoubleMem(n,m);
    double **B=RequestMatrixDoubleMem(m,m);
    double **LambdaMNT=RequestMatrixDoubleMem(m,n);
    double **QMM=RequestMatrixDoubleMem(m,m);
    double *x,*b,*eigens_curr,*eigens_new,distance=1000,ak;
    int count=0;
    x=RequestVectorDoubleMem(n);
    b=RequestVectorDoubleMem(n);
    eigens_curr=RequestVectorDoubleMem(m);
    eigens_new=RequestVectorDoubleMem(m);

    for (int i=0;i<m;i++)
        LambdaNM0[i][i]=1;


    while (distance>tolerance&&count<ite_max){
    count++;
    for (int i=0;i<m;i++)
    {

        for (int j=0;j<n;j++)
        {
            b[j]=LambdaNM0[j][i];
        }

        x=SolveCholeskySystem(Acholesky,b,x,n);

        if (i>0)
        for (int k=0;k<i;++k)
            {
            ak=0;
            for (int j=0;j<n;j++)
                ak+=LambdaNM1[j][k]*x[j];
            for (int j=0;j<n;j++)
                x[j]=x[j]-ak*LambdaNM1[j][k];
            }

        x=Normalize(x,n);

        for (int j=0;j<n;j++)
        {
            LambdaNM1[j][i]=x[j];
        }

    }

    for (int i=0;i<m;i++)
        for (int j=0;j<n;j++)
            LambdaMNT[i][j]=LambdaNM1[j][i];

    B=MatrizXMatriz(MatrizXMatriz(LambdaMNT,m,n,A,n,n),m,n,LambdaNM1,n,m);

    QMM=PerformJacobiRotation(B,QMM,m,tolerance,ite_max);

    LambdaNM0=MatrizXMatriz(LambdaNM1,n,m,QMM,m,m);

    distance=0;
    for (int i=0;i<m;i++)
        {
        eigens_new[i]=B[i][i];
        distance+=pow(eigens_curr[i]-eigens_new[i],2);
        }
    distance=sqrt(distance);

    for (int i=0;i<m;i++)
        eigens_curr[i]=eigens_new[i];
    }

    printf("Eigenvalores:\n");
        for (int i=0;i<m;i++)
            printf("%lf\n",B[i][i]);

    printf("\nEigenVectores por columnas:\n");
        for (int i=0;i<n;i++){
        for (int j=0;j<m;j++)
            printf("%lf  ",LambdaNM0[i][j]);
            printf("\n");}

}
