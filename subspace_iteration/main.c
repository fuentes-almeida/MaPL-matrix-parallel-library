#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "memo.h"
#include "methods.h"
#include <math.h>

int main()
{
    int n,m,ite_max; double tolerance;
    double **MatrixA;
    scanf("%d %lf %d %d",&n,&tolerance,&ite_max,&m);

    MatrixA=RequestMatrixDoubleMem(n,n);
    for (int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%lf",&MatrixA[i][j]);

    SubspaceIteration(MatrixA,n,m,tolerance,ite_max);
    return 0;
}
