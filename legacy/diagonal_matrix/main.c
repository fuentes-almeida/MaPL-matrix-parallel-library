#include <stdio.h>
#include <stdlib.h>
#include "memo.h"

double *SolveDiagMatrix(double *D,int n,double *x,double *b)
{
    int i;
    for(i=0;i<n;i++)
            x[i]=b[i]/D[i];
    return x;
}

double DetTriangMatrix(double *D,int n)
{
    double DetA;

    int i;
    DetA=1;
    for (i=0;i<n;i++)
        DetA=DetA*D[i];
    return DetA;
}

int main()
{
    int n,i;
    scanf("%d",&n);
    double *MatrixD=RequestVectorDoubleMem(n);
    double *x=RequestVectorDoubleMem(n);
    double *b=RequestVectorDoubleMem(n);

    for (i=0;i<n;i++)
    scanf("%lf",&MatrixD[i]);

    for (i=0;i<n;i++)
    scanf("%lf",&b[i]);

   x=SolveDiagMatrix(MatrixD,n,x,b);
   double det=DetTriangMatrix(MatrixD,n);
    for (i=0;i<n;i++)
    printf("x[%d] = %lf\n",i+1,x[i]);
    printf("det = %lf",det);
   return 0;
}
