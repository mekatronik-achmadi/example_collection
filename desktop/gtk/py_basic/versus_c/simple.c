#include <gtk/gtk.h>

int main(int argc, char *argv[]){
	GtkBuilder *mybuilder;
	GtkWindow *mywindow;
	GtkButton *btnQuit;
	
	gtk_init(&argc,&argv);
	mybuilder=gtk_builder_new();
	gtk_builder_add_from_file(mybuilder,"simple.glade",NULL);
	
	mywindow=gtk_builder_get_object(mybuilder,"window1");
	gtk_window_set_default_size(mywindow,200,200);
	gtk_window_set_position(mywindow,GTK_WIN_POS_CENTER);
	gtk_window_set_title(mywindow,"simple");
	gtk_signal_connect(mywindow,"destroy",gtk_main_quit,NULL);
	
	btnQuit=gtk_builder_get_object(mybuilder,"btnQuit");
	gtk_signal_connect(btnQuit,"clicked",gtk_main_quit,NULL);
	
	gtk_widget_show(mywindow);
	gtk_main();
	
	return 0;
}
