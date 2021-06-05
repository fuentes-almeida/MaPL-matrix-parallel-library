#include <stdio.h>
#include <stdlib.h>
#include "memo.h"
#include <math.h>
#include "methods.h"

int main()
{
    int n,ite_max; double tolerance;
    double **MatrixA,**Phi;
    scanf("%d %lf %d",&n,&tolerance,&ite_max);

    MatrixA=RequestMatrixDoubleMem(n,n);
    Phi=RequestMatrixDoubleMem(n,n);
    for (int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%lf",&MatrixA[i][j]);

    PerformJacobiRotation (MatrixA,Phi,n,tolerance,ite_max);

    return 0;
}
