#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include "fdtd.hpp"
#include "memo.hpp"
#include <omp.h>
#define THREADS 4

double GaussianPulse(double t, double width, int i)
{
    return exp(-0.5*(pow((t-i)/width,2)));
}

void SetX_PML_cells(layer *PML)
{
    for (int i=0;i<PML->PML_cells;i++)
    {
        double xnum=PML->PML_cells-i;
        double xd=PML->PML_cells;
        double xxn=xnum/xd;
        double xn=0.33*pow(xxn,3);

        PML->gi2[i]=1.0/(1.0+xn);
        PML->gi2[N-1-i]=1.0/(1.0+xn);
        PML->gi3[i]=(1.0-xn)/(1.0+xn);
        PML->gi3[N-1-i]=(1.0-xn)/(1.0+xn);
        xxn=(xnum-0.5)/xd;
        xn=0.25*pow(xxn,3);
        PML->fi1[i]=xn;
        PML->fi1[N-2-i]=xn;
        PML->fi2[i]=1.0/(1.0+xn);
        PML->fi2[N-2-i]=1.0/(1.0+xn);
        PML->fi3[i]=(1.0-xn)/(1.0+xn);
        PML->fi3[N-2-i]=(1.0-xn)/(1.0+xn);
    }
}

void SetY_PML_cells(layer *PML)
{
    for (int j=0;j<PML->PML_cells;j++)
    {
        double xnum=PML->PML_cells-j;
        double xd=PML->PML_cells;
        double xxn=xnum/xd;
        double xn=0.33*pow(xxn,3);

        PML->gj2[j]=1.0/(1.0+xn);
        PML->gj2[M-1-j]=1.0/(1.0+xn);
        PML->gj3[j]=(1.0-xn)/(1.0+xn);
        PML->gj3[M-1-j]=(1.0-xn)/(1.0+xn);
        xxn=(xnum-0.5)/xd;
        xn=0.25*pow(xxn,3);
        PML->fj1[j]=xn;
        PML->fj1[M-2-j]=xn;
        PML->fj2[j]=1.0/(1.0+xn);
        PML->fj2[M-2-j]=1.0/(1.0+xn);
        PML->fj3[j]=(1.0-xn)/(1.0+xn);
        PML->fj3[M-2-j]=(1.0-xn)/(1.0+xn);
    }
}

void SetDielectric(datos* data)
{
    omp_set_num_threads(THREADS);
    int radius,x_center,y_center,xdist,ydist;
    double epsilon;
    double sigma;
    int i,j;
     #pragma omp parallel for
    for(i=0;i<N;i++)
        for(int j=0;j<M;j++)
            data->dielectric[i][j]=1.0;
    printf("Radio del dielectrico: ");
    scanf("%d",&radius);

    if (radius>0)
    {
        printf("Centro del dielectrico: ");
        scanf("%d %d",&x_center, &y_center);
        printf("Constante dielectrica: ");
        scanf("%lf",&epsilon);
        printf("Conductividad: ");
        scanf("%lf",&sigma);

        #pragma omp parallel for
        for ( i=x_center-radius;i<x_center+radius;i++)
            for( j=y_center-radius;j<y_center+radius;j++)
            {
                xdist=x_center-i;
                ydist=y_center-j;
                double dist=sqrt(pow(xdist,2)+pow(ydist,2));
                if (dist<=radius)
                {
                    double aux=1/(epsilon+(sigma*(0.01/6e8)/8.0e-12));
                    data->dielectric[i][j]=aux;
                }
            }
    }

}


