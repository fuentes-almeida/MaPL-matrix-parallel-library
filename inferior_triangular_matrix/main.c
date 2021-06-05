#include <stdio.h>
#include <stdlib.h>

void SolveTriInfMatrix(double MatrixA[][5],int n,double x[n],double B[n])
{
    int i,j;
    double sum=0;
    x[0]=B[0]/MatrixA[0][0];
    printf("x[%d] = %lf\n",0,x[0]);
    for(j=1;j<n;j++){
        for(i=0;i<=j-1;i++){
            sum=sum + MatrixA[j][i]*x[i];
        }
        x[j]=(B[j]-sum)/MatrixA[j][j];
        printf("x[%d] = %lf\n",j,x[j]);
    sum=0;
    }
    return;
}

void DetTriangMatrix(double MatrixA[][5],int n)
{
    double DetA;
    int i;
    DetA=1;
    for (i=0;i<n;i++)
        DetA=DetA*MatrixA[i][i];
    printf("DetA = %lf",DetA);

}
int main()
{
    int n,i,j;
    scanf("%d",&n);
    double MatrixA[n][n];
    double B[n];
    double x[n];

    for (i=0;i<n;i++)
    for (j=0;j<n;j++)
    scanf("%lf",&MatrixA[i][j]);

    for (i=0;i<n;i++)
    scanf("%lf",&B[i]);

   SolveTriInfMatrix(MatrixA,5,x,B);
   DetTriangMatrix(MatrixA,5);

   return 0;
}
