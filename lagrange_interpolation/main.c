#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "memo.h"

double LargrangeInterpolation(double **curve, int n,double x)
{
    double *y=RequestVectorDoubleMem(n);
    double *den=RequestVectorDoubleMem(n);
    double product;
    double Px=0;

    for (int i=0;i<n;i++)
        y[i]=curve[1][i];

    for (int i=0;i<n;i++)
    {
        product=1;
        for (int j=0;j<n;j++)
        if (i!=j)
            product*=(curve[0][i]-curve[0][j]);
        den[i]=product;
    }

        for (int i=0;i<n;i++)
        {
            product=1;
            for (int j=0;j<n;j++)
                if (i!=j) product*=(x-curve[0][j]);
            Px+=y[i]*product/den[i];
        }

    return Px;

}


int main()
{
    int n1,n2,n3;

    scanf("%d",&n1);
    double **curve1=RequestMatrixDoubleMem(2,n1);
    for (int i=0;i<n1;i++)
        scanf("%lf %lf",&curve1[0][i],&curve1[1][i]);
    double x=6.0;

    printf("%lf\n",LargrangeInterpolation(curve1,n1,x));

    scanf("%d",&n2);
    double **curve2=RequestMatrixDoubleMem(n2,2);
    for (int i=0;i<n2;i++)
        scanf("%lf %lf",&curve2[0][i],&curve2[1][i]);
    x=24.0;
    printf("%lf\n",LargrangeInterpolation(curve2,n2,x));

    scanf("%d",&n3);
    double **curve3=RequestMatrixDoubleMem(n3,2);
    for (int i=0;i<n3;i++)
        scanf("%lf %lf",&curve3[0][i],&curve3[1][i]);

    x=28.0;
    printf("%lf\n",LargrangeInterpolation(curve3,n3,x));


    return 0;
}
