#ifndef FDTD_HPP_INCLUDED
#define FDTD_HPP_INCLUDED
#define pi 3.141592
#define N 100
#define M 100

// Estructura para guardar datos
typedef struct{
    double **dielectric,**Dz,**Ez,**Hx,**Hy;
    int nsteps,T,X,Y,flag;
    double freq,width;
}datos;

typedef struct{
    double *gi2,*gi3,*gj2,*gj3;
    double *fi1,*fi2,*fi3,*fj1,*fj2,*fj3;
    double **iHx, **iHy;
    int PML_cells;
}layer;

double GaussianPulse(double t, double width, int i);
void FDTD_2D(datos* data, layer *PML);
void SetX_PML_cells(layer *PML);
void SetY_PML_cells(layer *PML);
datos *RequestDataMemory();
layer *RequestLayerMemory();
void FreeDataMemory(datos *data);
void FreeLayerMemory(layer *PML);
void SetDielectric(datos* data);

#endif // FDTD_HPP_INCLUDED
