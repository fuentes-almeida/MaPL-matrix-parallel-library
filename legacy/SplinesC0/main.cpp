#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "memo.hpp"

#define length 800
#define width 600
#define datasize 800

using namespace std;
//g++ -Wall -g main.cpp fparser/fparser.cc `pkg-config --cflags --libs gtk+-3.0` -o main

 double **curve1,**curve2,**curve3;
 double xmin,xmax,xmid1,xmid2;
 int n1,n2,n3;

//escala y factor de corrimiento
 double xscale=1.0, yscale=1.0;
 double xoffset=0.0, yoffset=0.0;

// Ventana y área de dibujo
GtkWidget *window;
GtkWidget *areaDib;

// Estructura para guardar datos
typedef struct{
    int tam;

    }datos;

double splineC0(double x)
{
    double **curve;
    if (x<xmid1){
    curve=curve1;}
    else if(x<xmid2){
    curve=curve2;}
    else {
    curve=curve3;}
    int k=0;

    while(x>curve[0][k])
        k++;

    double s=curve[1][k-1]+(curve[1][k]-curve[1][k-1])/(curve[0][k]-curve[0][k-1])*(x-curve[0][k-1]);

    return s;
}


//Funcion para dibujar
static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer par)
    {
	double grosor, red, green, blue, trans, tamText;
     	double xdelta,factor;
   	int i,j,k;

    double *xvalue=RequestVectorDoubleMem(datasize);
    double *yvalue1=RequestVectorDoubleMem(datasize);

    //Asignar x y fx a dos vectores
	xdelta=(xmax-xmin)/length;
	factor=1/xdelta;

	for(k=0;k<length;k++)
        {
        xvalue[k]=(xmin+k*xdelta)*xscale+xoffset;
        yvalue1[k]=splineC0(xvalue[k])*yscale+yoffset;
        }

    //Limpiar la pantalla
    cairo_set_source_rgba (cr, 1, 1, 1, 1);
    cairo_set_operator (cr, CAIRO_OPERATOR_SOURCE);
    cairo_paint (cr);

	// Donde se va a pintar
	GdkWindow *sup = gtk_widget_get_window ( widget );

	// Crea un pincel
	cairo_t *pincel = gdk_cairo_create( sup );

	// Dibuja una linea
	grosor = 1.0;  	// Grosor
	red = 0.0;     	// Nivel de rojo
	green = 0.0;    // Nivel de verde
	blue = 0.0;     // Nivel de azul
	trans = 0.3;    // Transparencia

	cairo_set_source_rgba( pincel, red, green, blue, trans );
	cairo_set_line_width( pincel, grosor );

    //Ejes coodenados y cuadricula
    for (j=0;j<=length;j+=50)
        {
        cairo_move_to(pincel, j,0);
        cairo_line_to(pincel, j,width);
        cairo_move_to(pincel,0,j);
        cairo_line_to(pincel,length,j);
        cairo_stroke(pincel);
        }
	grosor = 1.0;  	// Grosor
	red = 0.0;     	// Nivel de rojo
	green = 0.0;    // Nivel de verde
	blue = 0.0;     // Nivel de azul
	trans = 0.5;    // Transparencia

	cairo_set_source_rgba( pincel, red, green, blue, trans );
	cairo_set_line_width( pincel, grosor );

        cairo_move_to(pincel, 0,width/2-factor*yoffset);
        cairo_line_to(pincel, length, width/2-factor*yoffset);
        cairo_move_to(pincel,length/2,0);
        cairo_line_to(pincel,length/2,width);
	cairo_stroke(pincel);

	// Texto
	tamText = 10.0;
	cairo_set_font_size( pincel, tamText );
	cairo_set_source_rgba( pincel, 0.0, 0.0, 0.0, 1.0 );

    float xindex;
    char text[15];
    for (k=0; k<=length;k+=50)
    {
    xindex = xvalue[k];
    sprintf(text, "%.2f", xindex);
    cairo_move_to( pincel,k, width/2-3);
    cairo_line_to(pincel,k,width/2+3);
    cairo_move_to( pincel,k, width/2-1);
    cairo_show_text(pincel,text);
    cairo_stroke(pincel);
    }

	// Dibuja una linea
	grosor = 2.5;     // Grosor
	red = 0.0;        // Nivel de rojo
	green = 0.0;      // Nivel de verde
	blue = 0.5;       // Nivel de azul
	trans = 1.0;      // Transparencia

	cairo_set_source_rgba( pincel, red, green, blue, trans );
	cairo_set_line_width( pincel, grosor );

	for (i=0; i<length-1; i++)
        {
        cairo_move_to( pincel, i, width/2-factor*yvalue1[i] );
        cairo_line_to( pincel, i+1, width/2-factor*yvalue1[i+1] );
        }
        cairo_stroke(pincel);

	return FALSE;
}

