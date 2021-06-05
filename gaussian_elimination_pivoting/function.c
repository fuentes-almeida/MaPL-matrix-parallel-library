#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "function.h"
#include <math.h>

void GaussianElimination(double **A,double *b, int n,double *x)
{

    //eliminacion Gaussiana
    for (int k =0;k<n-1;k++){
        for (int i=k+1;i<n;i++){
            double m=A[i][k]/A[k][k];
            for (int j=k+1;j<n;j++)
                A[i][j]=A[i][j]-m*A[k][j];
            A[i][k]=0;
            b[i]=b[i]-m*b[k];
        }
    }
    //resolucion del sistema por sustitucion hacia atras
    for (int i=n-1; i>=0;i--){
        double suma=0;
        for (int j=i+1;j<n;j++)
            suma+=A[i][j]*x[j];
        x[i]=(b[i]-suma)/A[i][i];
    }
}

void GaussianEliminationPivoting(double  **A, double *b, int n,double *x)
{
    double temp;
    int *index;
    index=RequestVectorIntMem(n);

    for (int i=1;i<n;i++)
        index[i]=i;

    for (int k=0; k<n; k++){
        double max=0;
        int fmax=k;
        int cmax=k;

        for (int i=k; i<n;i++){     //encuentra el elemento con mayor valor absoluto en la matrz A
            for(int j=k;j<n;j++){
                if (max<fabs(A[i][j])){
                    max=fabs(A[i][j]); //almacena su valor, fila y columna
                    fmax=i;
                    cmax=j;
                }
            }
        }

        if (fmax!=k){
            for (int j=0;j<n;j++){  //se intercambia la fila k por la fila fmax en la matriz A
                 temp=A[k][j];
                A[k][j]=A[fmax][j];
                A[fmax][j]=temp;
            }
            temp=b[k];      //se intercambia el elemento k por el elemento fmax en el vector de terminos independientes
            b[k]=b[fmax];
            b[fmax]=temp;
        }

        if (cmax!=k){
            for (int i=0;i<n;i++){ //se intercambia la columna k por la columna cmax
                temp=A[i][k];
                A[i][k]=A[i][cmax];
                A[i][cmax]=temp;
            }
            temp=index[k];   //estos cambios se guardan en un vector de indices para luego acomodar el vector solucion correctamente
            index[k]=index[cmax];
            index[cmax]=temp;
        }
    }

    GaussianElimination(A,b,n,x);//llamada a guncion de eliminacion gaussiana

    int k=0;
    for (int i=n-1; i>=0;i--){  //se hace un swap a los terminos del vector solucion para ordenarlos
        for (int j=0; j<n;j++){
            if (index[j]==i)
                k=j;
                }
        temp=x[k];
        x[k]=x[i];
        x[i]=temp;
        int temp2=index[k];
        index[k]=index[i];
        index[i]=temp2;
        }

 free(index);
}
