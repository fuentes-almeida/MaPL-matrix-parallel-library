#include <stdio.h>
#include <stdlib.h>

void SolveTriSupMatrix(double MatrixA[][5],int n,double x[n],double B[n])
{
    int i,j;
    double sum=0;

    x[n-1]=B[n-1]/MatrixA[n-1][n-1];

    printf("x[%d] = %lf\n",n-1,x[n-1]);

    for(j=n-2;j>=0;j--){
        for(i=j+1;i<n;i++){
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

void SolveMatrixTriangularSuperior(double mat[][6], int nr, int nc, double vec[])
{
    for(int i=nr-1;i>=0;i--)
    {
        vec[i]=mat[i][nr];
        for(int j=nc-2;j>i;j--)
            vec[i]=vec[i]-(mat[i][j]*vec[j]);

    vec[i]=vec[i]/mat[i][i];
    }

}

int main()
{
    int n,i,j;
    scanf("%d",&n);
    double MatrixA[n][n+1];
    double B[n];
    double x[n];

    for (i=0;i<n;i++)
    for (j=0;j<n;j++)
    scanf("%lf",&MatrixA[i][j]);

    for (i=0;i<n;i++)
    scanf("%lf",&MatrixA[i][n]);


    SolveMatrixTriangularSuperior(MatrixA,n,n+1,x);

    for (int i=0;i<n;i++)
        printf("%lf ",x[i]);

   return 0;
}
