#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"


int main()
{
    int n,i;
    double largo,k,Q,phi0,phin;
    double *b,*Phi,*L,*D;

    scanf("%lf %d %lf %lf %lf %lf",&largo,&n,&k,&Q,&phi0,&phin);

    double xdelta=largo/n;

    b=RequestVectorDoubleMem(n-1);
    Phi=RequestVectorDoubleMem(n-1);
    L=RequestVectorDoubleMem(n-2);
    D=RequestVectorDoubleMem(n-1);

    for (i=0;i<n-2;i++)
    L[i]=-1;

    for (i=0;i<n-1;i++){
    b[i]=Q*xdelta;
    D[i]=2;
    }
    b[0]+=phi0;
    b[n-2]+=phin;

    for (i=0;i<n-1;i++)
    b[i]=b[i]*xdelta/k;

    Phi=SolveTriDiagMatrix(D,L,L,b,n-1,Phi);

    for (i=0;i<n-1;i++)
    printf("Phi[%d] = %lf \t",i,Phi[i]);

    free(b);
    free(Phi);
    free(L);
    free(D);

    return 0;
}
