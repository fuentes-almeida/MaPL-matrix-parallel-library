#ifndef DRAW_HPP_INCLUDED
#define DRAW_HPP_INCLUDED
GtkWidget *window;
GtkWidget *areaDib;

static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, datos* data);
gboolean desplaza(GtkWidget *widget, GdkEventKey *event, datos *data);

#endif // DRAW_HPP_INCLUDED
