#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <stdlib.h>
#include <stdio.h>

GtkBuilder* builder;
GtkWidget* widget;
GtkRadioButton *rbPlus,*rbMinus,*rbMultiply,*rbDivide;
GtkEntry *txtV1,*txtV2,*txtVres;

char *strV1,*strV2,strVres[32];
int intV1,intV2,intVres;

void on_window1_destroy(GtkObject* object, gpointer user_data){
	gtk_main_quit();
}

void on_btnExit_clicked(GtkButton *button, gpointer user_data){
	gtk_main_quit();
}

void on_btnPlus_clicked(GtkButton *button, gpointer user_data){
	strV1=gtk_entry_get_text (txtV1);
	strV2=gtk_entry_get_text (txtV2);
	intV1=atoi(strV1);
	intV2=atoi(strV2);
	intVres=intV1+intV2;
	snprintf(strVres,32,"%i",intVres);
	gtk_entry_set_text(txtVres,strVres);
}

void on_btnMinus_clicked(GtkButton *button, gpointer user_data){
	strV1=gtk_entry_get_text (txtV1);
	strV2=gtk_entry_get_text (txtV2);
	intV1=atoi(strV1);
	intV2=atoi(strV2);
	intVres=intV1-intV2;
	snprintf(strVres,32,"%i",intVres);
	gtk_entry_set_text(txtVres,strVres);
}

void on_btnMultiply_clicked(GtkButton *button, gpointer user_data){
	strV1=gtk_entry_get_text (txtV1);
	strV2=gtk_entry_get_text (txtV2);
	intV1=atoi(strV1);
	intV2=atoi(strV2);
	intVres=intV1*intV2;
	snprintf(strVres,32,"%i",intVres);
	gtk_entry_set_text(txtVres,strVres);
}

void on_btnDivide_clicked(GtkButton *button, gpointer user_data){
	strV1=gtk_entry_get_text (txtV1);
	strV2=gtk_entry_get_text (txtV2);
	intV1=atoi(strV1);
	intV2=atoi(strV2);
	intVres=intV1/intV2;
	snprintf(strVres,32,"%i",intVres);
	gtk_entry_set_text(txtVres,strVres);
}

void on_btnCalc_clicked(GtkButton *button, gpointer user_data){
	strV1=gtk_entry_get_text (txtV1);
	strV2=gtk_entry_get_text (txtV2);
	intV1=atoi(strV1);
	intV2=atoi(strV2);
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rbPlus))){
		intVres=intV1+intV2;
	}
	else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rbMinus))){
		intVres=intV1-intV2;
	}
	else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rbMultiply))){
		intVres=intV1*intV2;
	}
	else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rbDivide))){
		intVres=intV1/intV2;
	}
	snprintf(strVres,32,"%i",intVres);
	gtk_entry_set_text(txtVres,strVres);
}

int main(int argc, char* argv[]){

	gtk_init(&argc,&argv);
	builder=gtk_builder_new ();
	gtk_builder_add_from_file (builder,"calc.glade",NULL);

	txtV1=GTK_ENTRY(gtk_builder_get_object (builder,"txtV1"));
	txtV2=GTK_ENTRY(gtk_builder_get_object (builder,"txtV2"));
	txtVres=GTK_ENTRY(gtk_builder_get_object (builder,"txtVres"));
	rbPlus=GTK_RADIO_BUTTON(gtk_builder_get_object(builder,"rbPlus"));
	rbMinus=GTK_RADIO_BUTTON(gtk_builder_get_object(builder,"rbMinus"));
	rbMultiply=GTK_RADIO_BUTTON(gtk_builder_get_object(builder,"rbMultiply"));
	rbDivide=GTK_RADIO_BUTTON(gtk_builder_get_object(builder,"rbDivide"));
	widget=GTK_WIDGET(gtk_builder_get_object (builder,"window1"));
	
	gtk_window_set_title(widget,"Simple Calculator");
	gtk_window_set_position(widget,GTK_WIN_POS_CENTER);

	gtk_builder_connect_signals (builder,NULL);
	g_object_unref (G_OBJECT(builder));
	gtk_widget_show (widget);
	gtk_main ();

	return 0;
}
