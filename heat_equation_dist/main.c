#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <cairo.h>
#include <stdlib.h>
#include "matrix.h"

    int n;
    double *Phi;
    double Len,k,Q,phi0,phin;
// Estructura para guardar datos
typedef struct{
	int tam;
}datos;

// Funcion para dibujar
static gboolean draw_cb( GtkWidget *widget, cairo_t *cr, gpointer par ){

	double grosor, r, g, b;

	// Donde se va a pintar
	GdkWindow *sup = gtk_widget_get_window ( widget );

	// Crea un pincel
	cairo_t *pincel = gdk_cairo_create( sup );

	// Parametrosde la linea
	grosor = 50.0;  // Grosor


	int i;
	double Delta = (750-50)/(double)(n-1); // 750 es la coordenada del limite superior de mi barra. 50 es el limite inferior.

	double MAX = -9999999999999;
	double MIN = 99999999999999;
	// Buscamos el maximo y el minimo del vector
	for( i=0; i<n-1; i++){
		if( Phi[i]<MIN )
			MIN = Phi[i];
		if( Phi[i]>MAX)
			MAX = Phi[i];
	}

	// Pintamos uno a uno el valor de los nodos
        for( i=0; i<n-1; i++){

		double x = (Phi[i]-MIN)/(MAX-MIN); // Normalizamos los valores a [0,1]

		/* Paleta de colores continua
			El rojo representa al valor mas grande del vector.
			El verde representa la media del vector.
			El azul representa el valor mas pequeño del vector.*/
        r = x;
		g = (x*(x-1))/(-0.501960784*0.498039215);
		b = (1 - x);

		// Coloreamos el nodo
 		cairo_set_source_rgba( pincel, r, g, b, 1.0 );
		cairo_set_line_width( pincel, grosor );

        	// Ubicamos el nodo
		cairo_move_to( pincel, (int)(50.0+Delta*i), 80.0 );// Empieza en 50 y se mueve Delta
		cairo_line_to( pincel, (int)(50.0+Delta*(i+1)), 80.0 );
		// Dibujamos el nodo
		cairo_stroke(pincel);
	}

	// Texto
	double tamText = 15.0;
	cairo_set_font_size( pincel, tamText );
	cairo_set_source_rgba( pincel, 0.0, 0.0, 0.0, 1.0 );

    char text[15];

    sprintf(text, "%.2lf", Phi[0]);
    cairo_move_to( pincel,50, 130);
    cairo_show_text(pincel,text);
    cairo_stroke(pincel);

    sprintf(text, "%.2lf", Phi[n-2]);
    cairo_move_to( pincel,710, 130);
    cairo_show_text(pincel,text);
    cairo_stroke(pincel);

    cairo_move_to( pincel,50, 170);
    cairo_show_text(pincel,"Numero de nodos:");
    cairo_stroke(pincel);

    sprintf(text, "%d",n);
    cairo_move_to( pincel,200, 170);
    cairo_show_text(pincel,text);
    cairo_stroke(pincel);

    cairo_move_to( pincel,50, 190);
    cairo_show_text(pincel,"Q = ");
    cairo_stroke(pincel);

    sprintf(text, "%.2lf", Q);
    cairo_move_to( pincel,90, 190);
    cairo_show_text(pincel,text);
    cairo_stroke(pincel);

    cairo_move_to( pincel,50, 210);
    cairo_show_text(pincel,"k = ");
    cairo_stroke(pincel);

    sprintf(text, "%.2lf", k);
    cairo_move_to( pincel,90, 210);
    cairo_show_text(pincel,text);
    cairo_stroke(pincel);

    cairo_move_to( pincel,50, 230);
    cairo_show_text(pincel,"Longitud =");
    cairo_stroke(pincel);

    sprintf(text, "%.2lf", Len);
    cairo_move_to( pincel,150, 230);
    cairo_show_text(pincel,text);
    cairo_stroke(pincel);

	return FALSE;

}

int main(int argc, char *argv[]) {


    double *b,*L,*D;
    int i;
    scanf("%lf %lf %lf %lf %lf",&Len,&k,&Q,&phi0,&phin);
    scanf("%d",&n);
    double xdelta=Len/n;

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

    /*for (i=0;i<n-1;i++)
    printf("Phi[%d] = %lf\n",i,Phi[i]);*/

	// Tamaño de la venta de visulazición
	int length = 800; // Pixeles
	int width = 300; // Pixeles

	// Datos que deseamos pasar a la funcion que grafica
	datos *par = (datos*)malloc(1 * sizeof(datos));
	par->tam = 50;

	// Inicia gtk
	gtk_init( &argc, &argv );

	//área de dibujo
	GtkWidget *window;
	GtkWidget *areaDib;

	// Tìtulo y dimensiones de la ventana
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_title(GTK_WINDOW(window), "Simulacion Ecuacion del Calor");

	// Para cerrar
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	// Área de dibujo
	areaDib = gtk_drawing_area_new( );
	gtk_widget_set_size_request ( areaDib, length, width );

	// Llama a la función para dibujar la gráfica
	g_signal_connect( areaDib, "draw", G_CALLBACK(draw_cb), par );

	// Borde de la ventana
	gtk_container_set_border_width(GTK_CONTAINER(window), 15);
	// Agrega a la ventana lo que se dibujó
	gtk_container_add (GTK_CONTAINER (window), areaDib);
	// Muestra el área de dibujo
	gtk_widget_show( areaDib );
	// Muestra la ventana
	gtk_widget_show( window );

	gtk_main( );

	free(par);

	free(b);

	free(Phi);

	free(L);

	free(D);

	return 0;
}
