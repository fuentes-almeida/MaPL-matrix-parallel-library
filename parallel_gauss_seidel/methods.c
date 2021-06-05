#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "methods.h"
#include "memo.h"
#include <omp.h>
#define THREADS 4

double VectorXVector(double esca,double *A,double *B,int n)
{
    esca=0;
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

void SolveGaussSeidelSystem(double **MatrixA, double *b, int n,int max_count,double tolerance)
{
    omp_set_num_threads(THREADS);

    for (int i=0;i<n;i++)
        if (MatrixA[i][i]==0){
        printf("Error: diagonal null element detected");
        return;}

    double residuo=1e10,suma;
    int ncount;
    double *x_curr;
    x_curr=RequestVectorDoubleMem(n);

     #pragma omp parallel for
    for (int i=0;i<n;i++)
        x_curr[i]=b[i]/MatrixA[i][i];

         ncount=0;

    while(residuo>tolerance&&ncount<max_count){
            ncount++; residuo=0;
    #pragma omp parallel for private (suma)
       for (int i=0;i<n;i++){
        suma=0;
    #pragma omp parallel for reduction (+:suma)
        for (int j=0;j<n;j++){
            if(i!=j)
            suma+=MatrixA[i][j]*x_curr[j];}
        suma=(b[i]-suma)/MatrixA[i][i];
        residuo+=pow(suma-x_curr[i],2);
        x_curr[i]=suma;
       }
        residuo=sqrt(residuo)/n;
    }

    for (int i=0;i<n;i++)
    printf("x[%d] = %lf \n",i,x_curr[i]);

}

void SolveJacobiSystem(double **MatrixA, double *b, int n,int max_count,double tolerance)
{
    omp_set_num_threads(THREADS);

    for (int i=0;i<n;i++)
        if (MatrixA[i][i]==0){
        printf("Error: diagonal null element detected");
        return;}

    double residuo=1e10,suma;
    int ncount;
    double *x_curr,*x_next;
    x_curr=RequestVectorDoubleMem(n);
    x_next=RequestVectorDoubleMem(n);

    #pragma omp parallel for
    for (int i=0;i<n;i++)
        x_curr[i]=b[i]/MatrixA[i][i];

         ncount=0;
    while(residuo>tolerance&&ncount<max_count){

    #pragma omp parallel for private (suma)
       for (int i=0;i<n;i++){
        suma=0;
        #pragma omp parallel for reduction (+:suma)
        for (int j=0;j<n;j++){
            if(i!=j)
            suma+=MatrixA[i][j]*x_curr[j];}
        x_next[i]=(b[i]-suma)/MatrixA[i][i];
       }
        residuo=0;

      #pragma omp parallel for reduction (+:residuo)
        for (int i=0;i<n;i++){
            residuo+=pow(x_next[i]-x_curr[i],2);
            x_curr[i]=x_next[i];}

        residuo=sqrt(residuo)/n;
        ncount++;
    }

    for (int i=0;i<n;i++)
    printf("x[%d] = %lf \n",i,x_next[i]);

}

void GetMaxEigenVectorEigenValue(double **matrix,double *curr_vector,int n, double tolerance, int r_max)
{
    curr_vector=Normalize(curr_vector,n);
    int r=0;
    double lamda_curr=0;
    double *new_vector,*temp;
    temp=RequestVectorDoubleMem(n);
    new_vector=RequestVectorDoubleMem(n);

    while(r<r_max){
        r++;
        new_vector=MatrixXVector(matrix,curr_vector,new_vector,n);

        double num=VectorXVector(num,new_vector,new_vector,n);
        double den=VectorXVector(den,new_vector,curr_vector,n);

        double lamda_new=num/den;
        new_vector=Normalize(new_vector,n);

        if (fabs(lamda_new-lamda_curr)<tolerance){
            printf("El eigenvalor mayor es = %lf\n",lamda_new);
            printf("El eigenvector respectivo es:\n");
            for (int i=0;i<n;i++)
            printf("v[%d] = %lf\n",i,new_vector[i]);
            return;
        }
        for (int i=0;i<n;i++){
            temp[i]=curr_vector[i];
            curr_vector[i]=new_vector[i];
            new_vector[i]=temp[i];
        }
        lamda_curr=lamda_new;
        printf("%lf\n",tolerance);
    }
    printf("NO se encontro");

}