void FDTD_2D(datos* data, layer *PML)
{

    omp_set_num_threads(THREADS);
    int i,j;

    ///Calcular Dz
    for( j=1;j<M;j++)
        #pragma omp parallel for
        for ( i=1;i<N;i++)
            data->Dz[i][j]=PML->gi3[i]*PML->gj3[j]*data->Dz[i][j]
            +PML->gi2[i]*PML->gj2[j]*0.5*(data->Hy[i][j]-data->Hy[i-1][j]-data->Hx[i][j]+data->Hx[i][j-1]);

    ///Pulso de Origen
    double pulse=0.0;
    if (data->flag==1)
        pulse=sin(2*pi*data->freq*1e6*data->T*(0.01/6e8));
    else
        pulse=GaussianPulse(20.0,data->width,data->T);
    data->Dz[data->Y][data->X]=pulse;

    ///Calcular Ez
    for( j=1;j<M;j++)
        #pragma omp parallel for
        for ( i=1;i<N;i++)
            data->Ez[i][j]=data->dielectric[i][j]*data->Dz[i][j];

    ///Poner contorno en cero
    if (PML->PML_cells>0){
    #pragma omp parallel for
    for ( j=0;j<M-1;j++){
        data->Ez[0][j]=0.0;
        data->Ez[M-1][j]=0.0;}
    #pragma omp parallel for
    for ( i=0;i<N-1;i++){
        data->Ez[i][0]=0.0;
        data->Ez[i][N-1]=0.0;}}

    ///Calcular Hx
    for( j=0;j<M-1;j++)
        #pragma omp parallel for
        for ( i=0;i<N;i++){
            PML->iHx[i][j]+=PML->fi1[i]*(data->Ez[i][j]-data->Ez[i][j+1]);
            data->Hx[i][j]=PML->fj3[j]*data->Hx[i][j]+PML->fj2[j]*0.5*(data->Ez[i][j]-data->Ez[i][j+1]+PML->iHx[i][j]);}

    ///Calcular el campo Hy
    for( j=0;j<M-1;j++)
        #pragma omp parallel for
        for ( i=0;i<N-1;i++){
            PML->iHy[i][j]+=PML->fj1[j]*(data->Ez[i+1][j]-data->Ez[i][j]);
            data->Hy[i][j]=PML->fi3[i]*data->Hy[i][j]+PML->fi2[i]*0.5*(data->Ez[i+1][j]-data->Ez[i][j]+PML->iHy[i][j]);}

    ///Guardamos Ex en un archivo
    FILE *output=fopen("matrix.txt","w");
    for( i=0;i<N;i++){
        for ( j=0;j<M;j++)
            fprintf(output,"%lf ",data->Ez[i][j]);
        fprintf(output,"\n");}
    fclose(output);
}

datos *RequestDataMemory()
{
    datos *data;
    data=(datos*)malloc(sizeof(datos));    data->Ez=RequestMatrixDoubleMem(N,M);
    data->Hx=RequestMatrixDoubleMem(N,M);
    data->Hy=RequestMatrixDoubleMem(N,M);
    data->Dz=RequestMatrixDoubleMem(N,M);
    data->dielectric=RequestMatrixDoubleMem(N,M);
    return data;
}

layer *RequestLayerMemory()
{
    layer *PML;
    PML=(layer*)malloc(sizeof(layer));
    PML->gi2=RequestVectorDoubleMem(N);
    PML->gi3=RequestVectorDoubleMem(N);
    PML->gj2=RequestVectorDoubleMem(M);
    PML->gj3=RequestVectorDoubleMem(M);
    PML->fi1=RequestVectorDoubleMem(N);
    PML->fi2=RequestVectorDoubleMem(N);
    PML->fi3=RequestVectorDoubleMem(N);
    PML->fj1=RequestVectorDoubleMem(M);
    PML->fj2=RequestVectorDoubleMem(M);
    PML->fj3=RequestVectorDoubleMem(M);
    PML->iHx=RequestMatrixDoubleMem(N,M);
    PML->iHy=RequestMatrixDoubleMem(N,M);
    return PML;
}

void FreeDataMemory(datos *data)
{
    free(data->Ez);
    free(data->Hx);
    free(data->Hy);
    free(data->dielectric);
    free(data->Dz);
    free(data);
}

void FreeLayerMemory(layer *PML)
{
    free(PML->gi2);
    free(PML->gi3);
    free(PML->gj2);
    free(PML->gj3);
    free(PML->fi1);
    free(PML->fi2);
    free(PML->fi3);
    free(PML->fj1);
    free(PML->fj2);
    free(PML->fj3);
    freeMatrizDouble(PML->iHx,M);
    freeMatrizDouble(PML->iHy,M);
    free(PML);
}
