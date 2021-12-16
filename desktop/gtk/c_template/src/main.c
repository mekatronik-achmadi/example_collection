#include <gtk/gtk.h>

typedef struct {} app_widgets;

int main(int argc, char *argv[])
{
    GtkBuilder *builder;
    GtkWidget *window;
    app_widgets *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("glade/window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder,NULL);

    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();

    g_slice_free(app_widgets, widgets);

    return 0;
}

/*void dummy(GtkButton *button, app_widgets *app_wdgts){}*/

void on_window_main_destroy(){
    gtk_main_quit();
}