gboolean desplaza(GtkWidget *widget, GdkEventKey *event, gpointer aux)
{
    // Donde se va a pintar
	GdkWindow *sup = gtk_widget_get_window ( widget );

    // Crea un pincel
	cairo_t *pincel = gdk_cairo_create( sup );

	cairo_set_source_rgba(pincel,1.0,0.0,0.0,1.0);
	cairo_set_line_width(pincel,2.0);
   	gpointer *par=NULL;

       switch(event->keyval)
       {
        case 'z':xscale=xscale+0.1;
        draw_cb(areaDib,pincel,par);break;

        case 'x':xscale=xscale-0.1;
        if (xscale<0) xscale=0;
        draw_cb(areaDib,pincel,par);break;

        case 'a':yscale=yscale+0.1;
        draw_cb(areaDib,pincel,par);break;

        case 's':yscale=yscale-0.1;
        if (yscale<0) yscale=0;
        draw_cb(areaDib,pincel,par);break;

        case 'c':xoffset=xoffset+0.1;
        draw_cb(areaDib,pincel,par);break;

        case 'v':xoffset=xoffset-0.1;
        draw_cb(areaDib,pincel,par);break;

        case 'd':yoffset=yoffset+0.1;
        draw_cb(areaDib,pincel,par);break;

        case 'f':yoffset=yoffset-0.1;
        draw_cb(areaDib,pincel,par);break;
        }
       cairo_stroke(pincel);

return FALSE;
}

int main(int argc, char *argv[])
{
    scanf("%d",&n1);
    curve1=RequestMatrixDoubleMem(2,n1);
    for (int i=0;i<n1;i++)
        scanf("%lf %lf",&curve1[0][i],&curve1[1][i]);

    scanf("%d",&n2);
    curve2=RequestMatrixDoubleMem(2,n2);
    for (int i=0;i<n2;i++)
        scanf("%lf %lf",&curve2[0][i],&curve2[1][i]);

    scanf("%d",&n3);
    curve3=RequestMatrixDoubleMem(2,n3);
    for (int i=0;i<n3;i++)
        scanf("%lf %lf",&curve3[0][i],&curve3[1][i]);

    xmin=curve1[0][0];
    xmid1=curve2[0][0];
    xmid2=curve3[0][0];
    xmax=curve3[0][n3-1];

	// Datos que deseamos pasar a la funcion que grafica
	datos *par = (datos*)malloc(1 * sizeof(datos));
	par->tam = 50;

	// Inicia gtk
	gtk_init( &argc, &argv );

	// Tìtulo y dimensiones de la ventana
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_title(GTK_WINDOW(window), "GRAFICADOR 1.0");

	// Para cerrar
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	// Área de dibujo
	areaDib = gtk_drawing_area_new( );
	gtk_widget_set_size_request ( areaDib, length, width );

	// Llama a la función para dibujar la gráfica
	g_signal_connect( areaDib, "draw", G_CALLBACK(draw_cb), par );

    	//Para desplazar la vista y hacer zoom
  	  g_signal_connect(G_OBJECT(window),"key_press_event",
                    G_CALLBACK(desplaza), NULL);

	// Borde de la ventana
	gtk_container_set_border_width(GTK_CONTAINER(window), 15);
	// Agrega a la ventana lo que se dinujó
	gtk_container_add (GTK_CONTAINER (window), areaDib);
	// Muestra el área de dibujo
	gtk_widget_show( areaDib );
	// Muestra la ventana
	gtk_widget_show( window );

	gtk_main( );

	free(par);

    freeMatrizDouble(curve1,2);
    freeMatrizDouble(curve2,2);
    freeMatrizDouble(curve3,2);
	return 0;
}
