#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

static void destroyWindowCb(GtkWidget* widget, GtkWidget* window);
static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window);

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget* main_wndw = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(main_wndw),800,800);

    WebKitWebView* webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

    gtk_container_add(GTK_CONTAINER(main_wndw), GTK_WIDGET(webView));

    g_signal_connect(main_wndw, "destroy", G_CALLBACK(destroyWindowCb), NULL);
    g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb), NULL);

    webkit_web_view_load_uri(webView,"https://www.whatsmybrowser.org/");

    gtk_widget_grab_focus(GTK_WIDGET(webView));

    gtk_widget_show_all(main_wndw);

    gtk_main();

    return 0;
}

static void destroyWindowCb(GtkWidget* widget, GtkWidget* window){
    gtk_main_quit();
}
static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window){
    gtk_widget_destroy(window);
    return TRUE;
}
