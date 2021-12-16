#include <gtk/gtk.h>

//void destroy(GtkWidget *widget,gpointer data){
	//gtk_main_quit();
//}

int main(int argc, char *argv[]){
	//init GTK
	GtkWidget *window;
	GdkPixbuf *icons;
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	icons=gdk_pixbuf_new_from_file("/usr/share/icons/matefaenza/places/22/start-here-mate.png",NULL);
	
	//signal connects
	//gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(destroy),NULL);
	gtk_signal_connect(window,"destroy",gtk_main_quit,NULL);
	
	//window management
	gtk_window_set_title(window,"Test");
	gtk_window_set_default_size(window,200,200);
	gtk_window_set_position(window,GTK_WIN_POS_CENTER);
	gtk_window_set_icon(window,icons);
	
	//tooltips
	gtk_widget_set_tooltip_text(window,"just a test");
	
	//run gtk
	//gtk_widget_show_all(window);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
