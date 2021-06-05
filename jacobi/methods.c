#include <stdio.h>
#include <stdlib.h>
#include "memo.h"
#include <math.h>
#include "methods.h"

void FindMaxAbsValue(double**A,int n,int *max_row, int *max_col,double *valor)
{
    *valor=0.0;
    for (int i=0;i<n;i++)
        for (int j=i+1;j<n;j++)
            if (fabs(A[i][j])>*valor)
                {
                    *valor=fabs(A[i][j]);
                    *max_row=i; *max_col=j;
                }
}

void PerformJacobiRotation (double **A,double**Phi,int n,double tolerance, int ite_max)
{
    double valor=1e6;
    int i,j,count=0;
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
    printf("Matriz de eigenvectores:\n");
    for (int k=0;k<n;k++){
        for (int p=0;p<n;p++)
            printf("%lf ",Phi[k][p]);
        printf("\n");}
        printf("\n");
    printf("Eigenvalores:\n");
    for (int k=0;k<n;k++)
            printf("%lf\n",A[k][k]);

}
