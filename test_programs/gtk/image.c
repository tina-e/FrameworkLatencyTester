// this program is based on tutorials by ZetCode
// https://zetcode.com/gfx/cairo/

#include <cairo.h>
#include <gtk/gtk.h>

static void draw(cairo_t *);

int clicked = 0;

cairo_surface_t *image; 

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    draw(cr);

    return FALSE;
}

static gboolean on_click_event(GtkWidget *widget, gpointer data)
{
    clicked = 1;
    gtk_widget_queue_draw(widget);
    return FALSE;
}

static gboolean on_release_event(GtkWidget *widget, gpointer data)
{
    clicked = 0;
    gtk_widget_queue_draw(widget);
    return FALSE;
}

static void draw(cairo_t *cr)
{
    if (clicked)
    {
        cairo_set_source_surface(cr, image, 0, 0);
        cairo_paint(cr);   
    }
    else
    {
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_move_to(cr, 0.0, 0.0);
        cairo_rectangle(cr, 0, 0, 1920, 1080);
        cairo_fill(cr);
    }
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *drawing_area;

    image = cairo_image_surface_create_from_png("noise.png");

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(window);

    drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_event), NULL); 
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(window, "button-press-event", G_CALLBACK(on_click_event), NULL); 
    g_signal_connect(window, "button-release-event", G_CALLBACK(on_release_event), NULL); 

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1080); 
    gtk_window_set_title(GTK_WINDOW(window), "GTK Test Application");

    gtk_widget_show_all(window);

    gtk_main();

    cairo_surface_destroy(image);

    return 0;
}
