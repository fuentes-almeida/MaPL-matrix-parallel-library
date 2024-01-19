#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include "memo.hpp"
#define pi 3.141592
#define N 100
#define M 100

// Estructura para guardar datos
typedef struct{
    double **GA,**Dz,**Ez,**Hx,**Hy;
    int nsteps,T;
}datos;




int main()
{
    int nsteps,npml;
    double dt,ddx,xn,xxn,xnum,xd,curl_e;
    double *gi2=RequestVectorDoubleMem(N);
    double *gi3=RequestVectorDoubleMem(N);
    double *gj2=RequestVectorDoubleMem(M);
    double *gj3=RequestVectorDoubleMem(M);
    double *fi1=RequestVectorDoubleMem(N);
    double *fi2=RequestVectorDoubleMem(N);
    double *fi3=RequestVectorDoubleMem(N);
    double *fj1=RequestVectorDoubleMem(M);
    double *fj2=RequestVectorDoubleMem(M);
    double *fj3=RequestVectorDoubleMem(M);
    double **iHx=RequestMatrixDoubleMem(N,M);
    double **iHy=RequestMatrixDoubleMem(N,M);

    printf("Numero de pasos: ");
    scanf("%d",&nsteps);

    datos *data=(datos*)malloc(sizeof(datos));
    data->Ez=RequestMatrixDoubleMem(N,M);
    data->Hx=RequestMatrixDoubleMem(N,M);
    data->Hy=RequestMatrixDoubleMem(N,M);
    data->Dz=RequestMatrixDoubleMem(N,M);
    data->GA=RequestMatrixDoubleMem(N,M);
    data->nsteps=nsteps;
    data->T=0;

    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            data->GA[i][j]=1.0;

    double t0=40.0;         //centro del pulso incidente
    double spread=15.0;     //ancho del pulso incidente
    ddx=0.01;
    dt=ddx/6e8;
   double epsz=8.8e-12;

    ///Calcular parametros de PML

    for (int i=0;i<N;i++){
        gi2[i]=1.0; gi3[i]=1.0;
        fi1[i]=0.0; fi2[i]=1.0; fi3[i]=1.0;}

    for (int j=0;j<M;j++){
        gj2[j]=1.0; gj3[j]=1.0;
        fj1[j]=0.0; fj2[j]=1.0; fj3[j]=1.0;}

    printf("Numero de celdas PML: ");
    scanf("%d",&npml);

    for (int i=0;i<=npml;i++)
    {
        xnum=npml-i;
        xd=npml;
        xxn=xnum/xd;
        xn=0.33*pow(xxn,3);

        gi2[i]=1.0/(1.0+xn);
        gi2[N-1-i]=1.0/(1.0+xn);
        gi3[i]=(1.0-xn)/(1.0+xn);
        gi3[N-1-i]=(1.0-xn)/(1.0+xn);
        xxn=(xnum-0.5)/xd;
        xn=0.25*pow(xxn,3);
        fi1[i]=xn;
        fi1[N-2-i]=xn;
        fi2[i]=1.0/(1.0+xn);
        fi2[N-2-i]=1.0/(1.0+xn);
        fi3[i]=(1.0-xn)/(1.0+xn);
        fi3[N-2-i]=(1.0-xn)/(1.0+xn);

    }

    for (int j=0;j<=npml;j++)
    {
        xnum=npml-j;
        xd=npml;
        xxn=xnum/xd;
        xn=0.33*pow(xxn,3);

        gj2[j]=1.0/(1.0+xn);
        gj2[M-1-j]=1.0/(1.0+xn);
        gj3[j]=(1.0-xn)/(1.0+xn);
        gj3[M-1-j]=(1.0-xn)/(1.0+xn);
        xxn=(xnum-0.5)/xd;
        xn=0.25*pow(xxn,3);
        fj1[j]=xn;
        fj1[M-2-j]=xn;
        fj2[j]=1.0/(1.0+xn);
        fj2[M-2-j]=1.0/(1.0+xn);
        fj3[j]=(1.0-xn)/(1.0+xn);
        fj3[M-2-j]=(1.0-xn)/(1.0+xn);

    }

     FILE *pipeOut=popen("gnuplot -persist","w");
     fprintf(pipeOut,"set xlabel 'x'\n");
     fprintf(pipeOut,"set xrange [ 0 : %d ] noreverse nowriteback\n",N-1);
     fprintf(pipeOut,"set ylabel 'y'\n ");
     fprintf(pipeOut,"set yrange [ 0 : %d ] noreverse nowriteback\n",M-1);
     fprintf(pipeOut,"set zrange [ 0 : 1 ] noreverse nowriteback\n");
     fprintf(pipeOut,"set view 50,20\n");
     fprintf(pipeOut,"set ticslevel 0\n");


    for (int k=0;k<data->nsteps;k++)
    {
        data->T++;        //cuenta las veces que el ciclo se ha ejecutado

        ///Lazo principal FDTD

        ///Calcular el campo Dz
        for(int j=1;j<N;j++)
            for (int i=1;i<N;i++)
                data->Dz[i][j]=data->Dz[i][j]*gi3[i]*gj3[j]+gi2[i]*gj2[j]*0.5*(data->Hy[i][j]-data->Hy[i-1][j]-data->Hx[i][j]+data->Hx[i][j-1]);

            ///Pulso Senoidal en el centro
            double pulse=exp(-0.5*(pow((t0-data->T)/spread,2)));
            //double pulse=sin(2*pi*1500*1e6*dt*data->T);
            data->Dz[N/2-5][M/2-5]=pulse;

            ///Calcular el campo Ez
            for(int j=1;j<M;j++)
                for (int i=1;i<N;i++)
                    data->Ez[i][j]=data->GA[i][j]*data->Dz[i][j];

            ///Poner el contorno a cero, como parte del PML
            for (int j=0;j<M-1;j++){
                data->Ez[0][j]=0.0;
                data->Ez[M-1][j]=0.0;}

            for (int i=0;i<N-1;i++){
                data->Ez[i][0]=0.0;
                data->Ez[i][N-1]=0.0;}

            ///Calcular el campo Hx
            for(int j=0;j<M-1;j++)
                for (int i=0;i<N;i++){
                    iHx[i][j]+=fi1[i]*(data->Ez[i][j]-data->Ez[i][j+1]);
                    data->Hx[i][j]=fj3[j]*data->Hx[i][j]+fj2[j]*0.5*(data->Ez[i][j]-data->Ez[i][j+1]+iHx[i][j]);}

            ///Calcular el campo Hy
            for(int j=0;j<M-1;j++)
                for (int i=0;i<N-1;i++){
                    iHy[i][j]+=fj1[j]*(data->Ez[i+1][j]-data->Ez[i][j]);
                    data->Hy[i][j]=fi3[i]*data->Hy[i][j]+fi2[i]*0.5*(data->Ez[i+1][j]-data->Ez[i][j]+iHy[i][j]);}

        ///Fin del lazo principal

	double MAX = -9999999999999;
	double MIN = 99999999999999;
	// Buscamos el maximo y el minimo
    for(int j=0;j<M;j++)
        for (int i=0;i<N;i++){
            if( data->Ez[i][j]<MIN )
                MIN = data->Ez[i][j];
            if( data->Ez[i][j]>MAX)
                MAX = data->Ez[i][j];
        }

        //Nomalizamos
    for(int j=0;j<M;j++)
        for (int i=0;i<N;i++)
             data->Ez[i][j] = (data->Ez[i][j]-MIN)/(MAX-MIN);

    FILE *output=fopen("matrix.txt","w");
        for(int i=0;i<N;i++){
            for (int j=0;j<M;j++)
                fprintf(output,"%lf ",data->Ez[i][j]);
            fprintf(output,"\n");}
        fclose(output);
        fprintf(pipeOut,"plot 'matrix.txt' matrix with image \n");

         fflush(pipeOut);
         usleep(10000);
    }
    pclose(pipeOut);
    free(data->Ez);
    free(data->Hx);
    free(data->Hy);
    free(data->GA);
    free(data->Dz);
    free(data);
    return 0;
}
