#include <unistd.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

#define USE_ARG     FALSE
#define CHAR_PATH   1024

static void destroyWindowCb(GtkWidget* widget,GtkWidget* window){
    gtk_main_quit();
}

static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window){
    gtk_widget_destroy(window);
    return TRUE;
}

int main(int argc, char *argv[])
{

#if USE_ARG
#else
    char cwd[CHAR_PATH];
    char fname[CHAR_PATH];
#endif

    gtk_init(&argc, &argv);

    GtkWidget* main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);

    WebKitWebView* webView = WEBKIT_WEB_VIEW(webkit_web_view_new());
    gtk_container_add(GTK_CONTAINER(main_window), GTK_WIDGET(webView));

    g_signal_connect(main_window, "destroy", G_CALLBACK(destroyWindowCb),NULL);
    g_signal_connect(webView,"close",G_CALLBACK(closeWebViewCb),main_window);

#if USE_ARG
    if(argc < 2){
        g_print("no input html filename\r\n");
        return 1;
    }
    webkit_web_view_load_uri(webView, argv[1]);
#else
    if(getcwd(cwd, sizeof(cwd))==NULL){
        g_print("get current directory error\r\n");
    }
    else{
        sprintf(fname, "file://%s/documentation.html", cwd);
        webkit_web_view_load_uri(webView, fname);
    }
#endif

    gtk_widget_grab_focus(GTK_WIDGET(webView));

    gtk_widget_show_all(main_window);
    gtk_main();

    return 0;
}
