#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "memo.h"
#include "gauss.h"

int main()
{
    func *fxyz=(func*)malloc(3*sizeof(func));
    fxyz[0]=fxyz1;
    fxyz[1]=fxyz2;
    fxyz[2]=fxyz3;

    int ref;
    double a1,b1,a2,b2,a3,b3;

    printf("Intervalo variable x: ");
    scanf("%lf %lf",&a1,&b1);
    printf("Intervalo variable y: ");
    scanf("%lf %lf",&a2,&b2);
    printf("Intervalo variable z: ");
    scanf("%lf %lf",&a3,&b3);
    printf("Referencia a funcion: ");
    scanf("%d",&ref);

    printf("\n");
    for (int i=1;i<=10;i++)
    {
    double result=GaussQuadrature(i,a1,b1,a2,b2,a3,b3,fxyz[ref-1]);
    printf("para n=%d\tresultado=%lf\n",i,result);
    }
    return 0;
}
