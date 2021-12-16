#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

GtkBuilder* builder;
GtkWidget* widget;
GtkButton *btnPID;
pid_t my_pid;

void msg_pid(void){
	GtkWidget *msgbox;
	msgbox=gtk_message_dialog_new(widget,GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE,"PID = %i",my_pid);
	gtk_window_set_title(msgbox,"PID value");
	gtk_dialog_run(msgbox);
	gtk_widget_destroy(msgbox);
}

void view_PID(void){
	my_pid=getpid();
	g_print("PID= %i\n",my_pid);
	msg_pid();
}

int main(int argc, char* argv[]){

	gtk_init(&argc,&argv);
	builder=gtk_builder_new ();
	gtk_builder_add_from_file (builder,"test.glade",NULL);

	btnPID=GTK_BUTTON(gtk_builder_get_object(builder,"btnPID"));
	widget=GTK_WIDGET(gtk_builder_get_object (builder,"window1"));
	
	gtk_window_set_title(widget,"System Experiment");
	gtk_window_set_position(widget,GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(widget,200,200);
	gtk_signal_connect(widget,"destroy",gtk_main_quit,NULL);
	
	gtk_signal_connect(btnPID,"clicked",view_PID,NULL);

	gtk_builder_connect_signals (builder,NULL);
	g_object_unref (G_OBJECT(builder));
	gtk_widget_show (widget);
	gtk_main ();

	return 0;
}
