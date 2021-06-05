#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "memo.h"

// S1, S2, S3, and M are all constants, and z is part of the
// private per-thread generator state.
unsigned TausStep(unsigned z, int S1, int S2, int S3, unsigned M)
{
  unsigned b=(((z << S1) ^ z) >> S2);
  return z = (((z & M) << S3) ^ b);
}

// A and C are constants
unsigned LCGStep(unsigned  z, unsigned A, unsigned C)
{
    return z=(A*z+C);
}

double HybridTaus( )
{
    // Combined period is lcm(p1,p2,p3,p4)~ 2^121
    return 2.3283064365387e-10 * (
    // Periods
    TausStep(rand(), 13, 19, 12, 4294967294UL) ^    // p1=2^31-1
    TausStep(rand(), 2, 25, 4, 4294967288UL)   ^    // p2=2^30-1
    TausStep(rand(), 3, 11, 17, 4294967280UL)  ^    // p3=2^28-1
    LCGStep(rand(), 1664525, 1013904223UL)
    // p4=2^32
    );
}

int cmpfunc (const void * a, const void * b)
{
    double a2=*(double*)a;
    double b2=*(double*)b;

    if (a2>b2) return 1;
    else if (a2<b2) return -1;
    else return 0;
}

double fx(double x)
{
    return x*x;
}

double *SolveTriDiagMatrix(double *D, double *U, double *L, double *b,int n,double *x)
{
    int i;
    for(i=0;i<n;i++)
    x[i]=b[i]-x[i-1]*L[i-1];

    for (i=0;i<n;i++)
    x[i]=x[i]/D[i];

    for (i=n-1;i>=0;i--)
    x[i]=x[i]-U[i]*x[i+1];

    return x;
}

double *FactorizeTridiag(double **MatrixA, double *b, double *x,int n )
{
    double *L,*D,*U;
    L=RequestVectorDoubleMem(n-1);
    U=RequestVectorDoubleMem(n-1);
    D=RequestVectorDoubleMem(n);

    D[0]=MatrixA[0][0];

    for (int i=1;i<n;i++)
        {
        L[i-1]=MatrixA[i][i-1]/D[i-1];
        U[i-1]=MatrixA[i-1][i]/D[i-1];
        D[i]=MatrixA[i][i]-L[i-1]*D[i-1]*U[i-1];
        }

    x=SolveTriDiagMatrix(D,L,U,b,n,x);
    free(U);
    free(L);
    free(D);
    return x;
}

double *LeastSquareFiniteElement(double *x, double *y, int n, int m, double h, double lambda)
{
    double **K=RequestMatrixDoubleMem(m,m);
    double *Phi=RequestVectorDoubleMem(m);
    double *F=RequestVectorDoubleMem(m);
    int *index=RequestVectorIntMem(m+1);

    int aux=0;
    for (int i=0;i<n;i++)
        {
            if (aux>1 && index[aux-1]==0)
            index[aux-1]=index[aux-2];
            if (x[i]>aux*h)
                {
                index[aux]=i;
                aux++;
                }
    }
    for (int i=aux;i<m+1;i++)
    index[i]=n-1;///index contiene los indices iniciales de cada intervalo

    //for (int i=0;i<m+1;i++)
      //  printf("%d %lf\n",index[i],x[index[i]]);

    for (int e=0;e<m-1;e++)
    {
        double f1=0.0,f2=0.0,c1=0.0,c2=0.0,c3=0.0;
        for (int i=index[e];i<index[e+1];i++)
        {
            double Ni=(h*(e+1)-x[i])/h;
            double Ninext=(x[i]-h*e)/h;
            f1+=y[i]*Ni;
            f2+=y[i]*Ninext;
            c1+=Ni*Ni;
            c2+=Ni*Ninext;
            c3+=Ninext*Ninext;
        }
        c1+=lambda/h;
        c2-=lambda/h;
        c3+=lambda/h;

        K[e][e]+=c1;
        K[e][e+1]+=c2;
        K[e+1][e]+=c2;
        K[e+1][e+1]+=c3;

        F[e]+=f1;
        F[e+1]+=f2;
    }

    /*for (int i=0;i<m;i++){
        for (int j=0;j<m;j++)
            printf("%.2lf ",K[i][j]);
        printf("\n");}

    for (int i=0;i<m;i++)
         printf("%.2lf ",F[i]);
    printf("\n");*/

    Phi=FactorizeTridiag(K,F,Phi,m);
return Phi;
}

int main()
{
    srand(time(NULL));
    int n=1000;
    int m=100;
    double lambda=0.00001;
    double xmin=0.0;
    double xmax=50.0;
    double h=(xmax-xmin)/m;

    double *x=RequestVectorDoubleMem(n);
    double *y=RequestVectorDoubleMem(n);

    for (int i=0;i<n;i++)
        x[i]=(xmax-xmin)*HybridTaus()+xmin;
    qsort(x,n,sizeof(double),cmpfunc);

    for (int i=0;i<n;i++)
        y[i]=fx(x[i])+2*HybridTaus()-1.0;

    printf("DAtos:\n");
     for (int i=0;i<n;i++)
        printf("%lf %lf\n",x[i],y[i]);

    double *Phi=LeastSquareFiniteElement(x,y,n,m,h,lambda);

    printf("valores de phi con m=100 y h=10:\n");
    for (int i=0;i<m;i++)
         printf("%lf\n",Phi[i]);

    return 0;
}
