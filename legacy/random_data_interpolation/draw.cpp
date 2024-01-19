#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include "memo.hpp"
#include "methods.hpp"
#include "draw.hpp"
#define length 800
#define width 600
#define datasize 800




//Funcion para dibujar
static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, datos* data)
    {
	double grosor, red, green, blue, trans, tamText;
     	double xdelta,factor;
   	int i,j,k;


    double *xvalue=RequestVectorDoubleMem(datasize);
    double *yvalue1=RequestVectorDoubleMem(datasize);
    double *yvalue2=RequestVectorDoubleMem(datasize);
    double *yvalue3=RequestVectorDoubleMem(datasize);
    double *yvalue4=RequestVectorDoubleMem(datasize);
    double *yvalue5=RequestVectorDoubleMem(datasize);
    double *yvalue6=RequestVectorDoubleMem(datasize);
    //Asignar x y fx a dos vectores
	xdelta=(data->xmax-data->xmin)/length;
	factor=1/xdelta;

	for(k=0;k<length;k++)
        {
        xvalue[k]=(data->xmin+k*xdelta)*data->xscale+data->xoffset;
        yvalue1[k]=EvalPolinomio(xvalue[k],data->N,data->a)*data->yscale+data->yoffset;
        yvalue2[k]=LagrangeInterpolation(xvalue[k],data->N,data->curve)*data->yscale+data->yoffset;
        yvalue3[k]=NewtonInterpolation(xvalue[k],data->N,data->curve)*data->yscale+data->yoffset;
        yvalue4[k]=splineC0(xvalue[k],data->curve)*data->yscale+data->yoffset;
        yvalue5[k]=splineC1(xvalue[k],data->curve)*data->yscale+data->yoffset;
        yvalue6[k]=splineC2(xvalue[k],data->N,data->xvec,data->curve)*data->yscale+data->yoffset;
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

        cairo_move_to(pincel, 0,width/2-factor*data->yoffset);
        cairo_line_to(pincel, length, width/2-factor*data->yoffset);
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

    switch (data->flag)
    {

    case 1:
	// Dibuja una linea
	grosor = 7.0;     // Grosor
	red = 1.0;        // Nivel de rojo
	green = 0.0;      // Nivel de verde
	blue = 0.0;       // Nivel de azul
	trans = 0.3;      // Transparencia

	cairo_set_source_rgba( pincel, red, green, blue, trans );
	cairo_set_line_width( pincel, grosor );

	for (i=0; i<length-1; i++)
        {
        cairo_move_to( pincel, i, width/2-factor*yvalue1[i] );
        cairo_line_to( pincel, i+1, width/2-factor*yvalue1[i+1] );
        }
    cairo_stroke(pincel);
    break;
    case 2:
    // Dibuja una linea
	grosor = 5.0;     // Grosor
	red = 0.0;        // Nivel de rojo
	green = 0.0;      // Nivel de verde
	blue = 1.0;       // Nivel de azul
	trans = 0.3;      // Transparencia

	cairo_set_source_rgba( pincel, red, green, blue, trans );
	cairo_set_line_width( pincel, grosor );

    for (i=0; i<length-1; i++)
        {
        cairo_move_to( pincel, i, width/2-factor*yvalue2[i] );
        cairo_line_to( pincel, i+1, width/2-factor*yvalue2[i+1] );
        }
	cairo_stroke(pincel);
	break;
    case 3:
    // Dibuja una linea
	grosor = 1.0;     // Grosor
	red = 0.0;        // Nivel de rojo
	green = 1.0;      // Nivel de verde
	blue = 0.0;       // Nivel de azul
	trans = 1.0;      // Transparencia

	cairo_set_source_rgba( pincel, red, green, blue, trans );
	cairo_set_line_width( pincel, grosor );

    for (i=0; i<length-1; i++)
        {
        cairo_move_to( pincel, i, width/2-factor*yvalue3[i] );
        cairo_line_to( pincel, i+1, width/2-factor*yvalue3[i+1] );
        }

	cairo_stroke(pincel);
	break;
    case 4:
    // Dibuja una linea
	grosor = 7.0;     // Grosor
	red = 0.0;        // Nivel de rojo
	green = 0.5;      // Nivel de verde
	blue = 0.5;       // Nivel de azul
	trans = 0.5;      // Transparencia

	cairo_set_source_rgba( pincel, red, green, blue, trans );
	cairo_set_line_width( pincel, grosor );

    for (i=0; i<length-1; i++)
        {
        cairo_move_to( pincel, i, width/2-factor*yvalue4[i] );
        cairo_line_to( pincel, i+1, width/2-factor*yvalue4[i+1] );
        }

	cairo_stroke(pincel);
	break;
    case 5:
    // Dibuja una linea
	grosor = 5.0;     // Grosor
	red = 0.5;        // Nivel de rojo
	green = 0.3;      // Nivel de verde
	blue = 0.0;       // Nivel de azul
	trans = 1.0;      // Transparencia

	cairo_set_source_rgba( pincel, red, green, blue, trans );
	cairo_set_line_width( pincel, grosor );

    for (i=0; i<length-1; i++)
        {
        cairo_move_to( pincel, i, width/2-factor*yvalue5[i] );
        cairo_line_to( pincel, i+1, width/2-factor*yvalue5[i+1] );
        }

	cairo_stroke(pincel);
	break;
	case 6:
    // Dibuja una linea
	grosor = 2.0;     // Grosor
	red = 0.0;        // Nivel de rojo
	green = 1.0;      // Nivel de verde
	blue = 0.7;       // Nivel de azul
	trans = 1.0;      // Transparencia

	cairo_set_source_rgba( pincel, red, green, blue, trans );
	cairo_set_line_width( pincel, grosor );

    for (i=0; i<length-1; i++)
        {
        cairo_move_to( pincel, i, width/2-factor*yvalue6[i] );
        cairo_line_to( pincel, i+1, width/2-factor*yvalue6[i+1] );
        }

	cairo_stroke(pincel);
	break;
    }
	return FALSE;
}

gboolean desplaza(GtkWidget *widget, GdkEventKey *event, datos *data)
{
    // Donde se va a pintar
	GdkWindow *sup = gtk_widget_get_window ( widget );

    // Crea un pincel
	cairo_t *pincel = gdk_cairo_create( sup );

	cairo_set_source_rgba(pincel,1.0,0.0,0.0,1.0);
	cairo_set_line_width(pincel,2.0);
   	//gpointer *par=NULL;

       switch(event->keyval)
       {
        case 'z':data->xscale+=0.1;
        draw_cb(areaDib,pincel,data);break;

        case 'x':data->xscale-=0.1;
        if (data->xscale<0) data->xscale=0;
        draw_cb(areaDib,pincel,data);break;

        case 'a':data->yscale+=0.1;
        draw_cb(areaDib,pincel,data);break;

        case 's':data->yscale-=0.1;
        if (data->yscale<0) data->yscale=0;
        draw_cb(areaDib,pincel,data);break;

        case 'c':data->xoffset+=0.1;
        draw_cb(areaDib,pincel,data);break;

        case 'v':data->xoffset-=0.1;
        draw_cb(areaDib,pincel,data);break;

        case 'd':data->yoffset+=0.1;
        draw_cb(areaDib,pincel,data);break;

        case 'f':data->yoffset-=0.1;
        draw_cb(areaDib,pincel,data);break;

        case '1':
            data->flag=1;
            draw_cb(areaDib,pincel,data);break;
        case '2':
            data->flag=2;
            draw_cb(areaDib,pincel,data);break;
        case '3':
            data->flag=3;
            draw_cb(areaDib,pincel,data);break;
        case '4':
            data->flag=4;
            draw_cb(areaDib,pincel,data);break;
        case '5':
            data->flag=5;
            draw_cb(areaDib,pincel,data);break;
        case '6':
            data->flag=6;
            draw_cb(areaDib,pincel,data);break;
        }
       cairo_stroke(pincel);

return FALSE;
}
