#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


int main()
{
    int n,i,j;
    scanf("%d",&n);
    double **Lower;
    double *b,*x;
    Lower=RequestMatrixDoubleMem(n,n);
    b=RequestVectorDoubleMem(n);
    x=RequestVectorDoubleMem(n);

    for (i=0;i<n;i++)
    for (j=0;j<n;j++)
    scanf("%lf",&Lower[i][j]);

    for (i=0;i<n;i++)
    scanf("%lf",&b[i]);

   x=SolveTriInfTras(Lower,n,x,b);

    for (i=n-1;i>=0;i--)
   printf("x[%d] = %lf\n",i,x[i]);

    freeVectorDouble(b);
    freeVectorDouble(x);
    freeMatrizDouble(Lower,n);

   return 0;

}
