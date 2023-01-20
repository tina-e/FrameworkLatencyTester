#include <cairo.h>
#include <gtk/gtk.h>

static void draw(cairo_t *);

int r = 0;
int g = 0;
int b = 0;

int pressed = 0;

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    draw(cr);

    return 0;
}

static gboolean on_click_event(GtkWidget *widget, gpointer data)
{
    pressed = 1;
    gtk_widget_queue_draw(widget);
    return 0;
}

static gboolean on_release_event(GtkWidget *widget, gpointer data)
{
    pressed = 0;
    gtk_widget_queue_draw(widget);
    return 0;
}

static void draw(cairo_t *cr)
{
    if(pressed)
    {
        for (int i = 0; i < 1000; i++)
        {
            float r = (float)rand() / RAND_MAX;
            float g = (float)rand() / RAND_MAX;
            float b = (float)rand() / RAND_MAX;
            float a = 1; //(float)rand() / RAND_MAX;
            cairo_set_source_rgba(cr, r, g, b, a);

            int x = rand() % 1920;
            int y = rand() % 1080;
            int width = rand() % (1920 - x);
            int height = rand() % (1080 - y);

            cairo_rectangle(cr, x, y, width, height);
            cairo_fill(cr);
        }
        cairo_set_source_rgba(cr, 1, 1, 1, 1);
        cairo_rectangle(cr, 0, 0, 300, 300);
        cairo_fill(cr);
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

    return 0;
}
