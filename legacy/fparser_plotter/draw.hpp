#ifndef DRAW_HPP_INCLUDED
#define DRAW_HPP_INCLUDED



static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer par);
gboolean desplaza(GtkWidget *widget, GdkEventKey *event, gpointer aux);
double fx(double x);

#endif // DRAW_HPP_INCLUDED
