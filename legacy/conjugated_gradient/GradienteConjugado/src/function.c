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

double *GradienteConjugado(double **A, double *b, double *x,int n,double tolerance, int ite_max)
{
    double *r=RequestVectorDoubleMem(n);
    double *p=RequestVectorDoubleMem(n);
    double *w=RequestVectorDoubleMem(n);

    for (int i=0;i<n;i++){
        r[i]=b[i];
        p[i]=r[i];
    }

    double modulus=1;
    int count=0;

    while(modulus>tolerance&&count<ite_max)
    {
        count++;
        w=MatrixXVector(A,p,w,n);
        double alpha=VectorXVector(p,r,n)/VectorXVector(p,w,n);

        for (int i=0;i<n;i++){
            x[i]+=alpha*p[i];
            r[i]-=alpha*w[i];}

        modulus=sqrt(VectorXVector(r,r,n));
        if (modulus<tolerance){
            free(r);
            free(p);
            free(w);
            printf("Resultado en %d iteraciones\n",count);
            return x;}

        double beta=VectorXVector(w,r,n)/VectorXVector(w,p,n);
        for (int i=0;i<n;i++){
            p[i]=r[i]-beta*p[i];
            }
    }
    free(r);
    free(p);
    free(w);
    printf("Se excedio el maximo de iteraciones\n");
    return NULL;
}
