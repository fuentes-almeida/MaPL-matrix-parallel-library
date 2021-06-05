#include <stdio.h>
#include <stdlib.h>
#include "memo.h"
#include <math.h>
#include "function.h"

double VectorXVector(double *A,double *B,int n)
{
    double esca=0;
    for (int i=0;i<n;i++)
        esca+=A[i]*B[i];
    return esca;
}

double *MatrixXVector(double **matrix, double *vector, double *product, int n)
{
    for (int i=0;i<n;i++){
            double suma=0;
        for(int j=0;j<n;j++){
            suma+=matrix[i][j]*vector[j];
        }
        product[i]=suma;
    }
    return product;
}

double *GradienteConjugado(double **A, double *b, double *x,int n,double epsilon, int ite_max)
{
    int count=0;
    double *r=RequestVectorDoubleMem(n);
    double *p=RequestVectorDoubleMem(n);
    double *w=RequestVectorDoubleMem(n);

    for (int i=0;i<n;i++){
        r[i]=-b[i];
        p[i]=-r[i];
    }

    double rtr=VectorXVector(r,r,n);

    while(sqrt(rtr)>epsilon && count<ite_max)
    {
        count++;
        w=MatrixXVector(A,p,w,n);
        //double rtp=VectorXVector(r,p,n);
        double ptw=VectorXVector(p,w,n);
        double alpha=rtr/ptw;

        for (int i=0;i<n;i++){
            x[i]+=alpha*p[i];
            r[i]+=alpha*w[i];}

        double rtr2=VectorXVector(r,r,n);

        double beta=rtr2/rtr;

        for (int i=0;i<n;i++)
            p[i]=-r[i]+beta*p[i];

        rtr=rtr2;
    }

    free(r);
    free(p);
    free(w);

    if (sqrt(rtr)<epsilon){printf("Resultado en %d iteraciones\n",count);return x;}
    else {printf("Se excedio el maximo de iteraciones\n");return NULL;}
}
