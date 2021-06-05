#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include "fdtd.hpp"
#include "memo.hpp"
#include <omp.h>
#define THREADS 4

int main()
{
    omp_set_num_threads(THREADS);
    FILE *pipeOut=popen("gnuplot -persist","w");
    fprintf(pipeOut,"set xlabel 'x'\n");
    fprintf(pipeOut,"set xrange [ 0 : %d ] noreverse nowriteback\n",N-1);
    fprintf(pipeOut,"set ylabel 'y'\n ");
    fprintf(pipeOut,"set yrange [ 0 : %d ] noreverse nowriteback\n",M-1);

    datos* data=RequestDataMemory();
    layer* PML=RequestLayerMemory();
    int i,j;
    ///PML por default apagado
    #pragma omp parallel for
    for (i=0;i<N;i++){
        PML->gi2[i]=1.0; PML->gi3[i]=1.0;
        PML->fi1[i]=0.0; PML->fi2[i]=1.0; PML->fi3[i]=1.0;}
    #pragma omp parallel for
    for (j=0;j<M;j++){
        PML->gj2[j]=1.0; PML->gj3[j]=1.0;
        PML->fj1[j]=0.0; PML->fj2[j]=1.0; PML->fj3[j]=1.0;}

    printf("Numero de pasos: ");
    scanf("%d",&data->nsteps);
    data->T=0;

    printf("Numero de celdas PML: ");
    scanf("%d",&PML->PML_cells);
    SetX_PML_cells(PML);
    SetY_PML_cells(PML);

    printf("Origen del pulso: ");
    scanf("%d %d",&data->X,&data->Y);

    printf("Senoidal(1), Gausiano(2): ");
    scanf("%d",&data->flag);

    if (data->flag==1){
        printf("Frecuencia del pulso: ");
        scanf("%lf",&data->freq);}
    else{
        printf("Ancho del pulso: ");
        scanf("%lf",&data->width);}

    ///Cilindro dielectrico
    SetDielectric(data);

    for (int k=0;k<data->nsteps;k++)
    {
        data->T++;        //cuenta los pasos
        FDTD_2D(data,PML);
        //fprintf(pipeOut,"plot 'matrix.txt' matrix with image \n");
        //fflush(pipeOut);
        //usleep(10000);
    }

    pclose(pipeOut);
    FreeDataMemory(data);
    FreeLayerMemory(PML);

    return 0;
}
