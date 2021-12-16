#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <stdlib.h>
#include <stdio.h>

GtkBuilder* builder;
GtkWidget* widget;
GtkButton *btnCalc,*btnExit;
GtkButton *btnPlus,*btnMinus,*btnMultiply,*btnDivide;
GtkRadioButton *rbPlus,*rbMinus,*rbMultiply,*rbDivide;
GtkEntry *txtV1,*txtV2,*txtVres;

char *strV1,*strV2,strVres[32];
int intV1,intV2,intVres;

void take_value(void){
	strV1=gtk_entry_get_text (txtV1);
	strV2=gtk_entry_get_text (txtV2);
	intV1=atoi(strV1);
	intV2=atoi(strV2);
}

void view_value(void){
	snprintf(strVres,32,"%i",intVres);
	gtk_entry_set_text(txtVres,strVres);
}

void plus_func(void){
	take_value();
	intVres=intV1+intV2;	
	view_value();
}

void minus_func(void){
	take_value();
	intVres=intV1-intV2;	
	view_value();
}

void multiply_func(void){
	take_value();
	intVres=intV1*intV2;	
	view_value();
}

void divide_func(void){
	take_value();
	intVres=intV1/intV2;	
	view_value();
}

void calculate(void){
	take_value();
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
	view_value();
}

int main(int argc, char* argv[]){

	gtk_init(&argc,&argv);
	builder=gtk_builder_new ();
	gtk_builder_add_from_file (builder,"calc2.glade",NULL);

	txtV1=GTK_ENTRY(gtk_builder_get_object (builder,"txtV1"));
	txtV2=GTK_ENTRY(gtk_builder_get_object (builder,"txtV2"));
	txtVres=GTK_ENTRY(gtk_builder_get_object (builder,"txtVres"));
	btnExit=GTK_BUTTON(gtk_builder_get_object(builder,"btnExit"));
	btnCalc=GTK_BUTTON(gtk_builder_get_object(builder,"btnCalc"));
	btnPlus=GTK_BUTTON(gtk_builder_get_object(builder,"btnPlus"));
	btnMinus=GTK_BUTTON(gtk_builder_get_object(builder,"btnMinus"));
	btnMultiply=GTK_BUTTON(gtk_builder_get_object(builder,"btnMultiply"));
	btnDivide=GTK_BUTTON(gtk_builder_get_object(builder,"btnDivide"));
	rbPlus=GTK_RADIO_BUTTON(gtk_builder_get_object(builder,"rbPlus"));
	rbMinus=GTK_RADIO_BUTTON(gtk_builder_get_object(builder,"rbMinus"));
	rbMultiply=GTK_RADIO_BUTTON(gtk_builder_get_object(builder,"rbMultiply"));
	rbDivide=GTK_RADIO_BUTTON(gtk_builder_get_object(builder,"rbDivide"));
	widget=GTK_WIDGET(gtk_builder_get_object (builder,"window1"));
	
	gtk_window_set_title(widget,"Simple Calculator");
	gtk_window_set_position(widget,GTK_WIN_POS_CENTER);
	
	gtk_signal_connect(widget,"destroy",gtk_main_quit,NULL);
	gtk_signal_connect(btnExit,"clicked",gtk_main_quit,NULL);
	gtk_signal_connect(btnCalc,"clicked",calculate,NULL);
	gtk_signal_connect(btnPlus,"clicked",plus_func,NULL);
	gtk_signal_connect(btnMinus,"clicked",minus_func,NULL);
	gtk_signal_connect(btnMultiply,"clicked",multiply_func,NULL);
	gtk_signal_connect(btnDivide,"clicked",divide_func,NULL);

	gtk_builder_connect_signals (builder,NULL);
	g_object_unref (G_OBJECT(builder));
	gtk_widget_show (widget);
	gtk_main ();

	return 0;
}
