#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "memo.h"

///Simulacion FDTD en 1D en el vacio

#define N 200 //numero de nodos a utilizarse

int main()
{

    double *Ex=RequestVectorDoubleMem(N);
    double *Hy=RequestVectorDoubleMem(N);

    for (int i=0;i<N;i++)
    {
        Ex[i]=0.0;
        Hy[i]=0.0;
    }

    int center=N/2;         //centro del espacio
    double t0=40.0;         //centro del pulso incidente
    double spread=12.0;     //ancho del pulso incidente
    double T=0.0;
    int nsteps=1;

    while (nsteps>0)
    {
        printf("nsteps--->");
        scanf("%d",&nsteps);
        printf("%d\n",nsteps);

        for (int j=1;j<nsteps;j++)
        {
            T=T+1.0;        //cuenta las veces que el ciclo se ha ejecutado

        ///Lazo principal FDTD

            ///Calcular el campo Ex
            for(int k=1;k<N;k++)
                Ex[k]=Ex[k]+0.5*(Hy[k-1]-Hy[k]);

            ///Pulso Gaussiano en el centro
            double pulse=exp(-0.5*(pow((t0-T)/spread,2)));
            Ex[center]=pulse;
            printf("%5.1lf %6.2lf\n",t0-T,Ex[center]);

            ///Calcular el campo Hy
            for (int k=0;k<N;k++)
                Hy[k]=Hy[k]+0.5*(Ex[k]-Ex[k+1]);

        ///Fin del lazo principal

            for (int k=1;k<=N;k++)
                printf("%3d  %6.3lf   %6.3lf",k,Ex[k],Hy[k]);

            FILE *output;

            output=fopen("Ex.dat","w");
            for (int k=1;k<=N;k++)
                fprintf(output,"%lf\n",Ex[k]);
            fclose(output);

            output=fopen("Hy.dat","w");
            for (int k=1;k<=N;k++)
                fprintf(output,"%lf\n",Hy[k]);
            fclose(output);

            printf("T=%lf\n",T);


        }
    }

}
