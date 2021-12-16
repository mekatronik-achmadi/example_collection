#include <gtk/gtk.h>

typedef struct {
    GtkWidget     *w_txt_vw_memory;
    GtkTextBuffer *textbuffer_main;
} app_widgets;

int main(int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;
    app_widgets     *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("glade/window_main.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    widgets->w_txt_vw_memory  = GTK_WIDGET(gtk_builder_get_object(builder, "txt_vw_memory"));
    widgets->textbuffer_main  = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textbuffer_main"));

    gtk_builder_connect_signals(builder, widgets);

    g_object_unref(builder);

    gtk_widget_show_all(window);
    gtk_main();

    g_slice_free(app_widgets, widgets);

    return 0;
}

void on_btn_get_mem_size_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    gboolean result;
    gchar *standard_out;
    gchar *standard_err;
    gint exit_state;
    GError *err;

    result = g_spawn_command_line_sync(
                           "free -h",
                           &standard_out,
                           &standard_err,
                           &exit_state,
                           &err);
    if (result == FALSE) {
        g_print("An error occured\n");
    }
    else {
       gtk_text_buffer_set_text(app_wdgts->textbuffer_main, standard_out, -1);
    }
}

void on_window_main_destroy()
{
    gtk_main_quit();
}
