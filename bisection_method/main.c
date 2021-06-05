#include <stdio.h>
#include <math.h>

double f(double);
void biseccion(double, double, int, double);

int main()
{
  int max_iter=100; // número maximo de iteraciones
  int i;
  double a, b; // extremos izquierdo y derecho del intervalo inicial
  double tolerance=0.0005; // tolerancia
  printf("Buscando las raices de la ecuacion 1/x + x^2 - 10...\n");
  for (i=0;i<=1000;i++){
    a=-5+0.01*i;
    b=-5+0.01*(i+1);
    biseccion(a, b, max_iter, tolerance);
  }
  return 0;
}
// funcion f(x) para evaluar
double f(double x){return (1/x+x*x-10);}

void biseccion(double a, double b, int max_iter, double tolerance)
{
  int i;             // contador de iteraciones
  double x1, x2, x3; // punto inicial, intermedio y final del intervalo actual
  x1 = a;
  x3 = b;
  if (f(x1) * f(x3) < 0.0){ // verifica si hay una raiz en el intervalo
        for (i = 1; i <= max_iter; i++)
        {
          x2 = (x1 + x3) / 2.0;// encuentra cual mitad del intervalo contiene la raiz
          if (f(x1) * f(x2) <= 0.0){ // la raiz esta en la mitad izquierda del intervalo
            x3 = x2;
          }
          else{
            x1 = x2;// la raiz esta en la mitad derecha del intervalo
          }
          if (fabs(f(x2)) < tolerance){
            printf("\nSe encontro una raiz en x = %lf ",x2);
            return;
          }
        }
    }

  return;
}
