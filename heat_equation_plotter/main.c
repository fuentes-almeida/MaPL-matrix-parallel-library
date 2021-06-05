#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"

    int n,i;
    double largo,k,Q,phi0,phin;
    double *b,*Phi, *Phimed;
    double *L,*D;

// Tamaño de la venta de visulazición
int length = 800; // Pixeles
int width = 600; // Pixeles


// Ventana y área de dibujo
GtkWidget *window;
GtkWidget *areaDib;

// Estructura para guardar datos
typedef struct{
    int tam;
    }datos;

//Funcion para dibujar
static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer par)
    {
	double grosor, red, green, blue, trans, tamText;

   	int i,j;


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

	// Texto
	tamText = 10.0;
	cairo_set_font_size( pincel, tamText );
	cairo_set_source_rgba( pincel, 0.0, 0.0, 0.0, 1.0 );

    char text[10];
    sprintf(text, "%.2f", Phimed[800-1]);
    cairo_move_to( pincel,600, width/2-5);
    cairo_show_text(pincel,text);
    cairo_move_to( pincel,600, width/2-20);
    cairo_show_text(pincel,"Valor de convergencia:");
    cairo_stroke(pincel);

    	// Texto
	tamText = 20.0;
	cairo_set_font_size( pincel, tamText );
	cairo_set_source_rgba( pincel, 0.0, 0.0, 0.0, 1.0 );
    cairo_move_to( pincel,200, 20);
    cairo_show_text(pincel,"Grafica del nodo medio vs 2 a 1600 nodos");

	// Dibuja una linea
	grosor = 1.5;     // Grosor
	red = 0.0;        // Nivel de rojo
	green = 0.0;      // Nivel de verde
	blue = 0.5;       // Nivel de azul
	trans = 1.0;      // Transparencia

	cairo_set_source_rgba( pincel, red, green, blue, trans );
	cairo_set_line_width( pincel, grosor );

	double MAX = -9999999999999;
	double MIN = 99999999999999;

		for( int i=0; i<800; i++){
		if( Phimed[i]<MIN )
			MIN = Phimed[i];
		if( Phimed[i]>MAX)
			MAX = Phimed[i];
	}


	for (i=0; i<length-1; i++)
        {
        cairo_move_to( pincel, i, ((Phimed[i]-MIN)/(MAX-MIN))*width/2 );
        cairo_line_to( pincel, i+1, ((Phimed[i+1]-MIN)/(MAX-MIN))*width/2);
        }

	// Pinta lo que se ha hecho
	cairo_stroke(pincel);

	return FALSE;
}


int main(int argc, char *argv[])
{

    int m=0;
    scanf("%lf %lf %lf %lf %lf",&largo,&k,&Q,&phi0,&phin);
    Phimed=RequestVectorDoubleMem(800);

    for (n=2;n<=1600;n+=2){
    double xdelta=largo/n;

    b=RequestVectorDoubleMem(n-1);
    Phi=RequestVectorDoubleMem(n-1);
    L=RequestVectorDoubleMem(n-2);
    D=RequestVectorDoubleMem(n-1);

    for (i=0;i<n-2;i++)
    L[i]=-1;

    for (i=0;i<n-1;i++){
    b[i]=Q*xdelta;
    D[i]=2;}
    b[0]+=phi0;
    b[n-2]+=phin;

    for (i=0;i<n-1;i++)
    b[i]=b[i]*xdelta/k;

 Phi=SolveTriDiagMatrix(D,L,L,b,n-1,Phi);

Phimed[m]=Phi[n/2];
printf("%lf\n",Phimed[m]);
m++;
free(b);
free(Phi);
free(L);
free(D);

    }

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


    return 0;
}
