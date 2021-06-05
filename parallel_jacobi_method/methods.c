#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "methods.h"
#include "memo.h"
#include <omp.h>
#define THREADS 4

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

   // for (int i=0;i<n;i++)
     //  printf("x[%d] = %lf \n",i,x_curr[i]);

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

    //for (int i=0;i<n;i++)
      // printf("x[%d] = %lf \n",i,x_next[i]);

}

